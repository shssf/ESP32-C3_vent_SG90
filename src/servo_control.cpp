#include <driver/ledc.h>
#include <esp_log.h>

#include "led_status.h"
#include "servo_control.h"
#include "utils.h"

static const char* TAG = "servo";

/* SG90 typical pulse widths: 500 µs (0°) → 2400 µs (180°).
   LEDC timer: 50 Hz, 14-bit resolution → period = 20 ms = 16384 ticks.
   duty = pulse_us / 20000 * 16384                                      */

#define SERVO_GPIO      GPIO_NUM_4
#define LEDC_TIMER      LEDC_TIMER_0
#define LEDC_CHANNEL    LEDC_CHANNEL_0
#define LEDC_RESOLUTION LEDC_TIMER_14_BIT /* 16384 */
#define LEDC_FREQ_HZ    50
#define PULSE_MIN_US    500
#define PULSE_MAX_US    2400
#define DUTY_MAX        ((1 << 14) - 1) /* 16383 */

static int s_angle = 0;
static bool s_initialized = false;

static uint32_t angle_to_duty(int angle)
{
  if (angle < 0)
  {
    angle = 0;
  }
  if (angle > 180)
  {
    angle = 180;
  }
  uint32_t pulse_us = PULSE_MIN_US + (uint32_t)((PULSE_MAX_US - PULSE_MIN_US) * angle / 180);
  return (uint32_t)((uint64_t)pulse_us * DUTY_MAX / 20000ULL);
}

void servo_init(void)
{
  if (s_initialized)
  {
    return;
  }

  led_status_init();

  ledc_timer_config_t timer_cfg = {};
  timer_cfg.speed_mode = LEDC_LOW_SPEED_MODE;
  timer_cfg.timer_num = LEDC_TIMER;
  timer_cfg.duty_resolution = LEDC_RESOLUTION;
  timer_cfg.freq_hz = LEDC_FREQ_HZ;
  timer_cfg.clk_cfg = LEDC_AUTO_CLK;
  esp_err_t err = ledc_timer_config(&timer_cfg);
  if (err != ESP_OK)
  {
    ESP_LOGE(TAG, "LEDC timer init failed: %s (%d)", esp_err_to_name(err), (int)err);
    return;
  }

  ledc_channel_config_t ch_cfg = {};
  ch_cfg.speed_mode = LEDC_LOW_SPEED_MODE;
  ch_cfg.channel = LEDC_CHANNEL;
  ch_cfg.timer_sel = LEDC_TIMER;
  ch_cfg.intr_type = LEDC_INTR_DISABLE;
  ch_cfg.gpio_num = SERVO_GPIO;
  ch_cfg.duty = angle_to_duty(0);
  ch_cfg.hpoint = 0;
  err = ledc_channel_config(&ch_cfg);
  if (err != ESP_OK)
  {
    ESP_LOGE(TAG, "LEDC channel init failed: %s (%d)", esp_err_to_name(err), (int)err);
    return;
  }

  s_angle = 0;
  s_initialized = true;
  ESP_LOGI(TAG, "Servo init on GPIO%d, 0 deg", SERVO_GPIO);
}

void servo_set_angle(int angle_deg)
{
  if (!s_initialized)
  {
    servo_init();
    if (!s_initialized)
    {
      ESP_LOGE(TAG, "Servo set aborted: LEDC init did not complete");
      return;
    }
  }

  if (angle_deg < 0)
  {
    angle_deg = 0;
  }
  if (angle_deg > 180)
  {
    angle_deg = 180;
  }
  s_angle = angle_deg;

  uint32_t duty = angle_to_duty(angle_deg);
  CHECK_ERR(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL, duty));
  CHECK_ERR(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL));
  led_set_vent_open(angle_deg > 0);
  ESP_LOGI(TAG, "Servo -> %d deg (duty %lu)", angle_deg, (unsigned long)duty);
}

bool servo_is_vent_open(void)
{
  return s_angle > 0;
}

int servo_get_angle(void)
{
  return s_angle;
}
