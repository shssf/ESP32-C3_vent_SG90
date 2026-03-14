#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "led_status.h"
#include "servo_control.h"
#include "web_server.h"

// ---------- JSON helpers (minimal set for /status) ----------
static void json_escape_append(std::string& out, const char* s)
{
  if (s == NULL)
  {
    out += "null";
    return;
  }
  out.push_back('"');
  for (const unsigned char* p = (const unsigned char*)s; *p != '\0'; ++p)
  {
    unsigned char c = *p;
    if (c == '"')
      out += "\\\"";
    else if (c == '\\')
      out += "\\\\";
    else if (c < 0x20)
    {
      char buf[7];
      (void)snprintf(buf, sizeof(buf), "\\u%04X", (unsigned)c);
      out += buf;
    }
    else
      out.push_back((char)c);
  }
  out.push_back('"');
}

static void json_append_kv_str(std::string& out, const char* key, const char* val, bool last)
{
  out.push_back('"');
  out += key;
  out += "\":";
  json_escape_append(out, val);
  if (!last)
    out.push_back(',');
}

static void json_append_kv_num_i(std::string& out, const char* key, long long val, bool last)
{
  out.push_back('"');
  out += key;
  out += "\":";
  char buf[32];
  (void)snprintf(buf, sizeof(buf), "%lld", val);
  out += buf;
  if (!last)
    out.push_back(',');
}

// ---------- HTTP handlers ----------
static void handle_control_page()
{
  extern const uint8_t ctl_start[] asm("_binary_control_page_html_start");
  extern const uint8_t ctl_end[] asm("_binary_control_page_html_end");
  const size_t size = ctl_end - ctl_start;
  web_send_binary(200, "text/html; charset=utf-8", ctl_start, size);
}

static void handle_status()
{
  std::string j;
  j.reserve(256);
  j.push_back('{');
  json_append_kv_num_i(j, "servo_angle", (long long)servo_get_angle(), false);
  json_append_kv_str(j, "led_open", led_get_open() ? "on" : "off", false);
  json_append_kv_str(j, "led_closed", led_get_closed() ? "on" : "off", true);
  j.push_back('}');
  web_send(200, "application/json; charset=utf-8", j.c_str());
}

static void handle_servo_post()
{
  char buf[64] = {};
  int r = web_recv(buf, sizeof(buf) - 1);
  if (r <= 0)
  {
    web_send(400, "text/plain", "empty body");
    return;
  }
  buf[r] = '\0';

  /* Expect {"angle":NNN} — minimal parse */
  const char* p = strstr(buf, "\"angle\"");
  if (!p)
  {
    web_send(400, "text/plain", "missing angle");
    return;
  }
  p += 7; /* skip '"angle"' */
  while (*p == ' ' || *p == ':')
    ++p;
  int angle = atoi(p);
  if (angle < 0)
    angle = 0;
  if (angle > 180)
    angle = 180;

  servo_set_angle(angle);

  /* Update LEDs to reflect new position */
  if (angle > 0)
  {
    led_set_open(true);
    led_set_closed(false);
  }
  else
  {
    led_set_open(false);
    led_set_closed(true);
  }

  char resp[64];
  snprintf(resp, sizeof(resp), "{\"angle\":%d}", angle);
  web_send(200, "application/json", resp);
}

void control_register_web_route_handlers()
{
  web_register_get("/control", handle_control_page);
  web_register_get("/status", handle_status);
  web_register_post("/servo", handle_servo_post);
}
