#include <chrono>
#include <errno.h>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <wiringPiI2C.h>

class Sensor {
public:
  Sensor() {
    fd_ = wiringPiI2CSetup(slave_address_);
    // Configure the mcu 9250
    wiringPiI2CWriteReg8(fd_, 0x1c, res_2g_);
  }

  void read() {
    // Base register for the accelerometer readings. We need to read
    // 6 registers
    // https://invensense.tdk.com/download-pdf/mpu-9250-register-map/
    // -------------------------------------------------------
    // | byte-5 | byte-4 | byte-3 | byte-2 | byte-1 | byte-0 |
    // | X-high | X-low  | Y-high | Y-low  | Z-high | Z-low  |
    // -------------------------------------------------------
    const int reg = 0x3b;
    for (auto j = 0; j < 6; ++j) {
      acc_buffer_[6 - j - 1] = wiringPiI2CReadReg8(fd_, reg + j);
    }
  }

  std::string str() {
    std::stringstream ss{};
    for (auto k = 0; k < 3; ++k) {
      ss << *((short *)(acc_buffer_ + (k * 2))) / 16384.0 << " ";
    }
    return ss.str();
  }

private:
  // i2c slave address of 9250
  static const short slave_address_ = 0x68;
  // Config value to set 9250 accelerometer range to 2g
  static const short res_2g_ = 0x00;
  unsigned char acc_buffer_[6];
  unsigned char acc_offset_buffer_[6];
  int fd_;
};

int main() {
  Sensor s{};

  for (int i = 0; i < 10000000; ++i) {
    s.read();
    std::cout << s.str() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
}
