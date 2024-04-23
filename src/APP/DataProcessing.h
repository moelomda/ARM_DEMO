#include "DataCollect.h"


typedef enum {
    DECODE_NO_ERROR,
    DECODE_INVALID_START_END_BYTES,
    DECODE_CHECKSUM_MISMATCH
} DecodeErrorStatus_t;
u8 calculate_checksum(uint8_t data);
void encode_buffer(uint8_t data, uint8_t *buffer);
DecodeErrorStatus_t decode_buffer(uint8_t *buffer, uint8_t *data);
