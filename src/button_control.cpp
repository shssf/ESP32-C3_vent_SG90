#include <driver/gpio.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "button_control.h"
#include "servo_control.h"
#include "utils.h"

static const char* TAG = "button";

#define BUTTON_GPIO GPIO_NUM_3

static void button_task(void* arg)
{
  bool vent_open = false;
  bool last_btn = true; /* idle = high (pull-up) */

  /* Start in CLOSED state */
  servo_close();

  for (;;)
  {
    bool btn = gpio_get_level(BUTTON_GPIO);
    if (last_btn && !btn) /* falling edge = press */
    {
      vTaskDelay(pdMS_TO_TICKS(50)); /* debounce */
      btn = gpio_get_level(BUTTON_GPIO);
      if (!btn)
      {
        vent_open = !vent_open;
        if (vent_open)
        {
          servo_open();
        }
        else
        {
          servo_close();
        }
        ESP_LOGI(TAG, "Vent %s (%d deg)", vent_open ? "OPEN" : "CLOSED", servo_get_angle());
      }
    }
    last_btn = btn;
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

void button_control_init(void)
{
  /* Init sub-devices first */
  servo_init();

  gpio_config_t btn_cfg = {};
  btn_cfg.pin_bit_mask = (1ULL << BUTTON_GPIO);
  btn_cfg.mode = GPIO_MODE_INPUT;
  btn_cfg.pull_up_en = GPIO_PULLUP_ENABLE;
  btn_cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;
  btn_cfg.intr_type = GPIO_INTR_DISABLE;
  CHECK_ERR(gpio_config(&btn_cfg));

  CHECK_ERR_XTASK(xTaskCreate(button_task, "button_task", 2048, NULL, 5, NULL));
  ESP_LOGI(TAG, "Button init on GPIO%d", BUTTON_GPIO);
}
