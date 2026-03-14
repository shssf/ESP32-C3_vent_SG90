#include <driver/gpio.h>
#include <esp_log.h>

#include "led_status.h"
#include "utils.h"

static const char* TAG = "led_status";

#define LED_OPEN_GPIO   GPIO_NUM_5 /* green */
#define LED_CLOSED_GPIO GPIO_NUM_6 /* red   */

void led_status_init(void)
{
  gpio_config_t io = {};
  io.pin_bit_mask = (1ULL << LED_OPEN_GPIO) | (1ULL << LED_CLOSED_GPIO);
  io.mode = GPIO_MODE_OUTPUT;
  io.pull_up_en = GPIO_PULLUP_DISABLE;
  io.pull_down_en = GPIO_PULLDOWN_DISABLE;
  io.intr_type = GPIO_INTR_DISABLE;
  CHECK_ERR(gpio_config(&io));

  CHECK_ERR(gpio_set_level(LED_OPEN_GPIO, 0));
  CHECK_ERR(gpio_set_level(LED_CLOSED_GPIO, 0));
  ESP_LOGI(TAG, "LEDs init: OPEN=GPIO%d, CLOSED=GPIO%d", LED_OPEN_GPIO, LED_CLOSED_GPIO);
}

void led_set_vent_open(bool open)
{
  CHECK_ERR(gpio_set_level(LED_OPEN_GPIO, open ? 1 : 0));
  CHECK_ERR(gpio_set_level(LED_CLOSED_GPIO, open ? 0 : 1));
}
