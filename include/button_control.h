#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Initialise pushbutton on GPIO3 (D1) and start the polling task.
 *  The task toggles vent OPEN/CLOSED and drives servo + LEDs accordingly. */
void button_control_init(void);

#ifdef __cplusplus
}
#endif
