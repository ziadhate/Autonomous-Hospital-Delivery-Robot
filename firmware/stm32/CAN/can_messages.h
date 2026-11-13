#ifndef CAN_MESSAGES_H
#define CAN_MESSAGES_H

#include <stdint.h>
#include "can_protocol.h"

/* CAN Message IDs */
#define CAN_MSG_ID_SAFETY_STATUS    0x080U
#define CAN_MSG_ID_VELOCITY_COMMAND 0x100U
#define CAN_MSG_ID_CONTROL_COMMAND  0x101U
#define CAN_MSG_ID_PI_HEARTBEAT     0x110U
#define CAN_MSG_ID_STM32_HEARTBEAT  0x111U
#define CAN_MSG_ID_MOTOR_FEEDBACK   0x180U
#define CAN_MSG_ID_BATTERY_STATUS   0x181U
#define CAN_MSG_ID_FAULT_STATUS     0x182U
#define CAN_MSG_ID_ROBOT_STATUS     0x183U

/* Velocity command flags */
#define CAN_VELOCITY_FLAG_ENABLE (1U << 0)

/**
 * @brief Velocity command message.
 */
typedef struct
{
    int16_t linear_velocity_mm_s;
    int16_t angular_velocity_mrad_s;
    uint8_t sequence;
    uint8_t flags;
} can_velocity_command_t;

/**
 * @brief Node heartbeat message.
 */
typedef struct
{
    uint8_t node_state;
    uint8_t protocol_major;
    uint8_t protocol_minor;
    uint8_t sequence;
    uint32_t uptime_ms;
} can_heartbeat_t;

/**
 * @brief Motor feedback message.
 *
 * All velocity values are in mm/s.
 * Encoder values represent count differences.
 */
typedef struct
{
    int16_t left_velocity_mm_s;
    int16_t right_velocity_mm_s;
    int16_t left_encoder_delta;
    int16_t right_encoder_delta;
} can_motor_feedback_t;

/* Velocity command API */
can_protocol_status_t can_encode_velocity_command(
    const can_velocity_command_t *message,
    can_frame_t *frame
);

can_protocol_status_t can_decode_velocity_command(
    const can_frame_t *frame,
    can_velocity_command_t *message
);

/* Heartbeat API */
can_protocol_status_t can_encode_heartbeat(
    uint16_t message_id,
    const can_heartbeat_t *message,
    can_frame_t *frame
);

can_protocol_status_t can_decode_heartbeat(
    const can_frame_t *frame,
    can_heartbeat_t *message
);

/* Motor feedback API */
can_protocol_status_t can_encode_motor_feedback(
    const can_motor_feedback_t *message,
    can_frame_t *frame
);

can_protocol_status_t can_decode_motor_feedback(
    const can_frame_t *frame,
    can_motor_feedback_t *message
);

#endif
