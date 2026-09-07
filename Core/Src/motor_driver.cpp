#include "motor_driver.hpp"
#include <cstring>

MotorDriver::MotorDriver(CAN_HandleTypeDef* hcan,
                         uint8_t node_id)
    : hcan_(hcan),
      node_id_(node_id),
      position_(0.0f),
      velocity_(0.0f),
      torque_estimate_(0.0f),
      bus_voltage_(0.0f) {}

bool MotorDriver::init()
{
    /* Start CAN peripheral */
    HAL_CAN_Start(hcan_);

    /* Enable RX FIFO interrupt */
    HAL_CAN_ActivateNotification(
        hcan_,
        CAN_IT_RX_FIFO0_MSG_PENDING);

    return true;
}

/* =======================================================
 *                 Low-Level CAN Helpers
 * ===================================================== */

uint32_t MotorDriver::makeCanId(uint8_t command_id)
{
    // TODO:
    // Construct the ODrive CAN ID using the node ID
    // and command ID from the CAN protocol.
    return 0;
}

bool MotorDriver::transmitFrame(uint32_t can_id,
                                const uint8_t data[8])
{
    CAN_TxHeaderTypeDef header;

    header.StdId = can_id;
    header.IDE = CAN_ID_STD;
    header.RTR = CAN_RTR_DATA;
    header.DLC = 8;
    header.TransmitGlobalTime = DISABLE;

    uint32_t mailbox;

    return HAL_CAN_AddTxMessage(
        hcan_,
        &header,
        const_cast<uint8_t*>(data),
        &mailbox
    ) == HAL_OK;
}

/* =======================================================
 *                    TX Commands
 * ===================================================== */

bool MotorDriver::setAxisState(uint32_t state)
{
    uint8_t payload[8] = {0};

    // TODO:
    // Serialize axis state into payload.
    // Determine the correct command ID.

    uint32_t can_id = makeCanId(/* TODO */);

    return transmitFrame(can_id, payload);
}

bool MotorDriver::setControllerMode(uint32_t control_mode,
                                    uint32_t input_mode)
{
    uint8_t payload[8] = {0};

    // TODO:
    // Serialize controller mode and input mode.

    uint32_t can_id = makeCanId(/* TODO */);

    return transmitFrame(can_id, payload);
}

bool MotorDriver::setInputVelocity(float velocity,
                                   float torque_ff)
{
    uint8_t payload[8] = {0};

    // TODO:
    // Bytes 0-3 -> velocity
    // Bytes 4-7 -> torque feedforward

    uint32_t can_id = makeCanId(/* TODO */);

    return transmitFrame(can_id, payload);
}

bool MotorDriver::setInputTorque(float torque)
{
    uint8_t payload[8] = {0};

    // TODO:
    // Serialize torque into payload.

    uint32_t can_id = makeCanId(/* TODO */);

    return transmitFrame(can_id, payload);
}

/* =======================================================
 *                  RX Message Dispatcher
 * ===================================================== */

bool MotorDriver::processFrame(const CAN_RxHeaderTypeDef& header,
                               const uint8_t data[8])
{
    // TODO:
    // Determine the command ID from header.StdId.
    // Dispatch to the appropriate parser.

    return false;
}

/* =======================================================
 *                   RX Parsers
 * ===================================================== */

void MotorDriver::parseEncoderEstimates(const uint8_t data[8])
{
    // TODO:
    // Position  -> bytes 0-3
    // Velocity  -> bytes 4-7

    position_ = 0.0f;
    velocity_ = 0.0f;
}

void MotorDriver::parseBusVoltageCurrent(const uint8_t data[8])
{
    // TODO:
    // Bus voltage -> bytes 0-3
    // Bus current -> bytes 4-7

    bus_voltage_ = 0.0f;
}

void MotorDriver::parseTorques(const uint8_t data[8])
{
    // TODO:
    // Target torque
    // Estimated torque

    torque_estimate_ = 0.0f;
}

/* =======================================================
 *             Serialization / Deserialization
 * ===================================================== */

void MotorDriver::serializeFloat(float value,
                                 uint8_t* buffer)
{
    // TODO:
    // Serialize a float into 4 bytes.
}

float MotorDriver::deserializeFloat(const uint8_t* buffer)
{
    // TODO:
    // Deserialize 4 bytes into a float.
    return 0.0f;
}

/* =======================================================
 *                    Cached Getters
 * ===================================================== */

float MotorDriver::getPosition() const
{
    return position_;
}

float MotorDriver::getVelocity() const
{
    return velocity_;
}

float MotorDriver::getTorqueEstimate() const
{
    return torque_estimate_;
}

float MotorDriver::getBusVoltage() const
{
    return bus_voltage_;
}
