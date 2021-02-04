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
    off();
  }

  void on() { wiringPiI2CWrite(fd_, 1); }

  void off() { wiringPiI2CWrite(fd_, 0); }

private:
  static const short slave_address_ = 0x28;
  int fd_;
};

int main(int argc, char **argv) {
  Sensor s{};
  uint16_t delay = 200;

  if (argc > 1) {
    delay = std::stoi(argv[1]);
  }

  for (int i = 0; i < 10000000; ++i) {
    (i % 2 == 0) ? s.on() : s.off();
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }
}
