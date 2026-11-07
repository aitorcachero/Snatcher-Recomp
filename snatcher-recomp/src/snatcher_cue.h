#ifndef SNATCHER_CUE_H
#define SNATCHER_CUE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Convierte un archivo CUE/BIN de Sega CD a formato nativo SGCDIMG1 (.sgcd).
 * Retorna 1 si tuvo exito, 0 en caso de error (con mensaje en err_msg). */
int convert_cue_to_sgcd(const char *cue_path, const char *out_sgcd_path, char *err_msg, size_t err_cap);

/* Si solo existe SNATCHER.BIN sin archivo .cue, genera el CUE correspondiente de Snatcher Sega CD. */
int ensure_snatcher_cue_exists(const char *bin_path, char *out_cue_path, size_t cue_cap);

#ifdef __cplusplus
}
#endif

#endif // SNATCHER_CUE_H
