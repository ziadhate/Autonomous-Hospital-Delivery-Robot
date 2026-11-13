
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "can_protocol.h"
#include "can_messages.h"

/**
 * @brief Test positive velocity command encoding and decoding.
 */
static void test_positive_velocity(void)
{
    can_velocity_command_t tx = {
        .linear_velocity_mm_s = 500,
        .angular_velocity_mrad_s = 1000,
        .sequence = 1U,
        .flags = CAN_VELOCITY_FLAG_ENABLE
    };

    can_velocity_command_t rx;
    can_frame_t frame = {0};

    assert(can_encode_velocity_command(&tx, &frame) == CAN_PROTOCOL_OK);
    assert(frame.id == CAN_MSG_ID_VELOCITY_COMMAND);
    assert(frame.dlc == 8U);

    assert(can_decode_velocity_command(&frame, &rx) == CAN_PROTOCOL_OK);

    assert(rx.linear_velocity_mm_s == tx.linear_velocity_mm_s);
    assert(rx.angular_velocity_mrad_s == tx.angular_velocity_mrad_s);
    assert(rx.sequence == tx.sequence);
    assert(rx.flags == tx.flags);

    printf("[PASS] Positive velocity encode/decode\n");
}

/**
 * @brief Test negative velocity command encoding and decoding.
 */
static void test_negative_velocity(void)
{
    can_velocity_command_t tx = {
        .linear_velocity_mm_s = -500,
        .angular_velocity_mrad_s = -1000,
        .sequence = 2U,
        .flags = CAN_VELOCITY_FLAG_ENABLE
    };

    can_velocity_command_t rx;
    can_frame_t frame = {0};

    assert(can_encode_velocity_command(&tx, &frame) == CAN_PROTOCOL_OK);

    assert(can_decode_velocity_command(&frame, &rx) == CAN_PROTOCOL_OK);

    assert(rx.linear_velocity_mm_s == tx.linear_velocity_mm_s);
    assert(rx.angular_velocity_mrad_s == tx.angular_velocity_mrad_s);
    assert(rx.sequence == tx.sequence);
    assert(rx.flags == tx.flags);

    printf("[PASS] Negative velocity encode/decode\n");
}

/**
 * @brief Test Raspberry Pi heartbeat using CAN ID 0x110.
 */
static void test_pi_heartbeat(void)
{
    can_heartbeat_t tx = {
        .node_state = 1U,
        .protocol_major = 1U,
        .protocol_minor = 0U,
        .sequence = 10U,
        .uptime_ms = 123456U
    };

    can_heartbeat_t rx;
    can_frame_t frame = {0};

    assert(
        can_encode_heartbeat(
            CAN_MSG_ID_PI_HEARTBEAT,
            &tx,
            &frame
        ) == CAN_PROTOCOL_OK
    );

    assert(frame.id == CAN_MSG_ID_PI_HEARTBEAT);
    assert(frame.dlc == 8U);

    assert(can_decode_heartbeat(&frame, &rx) == CAN_PROTOCOL_OK);

    assert(rx.node_state == tx.node_state);
    assert(rx.protocol_major == tx.protocol_major);
    assert(rx.protocol_minor == tx.protocol_minor);
    assert(rx.sequence == tx.sequence);
    assert(rx.uptime_ms == tx.uptime_ms);

    printf("[PASS] Raspberry Pi heartbeat encode/decode\n");
}

/**
 * @brief Test STM32 heartbeat using CAN ID 0x111.
 */
static void test_stm32_heartbeat(void)
{
    can_heartbeat_t tx = {
        .node_state = 2U,
        .protocol_major = 1U,
        .protocol_minor = 0U,
        .sequence = 20U,
        .uptime_ms = 987654U
    };

    can_heartbeat_t rx;
    can_frame_t frame = {0};

    assert(
        can_encode_heartbeat(
            CAN_MSG_ID_STM32_HEARTBEAT,
            &tx,
            &frame
        ) == CAN_PROTOCOL_OK
    );

    assert(frame.id == CAN_MSG_ID_STM32_HEARTBEAT);
    assert(frame.dlc == 8U);

    assert(can_decode_heartbeat(&frame, &rx) == CAN_PROTOCOL_OK);

    assert(rx.node_state == tx.node_state);
    assert(rx.protocol_major == tx.protocol_major);
    assert(rx.protocol_minor == tx.protocol_minor);
    assert(rx.sequence == tx.sequence);
    assert(rx.uptime_ms == tx.uptime_ms);

    printf("[PASS] STM32 heartbeat encode/decode\n");
}

/**
 * @brief Test invalid CAN frame rejection.
 */
static void test_invalid_frames(void)
{
    can_frame_t frame = {0};

    /* Unknown message ID */
    frame.id = 0x200U;
    frame.dlc = 8U;

    assert(
        can_protocol_validate_frame(&frame) ==
        CAN_PROTOCOL_ERROR_UNKNOWN_MESSAGE
    );

    /* Invalid DLC */
    frame.id = CAN_MSG_ID_VELOCITY_COMMAND;
    frame.dlc = 7U;

    assert(
        can_protocol_validate_frame(&frame) ==
        CAN_PROTOCOL_ERROR_INVALID_DLC
    );

    /* Invalid reserved byte */
    can_velocity_command_t rx;

    frame.id = CAN_MSG_ID_VELOCITY_COMMAND;
    frame.dlc = 8U;
    frame.data[5] = 0U;
    frame.data[6] = 0x01U;
    frame.data[7] = 0U;

    assert(
        can_decode_velocity_command(&frame, &rx) ==
        CAN_PROTOCOL_ERROR_INVALID_DATA
    );

    printf("[PASS] Invalid frame rejection\n");
}

int main(void)
{
    test_positive_velocity();
    test_negative_velocity();
    test_pi_heartbeat();
    test_stm32_heartbeat();
    test_invalid_frames();

    printf("\nAll CAN message tests passed.\n");

    return 0;
}
