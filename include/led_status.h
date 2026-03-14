#pragma once

#include <stdbool.h>

void led_status_init(void);

/** Set vent state: true = open (green ON, red OFF), false = closed (green OFF, red ON). */
void led_set_vent_open(bool open);
