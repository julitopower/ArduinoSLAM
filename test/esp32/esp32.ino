#include <MPU9250_asukiaaa.h>

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

// See https://github.com/asukiaaa/MPU9250_asukiaaa
class IMU {
private:
  // Sensor object exposed by the library we use under the hood */
  MPU9250_asukiaaa sensor_{MPU9250_ADDRESS_AD0_LOW};
  /*! Acceleration offsets buffer as [x, y, z] */
  double acc_offset_[3];
  /*! Acceleration values buffer as [x, y, z] */
  double acc_[3] = {1.2, 0.0, 2.2};

public:
  IMU(TwoWire *wire) : sensor_{MPU9250_ADDRESS_AD0_LOW} {
    sensor_.setWire(wire);
    sensor_.beginAccel();
    sensor_.beginMag();
    sensor_.beginGyro();
  }

  /*! \brief Read acceleration values from the sensor
   *
   *  \return Pointer to buffer with the values as [x, y, z]
   */
  double *acc() {
    sensor_.accelUpdate();
    acc_[0] = sensor_.accelX();
    acc_[1] = sensor_.accelY();
    acc_[2] = sensor_.accelZ();
    return acc_;
  }

  /*! \brief Calibrate X,Y,Z acceleration at rest and aligned to the groud
   *
   *  X, Y acceleration should be 0.0
   *  Z acceleration should be 1.0
   */
  void calibrate() {
    double acum[3] = {0.0, 0.0, 0.0};
    const int iter = 100;
    for (int i = 0; i < iter; ++i) {
      acc();
      acum[0] += acc_[0];       // X
      acum[1] += acc_[1];       // Y
      acum[2] += (acc_[2] - 1); // Z
    }

    acc_offset_[0] = acum[0] / iter;
    acc_offset_[1] = acum[1] / iter;
    acc_offset_[2] = acum[2] / iter;
  }

  /*! \brief Get the offset adjusted accelerations
   *
   *  This method first reads acceleration values from the
   *  sensor, and then simply substract the offsets calculated
   *  during calibration
   *
   *  \return Pointer to buffer with adjusted accelerations as [x, y, z]
   */
  double *acc_adjusted() {
    acc();
    acc_[0] -= acc_offset_[0];
    acc_[1] -= acc_offset_[1];
    acc_[2] -= acc_offset_[2];
    return acc_;
  }

  double *acc_offset() { return acc_offset_; }
};

// Arduino Forces us to declare variables and objects that need to be visible
// accross setup/loop as globals
IMU *sensor;

void setup() {
  // Initialize Serial communication
  while (!Serial)
    ;
  Serial.begin(115200);

// Code works with ESP32 and Arduino
#ifdef _ESP32_HAL_I2C_H_
  // for esp32
  Wire.begin(SDA_PIN, SCL_PIN); // sda, scl
#else
  Wire.begin();
#endif

  sensor = new IMU{&Wire};
  sensor->calibrate();
}

void loop() {
  auto acc = sensor->acc_adjusted();
  Serial.println(String(acc[0]) + " " + String(acc[1]) + " " + String(acc[2]));
  delay(50);
}
