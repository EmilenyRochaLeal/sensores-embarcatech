# sensores-embarcatech
Repositório para prática de sensores para a residência de sistemas embarcados `EmbarcaTech`. Nele há diversos projetos desenvolvidos com a placa **RP2040 (BitDogLab)** utilizando sensores conectados via I2C. 

Cada pasta representa um projeto independente, com seu próprio código-fonte, estrutura e documentação.

## 📁 Estrutura dos Projetos

- [`BH1750`](./BH1750): Sensor de luminosidade. Mede a intensidade da luz e aciona LEDs com base no nível detectado.
- [`AHT10`](./AHT10): Sensor de temperatura e umidade. Exibe os dados no serial monitor e emite alertas em caso de condições ambientais críticas.
- [`MPU6050`](./MPU6050): Sensor de aceleração e giroscópio. Calcula a inclinação do dispositivo e informa alertas com base nos ângulos medidos via serial monitor.
- [`VL53L0X`](./VL53L0X): Sensor de distância a laser. Detecta objetos próximos e emite alertas via serial e buzzer quando a distância é crítica também via serial monitor

---

## 📜 Licença

Todos os direitos reservados © 2025 [Emileny Rocha Leal](https://github.com/EmilenyRochaLeal)  
