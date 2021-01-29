#include <MPU9250_asukiaaa.h>
 
#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

// See https://github.com/asukiaaa/MPU9250_asukiaaa
struct IMU {
  IMU(TwoWire* wire) : sensor_{MPU9250_ADDRESS_AD0_LOW} {
    sensor_.setWire(wire);
    sensor_.beginAccel();
    sensor_.beginMag();
    sensor_.beginGyro();
  }
  
  MPU9250_asukiaaa sensor_{MPU9250_ADDRESS_AD0_LOW};
  double acc_offset_[3];
  double acc_[3] = {1.2, 0.0, 2.2};

  double* acc() {
    sensor_.accelUpdate();
    acc_[0] = sensor_.accelX();
    acc_[1] = sensor_.accelY();
    acc_[2] = sensor_.accelZ();
    return acc_;
  }

  void calibrate() {
    double acum[3] = {0.0, 0.0, 0.0};
    const int iter = 100;
    for (int i = 0 ; i < iter ; ++i) {
      acc();
      acum[0] += acc_[0];
      acum[1] += acc_[1];
      acum[2] += acc_[2];
    }

    acc_offset_[0] = acum[0] / iter;
    acc_offset_[1] = acum[1] / iter;
    acc_offset_[2] = acum[2] / iter;
  }

  double* acc_adjusted() {
    acc();
    acc_[0] -= acc_offset_[0];
    acc_[1] -= acc_offset_[1];
    acc_[2] -= acc_offset_[2];
    return acc_;
  }

  double* acc_offset() {
    return acc_offset_;
  }
};

IMU* _sensor;
 
void setup() {
  while(!Serial);
   
  Serial.begin(115200);
   
  #ifdef _ESP32_HAL_I2C_H_   
  // for esp32
  Wire.begin(SDA_PIN, SCL_PIN); //sda, scl
  #else
  Wire.begin();
  #endif

  _sensor = new IMU{&Wire};
  _sensor->calibrate();
  //Serial.println("Finished Calibrating");
}
 
void loop() {
  auto acc = _sensor->acc_adjusted();
  Serial.println(String(acc[0]) + " " + String(acc[1]) + " " + String(acc[2]));
  delay(50);
}
