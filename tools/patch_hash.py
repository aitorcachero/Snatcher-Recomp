path = 'segagenesisrecomp/runner/cd/disc_image.c'
with open(path, 'rb') as f:
    data = f.read()

target = b'    if (!hash_payload(image->file, payload_offset, payload_size, digest)) {\r\n        set_error(error, capacity, "cannot read image payload"); goto fail;\r\n    }\r\n    if (memcmp(digest, image->digest, sizeof(digest)) != 0) { set_error(error, capacity, "payload SHA-256 mismatch"); goto fail; }'

replacement = b'#ifndef SEGACD_SKIP_PAYLOAD_HASH\r\n    if (!hash_payload(image->file, payload_offset, payload_size, digest)) {\r\n        set_error(error, capacity, "cannot read image payload"); goto fail;\r\n    }\r\n    if (memcmp(digest, image->digest, sizeof(digest)) != 0) { set_error(error, capacity, "payload SHA-256 mismatch"); goto fail; }\r\n#endif'

assert target in data, 'Target not found in disc_image.c'
data = data.replace(target, replacement, 1)

with open(path, 'wb') as f:
    f.write(data)
print('Successfully patched disc_image.c!')
