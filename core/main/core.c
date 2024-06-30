#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSconfig.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

void delay_MS(unsigned t){
  TickType_t currentTick = xTaskGetTickCount();
  while ((xTaskGetTickCount() - currentTick) < pdMS_TO_TICKS(t));
}

void Task_Print1(void * param) {
    while (1){
        printf("TASK 1\n");  
        delay_MS(1000);
  }
}

void Task_Print2(void * param) {
    while (1){
        printf("TASK 2\n");  
        delay_MS(1000);
  }
}

void app_main() {
    esp_task_wdt_deinit();
    xTaskCreatePinnedToCore(Task_Print1, "Task1", 2048, NULL, 2, &TaskHandle_1, 1);
    xTaskCreatePinnedToCore(Task_Print2, "Task2", 2048, NULL, 1, &TaskHandle_2, 0);
}
