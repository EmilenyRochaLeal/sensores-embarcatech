# 📏 Medição de Distância com Raspberry Pi Pico e VL53L0X

Este projeto utiliza o microcontrolador **Raspberry Pi Pico W** (via plataforma **BitDogLab**) e o sensor de distância **VL53L0X** para realizar medições em **milímetros (mm)**, **centímetros (cm)** e **metros (m)**. Quando um objeto é detectado a menos de **10 cm**, um **buzzer é ativado** com um beep sonoro. Os resultados são exibidos via console serial.

---

## 🛠️ Funcionalidades

✅ Inicializa o sensor **VL53L0X** via comunicação I2C  
✅ Realiza medições de distância a cada 500 ms  
✅ Converte automaticamente os valores de **milímetros**, **centímetros** e **metros**  
✅ Indica quando o objeto está **fora do alcance** do sensor (acima de ~2 metros)  
✅ Ativa **buzzer via PWM** quando um objeto está a menos de **10 cm**  

---

## ⚙️ Requisitos

* [Raspberry Pi Pico W (BitDogLab)](https://www.raspberrypi.com/products/raspberry-pi-pico/)
* Sensor **VL53L0X** (Time-of-Flight da STMicroelectronics)
* **Buzzer passivo** conectado ao GPIO 21 (PWM)
* Cabo micro-USB para programação
* [Pico SDK](https://github.com/raspberrypi/pico-sdk) configurado no seu ambiente
* Ferramentas de build:

  * `cmake`
  * `arm-none-eabi-gcc`
  * `ninja` (opcional)

---

## 📦 Conexões

### Sensor VL53L0X

| VL53L0X Pin | Raspberry Pi Pico Pin |
| ----------- | --------------------- |
| SDA         | GP0 (I2C0 SDA)        |
| SCL         | GP1 (I2C0 SCL)        |
| VIN         | 3V3 (OUT)             |
| GND         | GND                   |

> 📝 *Use resistores pull-up de 4.7kΩ nos pinos SDA e SCL, caso o módulo não os tenha embutidos.*

### Buzzer Passivo

| Buzzer Pin | Raspberry Pi Pico Pin |
| ---------- | --------------------- |
| +          | GP21 (PWM)            |
| -          | GND                   |

---

## 🔔 Comportamento do Alerta

Quando um objeto é detectado a menos de **10 cm**, o sistema:

- Emite um **beep PWM de 500 ms** usando o buzzer conectado ao pino GP21.
- Exibe uma mensagem no console:  
  `>>> ALERTA: Objeto detectado a X cm (Y m)`

---

## 🧑‍💻 Como Compilar e Executar

1. Clone este repositório:

   ```bash
   git clone https://github.com/seu-usuario/projeto-vl53l0x-pico.git
   cd projeto-vl53l0x-pico
