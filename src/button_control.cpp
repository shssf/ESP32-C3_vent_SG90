#include <driver/gpio.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "button_control.h"
#include "led_status.h"
#include "servo_control.h"
#include "utils.h"

static const char* TAG = "button";

#define BUTTON_GPIO       GPIO_NUM_3
#define VENT_OPEN_ANGLE   90
#define VENT_CLOSED_ANGLE 0

static void button_task(void* arg)
{
  bool vent_open = false;
  bool last_btn = true; /* idle = high (pull-up) */

  /* Start in CLOSED state */
  servo_set_angle(VENT_CLOSED_ANGLE);
  led_set_open(false);
  led_set_closed(true);

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
          servo_set_angle(VENT_OPEN_ANGLE);
          led_set_open(true);
          led_set_closed(false);
        }
        else
        {
          servo_set_angle(VENT_CLOSED_ANGLE);
          led_set_open(false);
          led_set_closed(true);
        }
        ESP_LOGI(TAG, "Vent %s (%d deg)", vent_open ? "OPEN" : "CLOSED", vent_open ? VENT_OPEN_ANGLE : VENT_CLOSED_ANGLE);
      }
    }
    last_btn = btn;
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

void button_control_init(void)
{
  /* Init sub-devices first */
  led_status_init();
  servo_init();

  gpio_config_t btn_cfg = {};
  btn_cfg.pin_bit_mask = (1ULL << BUTTON_GPIO);
  btn_cfg.mode = GPIO_MODE_INPUT;
  btn_cfg.pull_up_en = GPIO_PULLUP_ENABLE;
  btn_cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;
  btn_cfg.intr_type = GPIO_INTR_DISABLE;
  gpio_config(&btn_cfg);

  CHECK_XTASK_OK(xTaskCreate(button_task, "button_task", 2048, NULL, 5, NULL));
  ESP_LOGI(TAG, "Button init on GPIO%d", BUTTON_GPIO);
}
