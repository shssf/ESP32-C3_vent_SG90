#pragma once

#include <stdbool.h>

void servo_init(void);
void servo_close(void);
void servo_middle(void);
void servo_open(void);
void servo_set_angle(int angle_deg);

int servo_get_angle(void);

/** true when servo angle > 0 (vent open, green LED on). */
bool servo_is_vent_open(void);
