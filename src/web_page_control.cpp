#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

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
  j += "\"vent_open\":";
  j += servo_is_vent_open() ? "true" : "false";
  j.push_back('}');
  web_send(200, "application/json; charset=utf-8", j.c_str());
}

static void send_servo_state()
{
  char resp[64];
  snprintf(resp, sizeof(resp), "{\"angle\":%d}", servo_get_angle());
  web_send(200, "application/json", resp);
}

static void handle_servo_close_post()
{
  servo_close();
  send_servo_state();
}

static void handle_servo_middle_post()
{
  servo_middle();
  send_servo_state();
}

static void handle_servo_open_post()
{
  servo_open();
  send_servo_state();
}

void control_register_web_route_handlers()
{
  web_register_get("/control", handle_control_page);
  web_register_get("/status", handle_status);
  web_register_post("/servo/close", handle_servo_close_post);
  web_register_post("/servo/middle", handle_servo_middle_post);
  web_register_post("/servo/open", handle_servo_open_post);
}
