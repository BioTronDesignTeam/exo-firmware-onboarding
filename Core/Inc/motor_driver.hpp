#ifndef MOTOR_DRIVER_HPP
#define MOTOR_DRIVER_HPP

#include "main.h"
#include <cstdint>

class MotorDriver {
public:
    explicit MotorDriver(CAN_HandleTypeDef* hcan, uint8_t node_id);

    bool init();

    /* ---------------- TX Commands ---------------- */

    bool setAxisState(uint32_t state);

    bool setControllerMode(uint32_t control_mode,
                           uint32_t input_mode);

    bool setInputVelocity(float velocity,
                          float torque_ff = 0.0f);

    bool setInputTorque(float torque);

    /* ---------------- RX Getters ---------------- */

    bool processFrame(const CAN_RxHeaderTypeDef& header,
                      const uint8_t data[8]);

    float getPosition() const;
    float getVelocity() const;
    float getTorqueEstimate() const;
    float getBusVoltage() const;

private:
    CAN_HandleTypeDef* hcan_;
    uint8_t node_id_;

    /* Cached motor state */
    float position_;
    float velocity_;
    float torque_estimate_;
    float bus_voltage_;

    /* Low-level CAN helpers */
    uint32_t makeCanId(uint8_t command_id);

    bool transmitFrame(uint32_t can_id,
                       const uint8_t data[8]);

    /* -------- Serialization Helpers -------- */

    void serializeFloat(float value, uint8_t* buffer);
    float deserializeFloat(const uint8_t* buffer);

    /* -------- RX Parsing Helpers -------- */

    void parseEncoderEstimates(const uint8_t data[8]);
    void parseBusVoltageCurrent(const uint8_t data[8]);
    void parseTorques(const uint8_t data[8]);
};

#endif
