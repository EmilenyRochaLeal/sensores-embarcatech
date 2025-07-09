#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// I2C defines
#define I2C_PORT i2c0
#define I2C_SDA 0
#define I2C_SCL 1
#define AHT10_ADDR 0x38 // AHT10 I2C address


// Inicializa o AHT10
void aht10_init() {
    uint8_t init_cmd[] = {0xE1, 0x08, 0x00};
    i2c_write_blocking(I2C_PORT, 0x38, init_cmd, 3, false);
    sleep_ms(20);
}

// Lê temperatura (°C) e umidade (%) do AHT10
bool aht10_read(float *temperatura, float *umidade) {
    uint8_t trigger_cmd[] = {0xAC, 0x33, 0x00};
    uint8_t data[6];

    i2c_write_blocking(I2C_PORT, 0x38, trigger_cmd, 3, false);
    sleep_ms(80);  // tempo de medição recomendado

    int res = i2c_read_blocking(I2C_PORT, 0x38, data, 6, false);
    if (res != 6) return false;

    uint32_t raw_humi = ((data[1] << 16) | (data[2] << 8) | data[3]) >> 4;
    uint32_t raw_temp = ((data[3] & 0x0F) << 16) | (data[4] << 8) | data[5];

    *umidade = ((float)raw_humi * 100) / 1048576;
    *temperatura = (((float)raw_temp * 200) / 1048576) - 50;

    return true;
}


int main(){
    stdio_init_all();
    sleep_ms(1000); // Aguarda serial estabilizar

    
    // Inicializa I2C
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    aht10_init();


    while (true) {
        float temp, umi;
        bool ok = aht10_read(&temp, &umi);


    if (ok) {
        printf("Temp: %.2f °C | Umid: %.2f %%\n", temp, umi);

        if (temp < 20.0 || umi > 70.0) {
            printf(" Alerta: Condição ambiental crítica!\n");
        }
    } else {
        printf("Erro ao ler o sensor AHT10\n");
    }

        sleep_ms(2000);
    }

    return 0;
};