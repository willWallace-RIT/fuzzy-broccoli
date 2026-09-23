#include <driver/i2s.h>
#include "esp_a2dp_api.h"

#define I2S_NUM I2S_NUM_0
#define SAMPLE_RATE 44100

void setup_i2s_slave() {
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_SLAVE | I2S_MODE_RX),
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = 26,   // Tied to Node 1 BCK
        .ws_io_num = 25,    // Tied to Node 1 WS
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = 22   // Tied to Node 1 Data Out
    };

    i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM, &pin_config);
}

void setup() {
    Serial.begin(115200);
    setup_i2s_slave();
    // Initialize Bluetooth A2DP Source stack and connect to target headset here...
}

void loop() {
    int16_t inputBuffer[64];
    size_t bytesRead = 0;

    // Read incoming synchronized PCM frames from Node 1 via I2S
    i2s_read(I2S_NUM, inputBuffer, sizeof(inputBuffer), &bytesRead, portMAX_DELAY);

    if (bytesRead > 0) {
        // Pass PCM chunk directly into the Bluetooth A2DP source data callback buffer
        // esp_a2d_media_write((uint8_t*)inputBuffer, bytesRead);
    }
}
