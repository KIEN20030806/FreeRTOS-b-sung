#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/FreeRTOSConfig.h>
#include "esp_task_wdt.h"

int i=0;

// Đảm bảo rằng configUSE_TIME_SLICING được đặt thành 0 trong FreeRTOSConfig.h

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

void delay_MS(unsigned t) {
    TickType_t currentTick = xTaskGetTickCount();
    while ((xTaskGetTickCount() - currentTick) < pdMS_TO_TICKS(t)) {        
    }
}

void Task_Print1(void *param) {
    (void)param;
    while (1) {
        printf("TASK 1\n");
        delay_MS(1000);
        i++;
        if(i==5){
            vTaskDelay(3000/portTICK_PERIOD_MS);
            i=0;
        }
    }
}

void Task_Print2(void *param) {
    (void)param;
    while (1) {
        printf("TASK 2\n");
        delay_MS(1000);
    }
}

void app_main() {
    esp_task_wdt_deinit();
    xTaskCreate(Task_Print1, "Task1", 2048, NULL, 1, &TaskHandle_1); // Độ ưu tiên 1
    xTaskCreate(Task_Print2, "Task2", 2048, NULL, 1, &TaskHandle_2); // Độ ưu tiên 1
}