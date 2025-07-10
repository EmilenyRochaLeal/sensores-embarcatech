#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// ======= Configuração do I2C e Sensor VL53L0X =======
#include "vl53l0x_api.h"

#define I2C_PORT i2c0
#define SDA_PIN 0
#define SCL_PIN 1
#define VL53L0X_DEFAULT_ADDRESS 0x29

VL53L0X_Dev_t dev;
VL53L0X_DEV dev_ptr = &dev;

// ======= Configuração do Buzzer PWM =======
#define BUZZER_PIN 21
#define BUZZER_FREQUENCY 100

void pwm_init_buzzer(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096));
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 0); // Desliga buzzer inicialmente
}

void beep(uint pin, uint duration_ms) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_gpio_level(pin, 2048); // Duty cycle de 50%
    sleep_ms(duration_ms);
    pwm_set_gpio_level(pin, 0);
}

// ======= Inicialização do I2C VL53L0X =======
void i2c_init_vl53l0x() {
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

int main() {
    stdio_init_all();
    sleep_ms(2000);

    printf("Iniciando VL53L0X...\n");

    i2c_init_vl53l0x();
    pwm_init_buzzer(BUZZER_PIN); // Inicializa buzzer PWM

    dev_ptr->I2cDevAddr = VL53L0X_DEFAULT_ADDRESS;
    dev_ptr->comms_type = 1;
    dev_ptr->comms_speed_khz = 400;

    int status = VL53L0X_DataInit(dev_ptr);
    if (status) {
        printf("Erro na inicialização do VL53L0X: %d\n", status);
        return -1;
    }

    printf("VL53L0X inicializado com sucesso!\n");

    status = VL53L0X_StartMeasurement(dev_ptr);
    if (status) {
        printf("Erro ao iniciar medição: %d\n", status);
        return -1;
    }

    while (true) {
        VL53L0X_RangingMeasurementData_t measurement;
        status = VL53L0X_PerformSingleRangingMeasurement(dev_ptr, &measurement);
        if (status == 0) {
            uint16_t mm = measurement.RangeMilliMeter;

            if (mm >= 8190) {
                printf("Distância: Fora de alcance\n");
            } else if (mm < 100) {
                float cm = mm / 10.0f;
                float m = mm / 1000.0f;
                printf(">>> ALERTA: Objeto detectado a %.1f cm (%.2f m)\n", cm, m);
                beep(BUZZER_PIN, 500); // Toca o buzzer por 500ms
            } else {
                float cm = mm / 10.0f;
                float m = mm / 1000.0f;
                printf("Distância: %5d mm | %5.1f cm | %4.2f m\n", mm, cm, m);
            }
        } else {
            printf("Erro ao medir distância: %d\n", status);
        }

        sleep_ms(500);
    }
}
