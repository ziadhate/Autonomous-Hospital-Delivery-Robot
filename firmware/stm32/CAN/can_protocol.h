#ifndef CAN_PROTOCOL_H
#define CAN_PROTOCOL_H

#include <stdint.h>

#define CAN_PROTOCOL_MAX_DLC       8U
#define CAN_PROTOCOL_STANDARD_ID_MAX 0x7FFU

typedef struct
{
    uint16_t id;
    uint8_t dlc;
    uint8_t data[CAN_PROTOCOL_MAX_DLC];
} can_frame_t;

typedef enum
{
    CAN_PROTOCOL_OK = 0,
    CAN_PROTOCOL_ERROR_NULL,
    CAN_PROTOCOL_ERROR_INVALID_ID,
    CAN_PROTOCOL_ERROR_INVALID_DLC,
    CAN_PROTOCOL_ERROR_UNKNOWN_MESSAGE,
    CAN_PROTOCOL_ERROR_INVALID_DATA
} can_protocol_status_t;

can_protocol_status_t can_protocol_validate_frame(
    const can_frame_t *frame
);

#endif
