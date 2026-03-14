#pragma once

#include <stdbool.h>

void led_status_init(void);

void led_set_open(bool on);
void led_set_closed(bool on);

bool led_get_open(void);
bool led_get_closed(void);
