#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSconfig.h"
#include "esp_task_wdt.h"

void delay_MS(unsigned t){
  TickType_t currentTick = xTaskGetTickCount();
  while ((xTaskGetTickCount() - currentTick) < pdMS_TO_TICKS(t))
  {
  }
}

void vTask1()
{
    while (1)
    {
        printf("Task 1\n");
        delay_MS(1000);
    }   
}

void vTask2()
{
    while (1)
    {
        printf("Task 2\n");
        delay_MS(1000);
    }  
}

void app_main(void)
{
    esp_task_wdt_deinit();
    xTaskCreatePinnedToCore(vTask1,"Task1", 4096, NULL, 1,  NULL, 1);  
    delay_MS(5000);
    xTaskCreatePinnedToCore(vTask2,"Task2", 4096, NULL, 2,  NULL, 1);       
}