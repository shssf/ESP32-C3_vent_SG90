#pragma once

#include <esp_err.h>
#include <esp_log.h>

void log_print(const char* tag, const char* expr, const char* function_name, const char* detail_fmt, ...);

#define CHECK_ERR(expr)                                                                                                                    \
  do                                                                                                                                       \
  {                                                                                                                                        \
    esp_err_t err = (expr);                                                                                                                \
    if (err != ESP_OK)                                                                                                                     \
    {                                                                                                                                      \
      log_print(TAG, #expr, __FUNCTION__, "%s (%d)", esp_err_to_name(err), err);                                                           \
    }                                                                                                                                      \
  } while (0)

#define CHECK_ERR_RETURN(expr)                                                                                                             \
  do                                                                                                                                       \
  {                                                                                                                                        \
    esp_err_t err = (expr);                                                                                                                \
    if (err != ESP_OK)                                                                                                                     \
    {                                                                                                                                      \
      log_print(TAG, #expr, __FUNCTION__, "%s (%d)", esp_err_to_name(err), err);                                                           \
      return;                                                                                                                              \
    }                                                                                                                                      \
  } while (0)

#define CHECK_ERR_RETURN_VAL(expr, ret_val)                                                                                                \
  do                                                                                                                                       \
  {                                                                                                                                        \
    esp_err_t err = (expr);                                                                                                                \
    if (err != ESP_OK)                                                                                                                     \
    {                                                                                                                                      \
      log_print(TAG, #expr, __FUNCTION__, "%s (%d)", esp_err_to_name(err), err);                                                           \
      return (ret_val);                                                                                                                    \
    }                                                                                                                                      \
  } while (0)

#define CHECK_ERR_XTASK(expr)                                                                                                              \
  do                                                                                                                                       \
  {                                                                                                                                        \
    BaseType_t _st = (expr);                                                                                                               \
    if (_st != pdPASS)                                                                                                                     \
    {                                                                                                                                      \
      log_print(TAG, #expr, __FUNCTION__, "BaseType_t=%ld", (long)_st);                                                                    \
    }                                                                                                                                      \
  } while (0)
