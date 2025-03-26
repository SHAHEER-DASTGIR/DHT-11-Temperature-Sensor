#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "dht11.h"
#define DHT_GPIO GPIO_NUM_4  // Change to the GPIO pin you are using
void dht_test(void *pvParameter) {
    ESP_LOGI("DHT", "Starting DHT11 Sensor Readings");

    while (1) {
        int16_t temperature = 0, humidity = 0;
        esp_err_t result = dht_read_data(DHT_TYPE_DHT11, DHT_GPIO, &humidity, &temperature);

        if (result == ESP_OK) {
            printf("Temperature: %d.%d°C\n", temperature / 10, temperature % 10);
            printf("Humidity: %d.%d%%\n", humidity / 10, humidity % 10);
        } else {
            ESP_LOGE("DHT", "Failed to read sensor data");
        }

        vTaskDelay(pdMS_TO_TICKS(2000));  // Delay 2 seconds before the next read
    }
}
void app_main(void) {
    xTaskCreate(&dht_test, "dht_test", 2048, NULL, 5, NULL);  
}
