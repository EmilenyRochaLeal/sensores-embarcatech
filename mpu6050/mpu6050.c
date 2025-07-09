#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <math.h>


// I2C defines
#define I2C_PORT i2c0
#define I2C_SDA 0
#define I2C_SCL 1
#define MPU6050_ADDR 0x68 // endereço do mpu6050

#define M_PI 3.14159265358979323846


void inicializar_mpu6050() {
    uint8_t reset[2] = {0x6B, 0x00}; // Endereço do registrador Power Management 1
    i2c_write_blocking(i2c0, MPU6050_ADDR, reset, 2, false);
}

bool ler_acelerometro(int16_t *ax, int16_t *ay, int16_t *az) {
    uint8_t buffer[6];
    int status;

    status = i2c_write_blocking(i2c0, MPU6050_ADDR, (uint8_t[]){0x3B}, 1, true);
    if (status < 0) return false;

    status = i2c_read_blocking(i2c0, MPU6050_ADDR, buffer, 6, false);
    if (status < 6) return false;

    *ax = (buffer[0] << 8) | buffer[1];
    *ay = (buffer[2] << 8) | buffer[3];
    *az = (buffer[4] << 8) | buffer[5];

    return true;
}


float calcular_inclinacao(int16_t ax, int16_t ay, int16_t az) {
    float ax_g = ax / 16384.0; // Converte para g
    float ay_g = ay / 16384.0;
    float az_g = az / 16384.0;

    float inclinacao = atan2(ax_g, sqrt(ay_g * ay_g + az_g * az_g)) * (180.0 / M_PI);
    return inclinacao;
}

int main(){
    stdio_init_all();

    i2c_init(i2c0, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    inicializar_mpu6050();

    int16_t ax, ay, az;

    while (true) {
        ler_acelerometro(&ax, &ay, &az);
        float inclinacao = calcular_inclinacao(ax, ay, az);
        printf("Inclinação: %.2f graus\n", inclinacao);

    if (inclinacao > 30.0) {
        printf("Inclinação acima de 30°\n");
    } else if (inclinacao >= 15.0 && inclinacao <= 30.0) {
        printf("Inclinação entre 15° e 30°\n");
    } else  if (inclinacao < 15.0) {
        printf("Inclinação abaixo de 15°\n");
    }else {
        printf("Erro: sensor MPU6050 não encontrado!\n");
    }
        sleep_ms(500);
    }
}
