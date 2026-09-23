#include <driver/i2s.h>

#define I2S_NUM I2S_NUM_0
#define SAMPLE_RATE 44100
#define BITS_PER_SAMPLE I2S_BITS_PER_SAMPLE_16BIT

void setup_i2s_master() {
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = BITS_PER_SAMPLE,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = true
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = 26,   // Bit Clock connected to Nodes 2 & 3
        .ws_io_num = 25,    // Word Select (LRCLK) connected to Nodes 2 & 3
        .data_out_num = 22, // Serial Data Out connected to Nodes 2 & 3
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM, &pin_config);
}

void setup() {
    Serial.begin(115200);
    setup_i2s_master();
}

void loop() {
    // Generate or ingest PCM audio samples (e.g., sine wave test or incoming audio buffer)
    int16_t sampleBuffer[64];
    size_t bytesWritten = 0;

    // Fill buffer with audio data...
    
    // Broadcast synchronously over I2S to Node 2 and Node 3 hardware pins
    i2s_write(I2S_NUM, sampleBuffer, sizeof(sampleBuffer), &bytesWritten, portMAX_DELAY);
}
