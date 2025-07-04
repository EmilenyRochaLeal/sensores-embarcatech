#include <stdio.h>
#include <string.h> 
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"

// LEDs - usando GPIO
#define LED_VERMELHO 13  // LED vermelho
#define LED_VERDE 11  // LED verde
#define LED_AZUL 12  // LED azul

// BH1750 - usando i2c0
#define I2C_BH1750_PORT i2c0
#define I2C_BH1750_SDA 0  // GP0
#define I2C_BH1750_SCL 1  // GP1

// Endereço do BH1750
#define BH1750_ADDR 0x23
#define BH1750_CMD_START 0x10  // Medição contínua, alta resolução

// Configuração PWM
const uint16_t periodo = 200;
const float divisor_pwm = 16.0;
const uint16_t stemp_pwm = 40;
uint8_t nivelLuminosidade = 0;
uint8_t contadorA = 0;

void config_pwm(int led) {
    uint slice;
    gpio_set_function(led, GPIO_FUNC_PWM);
    slice = pwm_gpio_to_slice_num(led);
    pwm_set_clkdiv(slice, divisor_pwm);
    pwm_set_wrap(slice, periodo);
    pwm_set_gpio_level(led, stemp_pwm);
    pwm_set_enabled(slice, true);
}

void bh1750_init() {
    uint8_t buf[1] = {BH1750_CMD_START};
    i2c_write_blocking(I2C_BH1750_PORT, BH1750_ADDR, buf, 1, false);
}

float bh1750_read_lux() {
    uint8_t data[2];
    int result = i2c_read_blocking(I2C_BH1750_PORT, BH1750_ADDR, data, 2, false);
    if (result != 2) {
        printf("Erro ao ler o sensor BH1750\n");
        return -1;
    }
    uint16_t raw = (data[0] << 8) | data[1];
    return raw / 1.2;
}

void atualizar_por_lux(float lux) {
    if (lux < 10) {
        printf("Escuro: %.1f lx\n", lux);
        pwm_set_gpio_level(LED_VERMELHO, 0);
        pwm_set_gpio_level(LED_VERDE, 0);
        pwm_set_gpio_level(LED_AZUL, 0);
    } 
    else if (lux >= 10 && lux < 50) {
        printf("lux baixa: %.1f lx\n", lux);
        pwm_set_gpio_level(LED_VERMELHO, periodo);
        pwm_set_gpio_level(LED_VERDE, 0);
        pwm_set_gpio_level(LED_AZUL, 0);
    } 
    else if (lux >= 50 && lux < 200) {
        printf("Iluminado: %.1f lx\n", lux);
        pwm_set_gpio_level(LED_VERMELHO,0);
        pwm_set_gpio_level(LED_VERDE, periodo);
        pwm_set_gpio_level(LED_AZUL, 0);
    } 
    else if (lux >= 200 && lux < 1000) {
        printf("Claro: %.1f lx\n", lux);
        pwm_set_gpio_level(LED_VERMELHO, 0);
        pwm_set_gpio_level(LED_VERDE, 0);
        pwm_set_gpio_level(LED_AZUL, periodo);
    } 
    else {
        printf("lux alta: %.1f lx\n", lux);
        pwm_set_gpio_level(LED_VERMELHO, periodo);
        pwm_set_gpio_level(LED_VERDE, periodo);
        pwm_set_gpio_level(LED_AZUL, periodo);
    }
}

int main() {
    // Inicializa UART para debug (opcional)
    stdio_init_all();

    // Inicializa I2C para o BH1750
    i2c_init(I2C_BH1750_PORT, 100 * 1000);
    gpio_set_function(I2C_BH1750_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_BH1750_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_BH1750_SDA);
    gpio_pull_up(I2C_BH1750_SCL);

    // Inicializa BH1750
    bh1750_init();

    // Configura LEDs PWM
    config_pwm(LED_VERMELHO);
    config_pwm(LED_VERDE);
    config_pwm(LED_AZUL);

    sleep_ms(2000);

    bool modo_automatico = true;

    while (true) {
        float lux = bh1750_read_lux();
        
        if (modo_automatico && lux >= 0) {
            atualizar_por_lux(lux);
        } else {
            printf("Manual: Nivel %d", nivelLuminosidade);
        }

        sleep_ms(100);  // Aguarda 1 segundo para a próxima leitura
    }

    return 0;
}
