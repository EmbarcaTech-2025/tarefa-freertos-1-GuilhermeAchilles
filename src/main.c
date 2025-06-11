#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "buzzer.h"
#include "button.h"

// Declarar os handles
TaskHandle_t handle_changeColor = NULL;
TaskHandle_t handle_playBuzzer = NULL;

void changeColor_task(void *params) {
    while (1) {
        led_on(11);
        vTaskDelay(pdMS_TO_TICKS(500));
        led_off(11);
        led_on(12);
        vTaskDelay(pdMS_TO_TICKS(500));
        led_off(12);
        led_on(13);
        vTaskDelay(pdMS_TO_TICKS(500));
        led_off(13);
    }
}

void playBuzzer_task(void *params) {
    while (1) {
        play_buzzer(4096);
        vTaskDelay(pdMS_TO_TICKS(500));
        play_buzzer(0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void buttonInterrupt_task(void *params) {
    while (1) {
        if (!gpio_get(5)) {
            vTaskSuspend(handle_changeColor);
        } else {
            vTaskResume(handle_changeColor);
        }

        if (!gpio_get(6)) {
            vTaskSuspend(handle_playBuzzer);
        } else {
            vTaskResume(handle_playBuzzer);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

int main() {
    stdio_init_all();
    init_led();
    init_buttons();
    pwm_init_buzzer();


    xTaskCreate(changeColor_task, "Blink", 256, NULL, 2, &handle_changeColor);
    xTaskCreate(playBuzzer_task, "Play", 256, NULL, 2, &handle_playBuzzer);
    xTaskCreate(buttonInterrupt_task, "Buttons", 256, NULL, 1, NULL);

    vTaskStartScheduler();
    while (true) {}
}
