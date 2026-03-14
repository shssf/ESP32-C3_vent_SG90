#include <cstdarg>
#include <cstdio>
#include <esp_log.h>

#include "utils.h"

void log_print(const char* tag, const char* expr, const char* function_name, const char* detail_fmt, ...)
{
  char detail[96];
  va_list args;
  va_start(args, detail_fmt);
  vsnprintf(detail, sizeof(detail), detail_fmt, args);
  va_end(args);

  ESP_LOGE(tag, "ERROR: %s failed: %s in %s", expr, detail, function_name);
}
