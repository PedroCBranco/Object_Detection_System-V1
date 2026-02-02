# Object Detection System V1 (ESP32 Sonar)

[![en](https://img.shields.io/badge/lang-en-red.svg)](#english-version)
[![pt](https://img.shields.io/badge/lang-pt-green.svg)](#versão-portuguesa)

---

<a name="english-version"></a>
## 🇬🇧 English Version

**Ultrasonic sonar system with dual-mode control (Auto Sweep + Manual Joystick) powered by ESP32.**

This project was developed as a self-learning initiative during my 1st year of Electrical and Computer Engineering at **Instituto Superior Técnico (IST)**, Lisbon.

### ⚙️ How it Works
The system mimics a radar/sonar station using an ultrasonic sensor mounted on a servo motor. It operates in two distinct modes:

1.  **Automatic Mode (Scanner):**
    * The servo sweeps continuously from 0º to 180º.
    * If an object is detected within a specific range, the system alerts via LEDs.
    * Uses non-blocking logic (`millis()`) to ensure smooth movement.

2.  **Manual Mode (Joystick):**
    * Triggered by pressing the joystick button.
    * The user takes full control of the sensor's position using the Joystick's X-axis.
    * Allows for precise focusing on a specific target.

### 🛠️ Hardware Stack
* **MCU:** ESP32 (DevKit V1)
* **Actuator:** SG90 Micro Servo
* **Sensor:** HC-SR04 Ultrasonic Sensor
* **Input:** Analog Joystick (XY Axis + Switch)
* **Output:** Status LEDs (Red/Blue)

### 💻 Key Technical Concepts
* **Non-blocking Code:** Implementation of `millis()` timers instead of `delay()` to multitask (blink LEDs while moving the servo).
* **State Machine Logic:** Seamless transition between "Auto" and "Manual" states.
* **Input Pullup:** Utilization of internal ESP32 resistors for clean digital readings.

---

<a name="versão-portuguesa"></a>
## 🇵🇹 Versão Portuguesa

**Sistema de radar ultrassónico com controlo híbrido (Varrimento Automático + Joystick) baseado em ESP32.**

Este projeto foi desenvolvido no âmbito de aprendizagem autónoma durante o meu 1.º ano de Engenharia Eletrotécnica e de Computadores no **Instituto Superior Técnico (IST)**.

### ⚙️ Funcionalidades
O sistema simula uma estação de radar/sonar. O código alterna entre dois modos de funcionamento:

1.  **Modo Automático (Varredura):**
    * O servo motor faz uma varredura contínua de 0º a 180º.
    * O sensor lê a distância em tempo real. Se detetar algo, ativa os alertas visuais (LEDs).
    * Utiliza lógica não-bloqueante (`millis`) para o movimento não travar durante a leitura.

2.  **Modo Manual (Joystick):**
    * Ativado ao pressionar o botão do joystick (interrupção lógica do ciclo).
    * O utilizador controla a rotação do servo manualmente.
    * Permite focar o sensor numa direção específica para medições de precisão.

### 🛠️ Lista de Material
* **Microcontrolador:** ESP32 (DevKit V1)
* **Atuador:** Servo Motor SG90
* **Sensor:** Ultrassónico HC-SR04
* **Input:** Joystick Analógico
* **Output:** LEDs de Estado (Vermelho e Azul)
