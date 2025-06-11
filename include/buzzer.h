#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

void pwm_init_buzzer();
void play_buzzer(int pwm);


#endif // BUZZER_H
