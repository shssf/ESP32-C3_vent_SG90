#pragma once

#include <stdbool.h>

void servo_init(void);
void servo_set_angle(int angle_deg);

int servo_get_angle(void);
