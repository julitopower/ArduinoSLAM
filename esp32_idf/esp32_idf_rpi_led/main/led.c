#include "driver/gpio.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// I2C declarations
////////////////////////////////////////////////////////////////////////////////
static esp_err_t i2c_slave_init(void);

#define I2C_SLAVE_NUM 1
#define BLINK_GPIO GPIO_NUM_32
#define DELAY 10

void app_main(void) {
  if (i2c_slave_init() != ESP_OK) {
    printf("Error \n");
  } else {
    printf("I2C initialization correct\n");
  }

  // Input buffer, just one byte with the on/off command
  // This memory never gets released, since there is currently
  // no way to stop the application
  uint8_t *i_buffer = (uint8_t *)malloc(1);
  // Set the pin that controls the led in gpio mode for output
  gpio_pad_select_gpio(BLINK_GPIO);
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
  
  while (1) {
    // Check for commands from the i2c master
    int size = i2c_slave_read_buffer(I2C_SLAVE_NUM, i_buffer, 1,
                                     100 / portTICK_RATE_MS);

    if (size == 1) {
      /* Set the led state according to the command */
      gpio_set_level(BLINK_GPIO, *i_buffer);
    }

    // Wait a bit, to avoid busy waiting
    vTaskDelay(DELAY / portTICK_PERIOD_MS);
  }
}

/**
 * @brief i2c slave initialization
 */
static esp_err_t i2c_slave_init(void) {
  // By convention we use 0 as master and 1 as salve
  int i2c_slave_port = I2C_SLAVE_NUM;
  i2c_config_t conf_slave;
  conf_slave.sda_io_num = GPIO_NUM_4;
  conf_slave.sda_pullup_en = GPIO_PULLUP_ENABLE;
  conf_slave.scl_io_num = GPIO_NUM_5;
  conf_slave.scl_pullup_en = GPIO_PULLUP_ENABLE;
  conf_slave.mode = I2C_MODE_SLAVE;
  conf_slave.slave.addr_10bit_en = 0;
  conf_slave.slave.slave_addr = 0x28;
  i2c_param_config(i2c_slave_port, &conf_slave);
  return i2c_driver_install(i2c_slave_port, conf_slave.mode, 128, 128, 0);
}
