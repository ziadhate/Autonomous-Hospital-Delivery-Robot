#include "can_messages.h"

/* Write a 16-bit value in Little Endian format */
static void write_u16_le(uint8_t *dst, uint16_t value)
{
    dst[0] = (uint8_t)(value & 0xFFU);
    dst[1] = (uint8_t)(value >> 8U);
}

/* Read a 16-bit value in Little Endian format */
static uint16_t read_u16_le(const uint8_t *src)
{
    return (uint16_t)(
        (uint16_t)src[0] |
        ((uint16_t)src[1] << 8U)
    );
}

/* Write a 32-bit value in Little Endian format */
static void write_u32_le(uint8_t *dst, uint32_t value)
{
    dst[0] = (uint8_t)value;
    dst[1] = (uint8_t)(value >> 8U);
    dst[2] = (uint8_t)(value >> 16U);
    dst[3] = (uint8_t)(value >> 24U);
}

/* Read a 32-bit value in Little Endian format */
static uint32_t read_u32_le(const uint8_t *src)
{
    return (uint32_t)src[0] |
           ((uint32_t)src[1] << 8U) |
           ((uint32_t)src[2] << 16U) |
           ((uint32_t)src[3] << 24U);
}

/* Convert signed 16-bit data to its wire representation */
static uint16_t encode_i16(int16_t value)
{
    return (uint16_t)value;
}

/* Decode signed 16-bit data */
static int16_t decode_i16(uint16_t value)
{
    int32_t signed_value = (int32_t)value;

    if (value >= 0x8000U)
    {
        signed_value -= 65536;
    }

    return (int16_t)signed_value;
}

/**
 * @brief Encode a velocity command into a CAN frame.
 *
 * CAN ID: 0x100
 * DLC: 8 bytes
 *
 * Data layout:
 * Byte 0-1: Linear velocity (mm/s)
 * Byte 2-3: Angular velocity (mrad/s)
 * Byte 4:   Sequence number
 * Byte 5:   Flags
 * Byte 6-7: Reserved
 */
can_protocol_status_t can_encode_velocity_command(
    const can_velocity_command_t *message,
    can_frame_t *frame
)
{
    if ((message == 0) || (frame == 0))
    {
        return CAN_PROTOCOL_ERROR_NULL;
    }

    if ((message->flags &
         (uint8_t)~CAN_VELOCITY_FLAG_ENABLE) != 0U)
    {
        return CAN_PROTOCOL_ERROR_INVALID_DATA;
    }

    frame->id = CAN_MSG_ID_VELOCITY_COMMAND;
    frame->dlc = 8U;

    write_u16_le(
        &frame->data[0],
        encode_i16(message->linear_velocity_mm_s)
    );

    write_u16_le(
        &frame->data[2],
        encode_i16(message->angular_velocity_mrad_s)
    );

    frame->data[4] = message->sequence;
    frame->data[5] = message->flags;

    /* Reserved bytes must always be zero */
    frame->data[6] = 0U;
    frame->data[7] = 0U;

    return CAN_PROTOCOL_OK;
}

/**
 * @brief Decode a CAN frame into a velocity command.
 */
can_protocol_status_t can_decode_velocity_command(
    const can_frame_t *frame,
    can_velocity_command_t *message
)
{
    can_protocol_status_t status;

    if ((frame == 0) || (message == 0))
    {
        return CAN_PROTOCOL_ERROR_NULL;
    }

    status = can_protocol_validate_frame(frame);

    if (status != CAN_PROTOCOL_OK)
    {
        return status;
    }

    if (frame->id != CAN_MSG_ID_VELOCITY_COMMAND)
    {
        return CAN_PROTOCOL_ERROR_UNKNOWN_MESSAGE;
    }

    if ((frame->data[5] &
         (uint8_t)~CAN_VELOCITY_FLAG_ENABLE) != 0U)
    {
        return CAN_PROTOCOL_ERROR_INVALID_DATA;
    }

    if ((frame->data[6] != 0U) || (frame->data[7] != 0U))
    {
        return CAN_PROTOCOL_ERROR_INVALID_DATA;
    }

    message->linear_velocity_mm_s =
        decode_i16(read_u16_le(&frame->data[0]));

    message->angular_velocity_mrad_s =
        decode_i16(read_u16_le(&frame->data[2]));

    message->sequence = frame->data[4];
    message->flags = frame->data[5];

    return CAN_PROTOCOL_OK;
}

/**
 * @brief Encode a heartbeat message into a CAN frame.
 *
 * Supports:
 * - Raspberry Pi heartbeat: 0x110
 * - STM32 heartbeat:       0x111
 *
 * Data layout:
 * Byte 0:   Node state
 * Byte 1:   Protocol major version
 * Byte 2:   Protocol minor version
 * Byte 3:   Sequence number
 * Byte 4-7: Uptime in milliseconds
 */
can_protocol_status_t can_encode_heartbeat(
    uint16_t message_id,
    const can_heartbeat_t *message,
    can_frame_t *frame
)
{
    if ((message == 0) || (frame == 0))
    {
        return CAN_PROTOCOL_ERROR_NULL;
    }

    if ((message_id != CAN_MSG_ID_PI_HEARTBEAT) &&
        (message_id != CAN_MSG_ID_STM32_HEARTBEAT))
    {
        return CAN_PROTOCOL_ERROR_INVALID_ID;
    }

    frame->id = message_id;
    frame->dlc = 8U;

    frame->data[0] = message->node_state;
    frame->data[1] = message->protocol_major;
    frame->data[2] = message->protocol_minor;
    frame->data[3] = message->sequence;

    write_u32_le(&frame->data[4], message->uptime_ms);

    return CAN_PROTOCOL_OK;
}

/**
 * @brief Decode a heartbeat CAN frame.
 */
can_protocol_status_t can_decode_heartbeat(
    const can_frame_t *frame,
    can_heartbeat_t *message
)
{
    can_protocol_status_t status;

    if ((frame == 0) || (message == 0))
    {
        return CAN_PROTOCOL_ERROR_NULL;
    }

    status = can_protocol_validate_frame(frame);

    if (status != CAN_PROTOCOL_OK)
    {
        return status;
    }

    if ((frame->id != CAN_MSG_ID_PI_HEARTBEAT) &&
        (frame->id != CAN_MSG_ID_STM32_HEARTBEAT))
    {
        return CAN_PROTOCOL_ERROR_UNKNOWN_MESSAGE;
    }

    message->node_state = frame->data[0];
    message->protocol_major = frame->data[1];
    message->protocol_minor = frame->data[2];
    message->sequence = frame->data[3];
    message->uptime_ms = read_u32_le(&frame->data[4]);

    return CAN_PROTOCOL_OK;
}
