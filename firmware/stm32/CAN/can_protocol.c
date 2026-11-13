#include "can_protocol.h"
#include "can_messages.h"

/**
 * @brief Validate a received CAN frame.
 *
 * Checks:
 * - NULL pointer
 * - Standard 11-bit CAN identifier
 * - Valid Classical CAN payload length
 * - Known message identifier
 * - Expected payload length
 *
 * @param frame Pointer to the CAN frame.
 * @return CAN protocol validation status.
 */
can_protocol_status_t can_protocol_validate_frame(
    const can_frame_t *frame
)
{
    if (frame == 0)
    {
        return CAN_PROTOCOL_ERROR_NULL;
    }

    /* Check standard 11-bit CAN identifier */
    if (frame->id > CAN_PROTOCOL_STANDARD_ID_MAX)
    {
        return CAN_PROTOCOL_ERROR_INVALID_ID;
    }

    /* Classical CAN supports up to 8 data bytes */
    if (frame->dlc > CAN_PROTOCOL_MAX_DLC)
    {
        return CAN_PROTOCOL_ERROR_INVALID_DLC;
    }

    /* Validate known message identifiers */
    switch (frame->id)
    {
        case CAN_MSG_ID_SAFETY_STATUS:
        case CAN_MSG_ID_VELOCITY_COMMAND:
        case CAN_MSG_ID_CONTROL_COMMAND:
        case CAN_MSG_ID_PI_HEARTBEAT:
        case CAN_MSG_ID_STM32_HEARTBEAT:
        case CAN_MSG_ID_MOTOR_FEEDBACK:
        case CAN_MSG_ID_BATTERY_STATUS:
        case CAN_MSG_ID_FAULT_STATUS:
        case CAN_MSG_ID_ROBOT_STATUS:

            if (frame->dlc != CAN_PROTOCOL_MAX_DLC)
            {
                return CAN_PROTOCOL_ERROR_INVALID_DLC;
            }

            break;

        default:
            return CAN_PROTOCOL_ERROR_UNKNOWN_MESSAGE;
    }

    return CAN_PROTOCOL_OK;
}
