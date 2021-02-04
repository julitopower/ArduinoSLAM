CXX_FLAGS=-std=c++17
CXX_LD_FLAGS=-lwiringPi -lstdc++
all: i2c led

i2c: i2ctest.cpp
  $(CC) $(CXX_FLAGS) $(CXX_LD_FLAGS) i2ctest.cpp  -o i2c

led: led_i2c.cpp
  $(CC) $(CXX_FLAGS) $(CXX_LD_FLAGS) led_i2c.cpp  -o led
