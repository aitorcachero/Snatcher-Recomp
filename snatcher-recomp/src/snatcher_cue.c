#include "snatcher_cue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#endif

#define RAW 2352
#define FIRST_LBA -150
#define MAX_TRACKS 100
#define EDC_POLY 0xD8018001u
#define ECC_POLY 0x11Du

static uint32_t s_edc_table[256];
static uint8_t s_ecc_fwd[256];
static uint8_t s_ecc_bwd[256];
static int s_tables_inited = 0;

static void init_tables(void) {
    if (s_tables_inited) return;
    for (uint32_t i = 0; i < 256; i++) {
        uint32_t edc = i;
        for (int b = 0; b < 8; b++) {
            edc = (edc >> 1) ^ (edc & 1 ? EDC_POLY : 0);
        }
        s_edc_table[i] = edc;
    }
    for (uint32_t i = 0; i < 256; i++) {
        uint32_t v = i << 1;
        if (v & 0x100) v ^= ECC_POLY;
        s_ecc_fwd[i] = (uint8_t)v;
    }
    for (uint32_t i = 0; i < 256; i++) {
        s_ecc_bwd[s_ecc_fwd[i] ^ i] = (uint8_t)i;
    }
    s_tables_inited = 1;
}

static uint32_t calc_edc(const uint8_t *data, size_t size) {
    uint32_t edc = 0;
    for (size_t i = 0; i < size; i++) {
        edc = (edc >> 8) ^ s_edc_table[(edc ^ data[i]) & 0xFF];
    }
    return edc;
}

static void calc_ecc_pair(uint8_t *sector, int dst_offset, int major_count, int minor_count, int major_mult, int minor_inc) {
    int size = major_count * minor_count;
    for (int major = 0; major < major_count; major++) {
        int index = (major >> 1) * major_mult + (major & 1);
        uint8_t a = 0, b = 0;
        for (int minor = 0; minor < minor_count; minor++) {
            uint8_t sample = sector[12 + index];
            index += minor_inc;
            if (index >= size) index -= size;
            a = s_ecc_fwd[a ^ sample];
            b ^= sample;
        }
        uint8_t first = s_ecc_bwd[s_ecc_fwd[a] ^ b];
        uint8_t second = first ^ b;
        sector[dst_offset + major] = first;
        sector[dst_offset + major_count + major] = second;
    }
}

static uint8_t to_bcd(int val) {
    return (uint8_t)(((val / 10) * 16) + (val % 10));
}

static void encode_zero_mode1_sector(int lba, uint8_t sector[RAW]) {
    init_tables();
    int abs_frames = lba - FIRST_LBA;
    int minute = abs_frames / (60 * 75);
    int rem = abs_frames % (60 * 75);
    int second = rem / 75;
    int frame = rem % 75;

    memset(sector, 0, RAW);
    sector[0] = 0x00;
    memset(sector + 1, 0xFF, 10);
    sector[11] = 0x00;
    sector[12] = to_bcd(minute);
    sector[13] = to_bcd(second);
    sector[14] = to_bcd(frame);
    sector[15] = 1; // Mode 1

    uint32_t edc = calc_edc(sector, 2064);
    sector[2064] = (uint8_t)(edc & 0xFF);
    sector[2065] = (uint8_t)((edc >> 8) & 0xFF);
    sector[2066] = (uint8_t)((edc >> 16) & 0xFF);
    sector[2067] = (uint8_t)((edc >> 24) & 0xFF);

    calc_ecc_pair(sector, 2076, 86, 24, 2, 86);
    calc_ecc_pair(sector, 2248, 52, 43, 86, 88);
}

// SHA-256 implementation
typedef struct {
    uint32_t state[8];
    uint64_t bytes;
    uint8_t block[64];
    size_t used;
} Sha256;

static const uint32_t sha_k[64] = {
    0x428a2f98u,0x71374491u,0xb5c0fbcfu,0xe9b5dba5u,0x3956c25bu,0x59f111f1u,0x923f82a4u,0xab1c5ed5u,
    0xd807aa98u,0x12835b01u,0x243185beu,0x550c7dc3u,0x72be5d74u,0x80deb1feu,0x9bdc06a7u,
    0xc19bf174u,0xe49b69c1u,0xefbe4786u,0x0fc19dc6u,0x240ca1ccu,0x2de92c6fu,0x4a7484aau,0x5cb0a9dcu,
    0x76f988dau,0x983e5152u,0xa831c66du,0xb00327c8u,0xbf597fc7u,0xc6e00bf3u,0xd5a79147u,0x06ca6351u,
    0x14292967u,0x27b70a85u,0x2e1b2138u,0x4d2c6dfcu,0x53380d13u,0x650a7354u,0x766a0abbu,0x81c2c92eu,
    0x92722c85u,0xa2bfe8a1u,0xa81a664bu,0xc24b8b70u,0xc76c51a3u,0xd192e819u,0xd6990624u,0xf40e3585u,
    0x106aa070u,0x19a4c116u,0x1e376c08u,0x2748774cu,0x34b0bcb5u,0x391c0cb3u,0x4ed8aa4au,0x5b9cca4fu,
    0x682e6ff3u,0x748f82eeu,0x78a5636fu,0x84c87814u,0x8cc70208u,0x90befffau,0xa4506cebu,0xbef9a3f7u,
    0xc67178f2u
};

static uint32_t rotr32(uint32_t val, unsigned bits) {
    return (val >> bits) | (val << (32u - bits));
}

static void sha_transform(Sha256 *sha, const uint8_t block[64]) {
    uint32_t w[64], a,b,c,d,e,f,g,h;
    for (int i = 0; i < 16; ++i) {
        size_t p = (size_t)i * 4;
        w[i] = ((uint32_t)block[p] << 24) | ((uint32_t)block[p+1] << 16) |
               ((uint32_t)block[p+2] << 8) | (uint32_t)block[p+3];
    }
    for (int i = 16; i < 64; ++i) {
        uint32_t s0 = rotr32(w[i-15],7) ^ rotr32(w[i-15],18) ^ (w[i-15] >> 3);
        uint32_t s1 = rotr32(w[i-2],17) ^ rotr32(w[i-2],19) ^ (w[i-2] >> 10);
        w[i] = w[i-16] + s0 + w[i-7] + s1;
    }
    a=sha->state[0]; b=sha->state[1]; c=sha->state[2]; d=sha->state[3];
    e=sha->state[4]; f=sha->state[5]; g=sha->state[6]; h=sha->state[7];
    for (int i = 0; i < 64; ++i) {
        uint32_t s1 = rotr32(e,6) ^ rotr32(e,11) ^ rotr32(e,25);
        uint32_t ch = (e & f) ^ (~e & g);
        uint32_t t1 = h + s1 + ch + sha_k[i] + w[i];
        uint32_t s0 = rotr32(a,2) ^ rotr32(a,13) ^ rotr32(a,22);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        uint32_t t2 = s0 + maj;
        h=g; g=f; f=e; e=d+t1; d=c; c=b; b=a; a=t1+t2;
    }
    sha->state[0]+=a; sha->state[1]+=b; sha->state[2]+=c; sha->state[3]+=d;
    sha->state[4]+=e; sha->state[5]+=f; sha->state[6]+=g; sha->state[7]+=h;
}

static void sha_init(Sha256 *sha) {
    static const uint32_t initial[8] = {
        0x6a09e667u,0xbb67ae85u,0x3c6ef372u,0xa54ff53au,
        0x510e527fu,0x9b05688cu,0x1f83d9abu,0x5be0cd19u
    };
    memcpy(sha->state, initial, sizeof(initial));
    sha->bytes = 0;
    sha->used = 0;
}

static void sha_update(Sha256 *sha, const uint8_t *data, size_t size) {
    sha->bytes += (uint64_t)size;
    while (size != 0) {
        size_t take = sizeof(sha->block) - sha->used;
        if (take > size) take = size;
        memcpy(sha->block + sha->used, data, take);
        sha->used += take;
        data += take;
        size -= take;
        if (sha->used == sizeof(sha->block)) {
            sha_transform(sha, sha->block);
            sha->used = 0;
        }
    }
}

static void sha_final(Sha256 *sha, uint8_t out[32]) {
    uint64_t bit_count = sha->bytes * 8u;
    sha->block[sha->used++] = 0x80;
    if (sha->used > 56) {
        memset(sha->block + sha->used, 0, sizeof(sha->block) - sha->used);
        sha_transform(sha, sha->block);
        sha->used = 0;
    }
    memset(sha->block + sha->used, 0, 56 - sha->used);
    for (int i = 0; i < 8; ++i)
        sha->block[63-i] = (uint8_t)(bit_count >> (i*8u));
    sha_transform(sha, sha->block);
    for (int i = 0; i < 8; ++i) {
        out[i*4] = (uint8_t)(sha->state[i] >> 24);
        out[i*4+1] = (uint8_t)(sha->state[i] >> 16);
        out[i*4+2] = (uint8_t)(sha->state[i] >> 8);
        out[i*4+3] = (uint8_t)sha->state[i];
    }
}

// CUE and Track structures
typedef struct {
    int number;
    char path[512];
    int is_data;
    int has_index0;
    int index0;
    int has_index1;
    int index1;
    int pregap;
    int postgap;
    int stored_start;
    int stored_end;
    int index00;
    int start;
    int end;
} CueTrack;

static int parse_frames(const char *str) {
    int m = 0, s = 0, f = 0;
    if (sscanf(str, "%d:%d:%d", &m, &s, &f) == 3) {
        return (m * 60 + s) * 75 + f;
    }
    return -1;
}

static int64_t get_file_size_bytes(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return -1;
#if defined(_MSC_VER)
    _fseeki64(f, 0, SEEK_END);
    int64_t sz = _ftelli64(f);
#else
    fseeko(f, 0, SEEK_END);
    int64_t sz = ftello(f);
#endif
    fclose(f);
    return sz;
}

int convert_cue_to_sgcd(const char *cue_path, const char *out_sgcd_path, char *err_msg, size_t err_cap) {
    FILE *fcue = fopen(cue_path, "r");
    if (!fcue) {
        snprintf(err_msg, err_cap, "No se pudo abrir el archivo CUE: %s", cue_path);
        return 0;
    }

    // Extraer directorio contenedor del archivo CUE
    char cue_dir[512] = { 0 };
    strncpy(cue_dir, cue_path, sizeof(cue_dir) - 1);
    char *last_slash = strrchr(cue_dir, '/');
    char *last_bslash = strrchr(cue_dir, '\\');
    char *slash = last_slash > last_bslash ? last_slash : last_bslash;
    if (slash) {
        *(slash + 1) = '\0';
    } else {
        cue_dir[0] = '\0';
    }

    CueTrack tracks[MAX_TRACKS];
    int num_tracks = 0;
    char current_bin[512] = { 0 };

    char line[1024];
    while (fgets(line, sizeof(line), fcue)) {
        char *p = line;
        while (*p && isspace((unsigned char)*p)) p++;
        if (*p == '\0' || *p == '#') continue;

        if (_strnicmp(p, "REM", 3) == 0 || _strnicmp(p, "TITLE", 5) == 0 ||
            _strnicmp(p, "PERFORMER", 9) == 0 || _strnicmp(p, "SONGWRITER", 10) == 0 ||
            _strnicmp(p, "CATALOG", 7) == 0 || _strnicmp(p, "ISRC", 4) == 0) {
            continue;
        }

        if (_strnicmp(p, "FILE", 4) == 0) {
            p += 4;
            while (*p && isspace((unsigned char)*p)) p++;
            if (*p == '"') {
                p++;
                char *endq = strchr(p, '"');
                if (endq) {
                    *endq = '\0';
                    if (cue_dir[0] != '\0') {
                        snprintf(current_bin, sizeof(current_bin), "%s%s", cue_dir, p);
                    } else {
                        strncpy(current_bin, p, sizeof(current_bin) - 1);
                    }
                }
            }
        } else if (_strnicmp(p, "TRACK", 5) == 0) {
            if (num_tracks >= MAX_TRACKS) {
                snprintf(err_msg, err_cap, "Demasiadas pistas en el archivo CUE (max %d)", MAX_TRACKS);
                fclose(fcue);
                return 0;
            }
            int track_num = 0;
            char track_type[64] = { 0 };
            if (sscanf(p + 5, "%d %63s", &track_num, track_type) >= 2) {
                CueTrack *t = &tracks[num_tracks++];
                memset(t, 0, sizeof(*t));
                t->number = track_num;
                strncpy(t->path, current_bin, sizeof(t->path) - 1);
                t->is_data = (_strnicmp(track_type, "AUDIO", 5) != 0);
            }
        } else if (_strnicmp(p, "INDEX", 5) == 0 && num_tracks > 0) {
            int idx_num = 0;
            char msf[64] = { 0 };
            if (sscanf(p + 5, "%d %63s", &idx_num, msf) >= 2) {
                int fr = parse_frames(msf);
                if (fr >= 0) {
                    CueTrack *t = &tracks[num_tracks - 1];
                    if (idx_num == 0) {
                        t->has_index0 = 1;
                        t->index0 = fr;
                    } else if (idx_num == 1) {
                        t->has_index1 = 1;
                        t->index1 = fr;
                    }
                }
            }
        } else if (_strnicmp(p, "PREGAP", 6) == 0 && num_tracks > 0) {
            char msf[64] = { 0 };
            if (sscanf(p + 6, "%63s", msf) >= 1) {
                int fr = parse_frames(msf);
                if (fr >= 0) tracks[num_tracks - 1].pregap = fr;
            }
        } else if (_strnicmp(p, "POSTGAP", 7) == 0 && num_tracks > 0) {
            char msf[64] = { 0 };
            if (sscanf(p + 7, "%63s", msf) >= 1) {
                int fr = parse_frames(msf);
                if (fr >= 0) tracks[num_tracks - 1].postgap = fr;
            }
        }
    }
    fclose(fcue);

    if (num_tracks == 0) {
        snprintf(err_msg, err_cap, "No se encontraron pistas validas en el archivo CUE");
        return 0;
    }

    // Calcular limites de sectores para cada pista
    int cursor = 0;
    for (int i = 0; i < num_tracks; i++) {
        CueTrack *t = &tracks[i];
        if (!t->has_index1) {
            snprintf(err_msg, err_cap, "Pista %d no tiene INDEX 01", t->number);
            return 0;
        }
        int64_t fsz = get_file_size_bytes(t->path);
        if (fsz < 0 || (fsz % RAW) != 0) {
            snprintf(err_msg, err_cap, "Archivo BIN no encontrado o tamano incorrecto: %s", t->path);
            return 0;
        }
        int total_sectors = (int)(fsz / RAW);
        t->stored_start = t->has_index0 ? t->index0 : t->index1;
        t->stored_end = total_sectors;

        if (i + 1 < num_tracks && strcmp(tracks[i + 1].path, t->path) == 0) {
            CueTrack *next = &tracks[i + 1];
            if (!next->has_index1) {
                snprintf(err_msg, err_cap, "Pista siguiente %d sin INDEX 01", next->number);
                return 0;
            }
            t->stored_end = next->has_index0 ? next->index0 : next->index1;
        }

        int stored_gap = t->index1 - t->stored_start;
        if (i == 0) {
            t->index00 = FIRST_LBA;
            t->start = 0;
        } else {
            t->index00 = cursor;
            t->start = cursor + t->pregap + stored_gap;
        }
        t->end = t->start + t->stored_end - t->index1 + t->postgap;
        cursor = t->end;
    }

    int leadout = tracks[num_tracks - 1].end;
    uint32_t header_bytes = 96;
    uint32_t track_bytes = 32;
    uint32_t offset = header_bytes + (uint32_t)num_tracks * track_bytes;
    uint64_t payload_bytes = (uint64_t)(leadout - FIRST_LBA) * RAW;

    FILE *out = fopen(out_sgcd_path, "wb");
    if (!out) {
        snprintf(err_msg, err_cap, "No se pudo crear el archivo de destino: %s", out_sgcd_path);
        return 0;
    }

    // Cabecera temporal de ceros
    uint8_t zero_header[768];
    memset(zero_header, 0, sizeof(zero_header));
    if (fwrite(zero_header, 1, offset, out) != offset) {
        snprintf(err_msg, err_cap, "Error al escribir cabecera inicial");
        fclose(out);
        return 0;
    }

    Sha256 sha;
    sha_init(&sha);

    uint8_t sector_buf[RAW];
    uint8_t *copy_buf = (uint8_t *)malloc(64 * 1024);
    if (!copy_buf) {
        snprintf(err_msg, err_cap, "Error de memoria al reservar buffer de copia");
        fclose(out);
        return 0;
    }

    // Escribir payload de pistas
    for (int i = 0; i < num_tracks; i++) {
        CueTrack *t = &tracks[i];
        int gap = t->index1 - t->stored_start;

        int pregap_sectors = (i == 0) ? (150 - gap) : t->pregap;
        int pregap_first_lba = (i == 0) ? FIRST_LBA : t->index00;

        for (int s = 0; s < pregap_sectors; s++) {
            if (t->is_data) {
                encode_zero_mode1_sector(pregap_first_lba + s, sector_buf);
            } else {
                memset(sector_buf, 0, RAW);
            }
            fwrite(sector_buf, 1, RAW, out);
            sha_update(&sha, sector_buf, RAW);
        }

        FILE *fbin = fopen(t->path, "rb");
        if (!fbin) {
            snprintf(err_msg, err_cap, "No se pudo abrir BIN para lectura: %s", t->path);
            free(copy_buf);
            fclose(out);
            return 0;
        }

#if defined(_MSC_VER)
        _fseeki64(fbin, (int64_t)t->stored_start * RAW, SEEK_SET);
#else
        fseeko(fbin, (int64_t)t->stored_start * RAW, SEEK_SET);
#endif
        int64_t remaining_bytes = (int64_t)(t->stored_end - t->stored_start) * RAW;
        while (remaining_bytes > 0) {
            size_t to_read = (remaining_bytes < 64 * 1024) ? (size_t)remaining_bytes : 64 * 1024;
            size_t rd = fread(copy_buf, 1, to_read, fbin);
            if (rd != to_read) {
                snprintf(err_msg, err_cap, "Error de lectura en %s", t->path);
                fclose(fbin);
                free(copy_buf);
                fclose(out);
                return 0;
            }
            fwrite(copy_buf, 1, rd, out);
            sha_update(&sha, copy_buf, rd);
            remaining_bytes -= rd;
        }
        fclose(fbin);

        for (int s = 0; s < t->postgap; s++) {
            if (t->is_data) {
                encode_zero_mode1_sector((t->end - t->postgap) + s, sector_buf);
            } else {
                memset(sector_buf, 0, RAW);
            }
            fwrite(sector_buf, 1, RAW, out);
            sha_update(&sha, sector_buf, RAW);
        }
    }

    free(copy_buf);

    uint8_t payload_hash[32];
    sha_final(&sha, payload_hash);

    // Escribir cabecera final SGCDIMG1 en offset 0
    fseek(out, 0, SEEK_SET);

    uint8_t header[96];
    memset(header, 0, sizeof(header));
    memcpy(header, "SGCDIMG\0", 8);

    uint32_t val32 = 1; // version
    memcpy(header + 8, &val32, 4);
    val32 = offset; // toc_offset
    memcpy(header + 12, &val32, 4);
    val32 = RAW; // sector_bytes
    memcpy(header + 16, &val32, 4);
    val32 = (uint32_t)num_tracks; // track_count
    memcpy(header + 20, &val32, 4);
    int32_t val_i32 = FIRST_LBA; // first_lba
    memcpy(header + 24, &val_i32, 4);
    val_i32 = leadout; // leadout
    memcpy(header + 28, &val_i32, 4);

    uint64_t val64 = offset; // payload_offset
    memcpy(header + 32, &val64, 8);
    val64 = payload_bytes; // payload_size
    memcpy(header + 40, &val64, 8);

    memcpy(header + 48, payload_hash, 32);

    fwrite(header, 1, sizeof(header), out);

    // Escribir entradas TOC
    for (int i = 0; i < num_tracks; i++) {
        CueTrack *t = &tracks[i];
        uint8_t entry[32];
        memset(entry, 0, sizeof(entry));

        val32 = (uint32_t)t->number;
        memcpy(entry + 0, &val32, 4);
        val32 = (uint32_t)t->is_data;
        memcpy(entry + 4, &val32, 4);
        val_i32 = (int32_t)t->index00;
        memcpy(entry + 8, &val_i32, 4);
        val_i32 = (int32_t)t->start;
        memcpy(entry + 12, &val_i32, 4);
        val_i32 = (int32_t)t->end;
        memcpy(entry + 16, &val_i32, 4);

        fwrite(entry, 1, sizeof(entry), out);
    }

    fflush(out);
    fclose(out);

    return 1;
}

int ensure_snatcher_cue_exists(const char *bin_path, char *out_cue_path, size_t cue_cap) {
    if (!bin_path || bin_path[0] == '\0') return 0;
    int64_t sz = get_file_size_bytes(bin_path);
    if (sz <= 0) return 0;

    // Obtener directorio y nombre base del .bin
    char dir[512] = { 0 };
    strncpy(dir, bin_path, sizeof(dir) - 1);
    char *last_slash = strrchr(dir, '/');
    char *last_bslash = strrchr(dir, '\\');
    char *slash = last_slash > last_bslash ? last_slash : last_bslash;
    char fname[256] = { 0 };
    if (slash) {
        strncpy(fname, slash + 1, sizeof(fname) - 1);
        *(slash + 1) = '\0';
    } else {
        strncpy(fname, bin_path, sizeof(fname) - 1);
        dir[0] = '\0';
    }

    // Ruta esperada del CUE
    char target_cue[512] = { 0 };
    char *dot = strrchr(fname, '.');
    if (dot) *dot = '\0';
    if (dir[0] != '\0') {
        snprintf(target_cue, sizeof(target_cue), "%s%s.cue", dir, fname);
    } else {
        snprintf(target_cue, sizeof(target_cue), "%s.cue", fname);
    }

    // Si ya existe .cue o .CUE, retornarlo
    if (get_file_size_bytes(target_cue) > 0) {
        strncpy(out_cue_path, target_cue, cue_cap - 1);
        return 1;
    }
    // Probar con extension mayuscula .CUE
    char target_cue_upper[512] = { 0 };
    if (dir[0] != '\0') {
        snprintf(target_cue_upper, sizeof(target_cue_upper), "%s%s.CUE", dir, fname);
    } else {
        snprintf(target_cue_upper, sizeof(target_cue_upper), "%s.CUE", fname);
    }
    if (get_file_size_bytes(target_cue_upper) > 0) {
        strncpy(out_cue_path, target_cue_upper, cue_cap - 1);
        return 1;
    }

    // Si el archivo bin es exactamente el tamano oficial de Snatcher Sega CD (625,192,176 bytes),
    // creamos el CUE de 21 pistas automaticamente
    if (sz == 625192176LL) {
        FILE *fc = fopen(target_cue, "w");
        if (fc) {
            fprintf(fc, "FILE \"%s.BIN\" BINARY\n", fname);
            fprintf(fc, "  TRACK 01 MODE1/2352\n    INDEX 01 00:00:00\n");
            fprintf(fc, "  TRACK 02 AUDIO\n    PREGAP 00:02:00\n    INDEX 01 12:28:64\n");
            fprintf(fc, "  TRACK 03 AUDIO\n    INDEX 01 12:35:34\n");
            fprintf(fc, "  TRACK 04 AUDIO\n    INDEX 01 14:50:29\n");
            fprintf(fc, "  TRACK 05 AUDIO\n    INDEX 01 19:24:34\n");
            fprintf(fc, "  TRACK 06 AUDIO\n    INDEX 01 19:45:39\n");
            fprintf(fc, "  TRACK 07 AUDIO\n    INDEX 01 20:57:56\n");
            fprintf(fc, "  TRACK 08 AUDIO\n    INDEX 01 23:44:33\n");
            fprintf(fc, "  TRACK 09 AUDIO\n    INDEX 01 27:18:73\n");
            fprintf(fc, "  TRACK 10 AUDIO\n    INDEX 01 28:46:26\n");
            fprintf(fc, "  TRACK 11 AUDIO\n    INDEX 01 30:55:32\n");
            fprintf(fc, "  TRACK 12 AUDIO\n    INDEX 01 32:44:05\n");
            fprintf(fc, "  TRACK 13 AUDIO\n    INDEX 01 37:13:58\n");
            fprintf(fc, "  TRACK 14 AUDIO\n    INDEX 01 39:08:55\n");
            fprintf(fc, "  TRACK 15 AUDIO\n    INDEX 01 40:30:47\n");
            fprintf(fc, "  TRACK 16 AUDIO\n    INDEX 01 41:48:55\n");
            fprintf(fc, "  TRACK 17 AUDIO\n    INDEX 01 42:05:67\n");
            fprintf(fc, "  TRACK 18 AUDIO\n    INDEX 01 43:44:66\n");
            fprintf(fc, "  TRACK 19 AUDIO\n    INDEX 01 44:32:01\n");
            fprintf(fc, "  TRACK 20 AUDIO\n    INDEX 01 51:34:48\n");
            fprintf(fc, "  TRACK 21 AUDIO\n    INDEX 01 52:07:58\n");
            fclose(fc);
            strncpy(out_cue_path, target_cue, cue_cap - 1);
            return 1;
        }
    }

    return 0;
}
