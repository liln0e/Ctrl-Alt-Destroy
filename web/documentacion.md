---
layout: page
title: Documentación
---

# Deseño mecánico e de hardware

## Estrutura xeral
- **Dúas rodas motrices** (esquerda e dereita) con motores DC e reductora.
- **Un rodízio libre** dianteiro ou traseiro para estabilidade.
- **Chasis plano** en dúas plantas:
  - **Inferior:** sensores e batería.
  - **Superior:** electrónica de control.

## Dimensións orientativas
- **Largo:** ~16 cm
- **Ancho:** ~12 cm
- **Altura:** ~6 cm
- **Distancia entre rodas:** 9–11 cm
- **Altura sensores-chan:** 1–1,5 cm

## Sensores
- Barra con **5 sensores infravermellos** (ex. TCRT5000) colocados en liña na parte dianteira.
- Separación entre sensores: **1 cm aprox.**
- Colocación centrada respecto ao eixe do robot.

## Materiais recomendados
- **Chasis:** acrílico, aluminio lixeiro ou impreso en 3D.
- **Motores:** micromotores DC con caixa reductora (relación 1:30–1:50).
- **Rodas:** diámetro 6–7 cm, goma antiescorregadiza.
- **Rodízio:** pequeno (1–1.5").
- **Batería:** LiPo 2S (7,4 V) ou pack 4×AA NiMH.
- **Separadores e parafusos M3** para montar en dúas plantas.

## Montaxe básica
1. Fixar os **motores** en paralelo nas laterais do chasis.
2. Colocar a **barra de sensores** na parte dianteira, a 1–1,5 cm do chan.
3. Instalar o **rodízio** centrado (dianteiro ou traseiro).
4. Situar a **batería** no centro inferior para baixar o centro de gravidade.
5. Montar a **placa de control** na parte superior con separadores.


## Esquema simple (vista superior)
<pre>
┌───────────────────────────┐
│     Sensores IR (5x)      │
│   [S1][S2][S3][S4][S5]    │
│                           │
│    Placa controladora     │
│                           │
[Roda L]Motor   Motor[Roda R]
│                           │
│     Batería no centro     │
└───────────-───────────────┘
</pre>

# Deseño electrónico

## Obxectivo
Placa compacta que aloxa:
- Un **ESP32** como MCU/Wi-Fi/Bluetooth.
- Control de **2 motores DC** (driver dual).
- Lectura de até **5 sensores IR** reflectivos.
- Xestión de **alimentación** desde LiPo / pack AA.
- Conectores para batería, motores, sensores e programación.

## Dimensións recomendadas
- **PCB:** ~70 × 50 mm (axustable segundo o chasis).
- **Capas:** 2 (suficiente para prototipo).


## Elementos principais (BOM orientativa)
- 1 × Módulo/IC **ESP32-WROOM**.
- 1 × Driver motores dual: **TB6612FNG** ou **DRV8833** (recomendado TB6612 para até ~1.2 A por canal).
- 1 × Regulador buck 5V (por exemplo MP1584) ou conversor LDO 5V si prefires sinxelo.
- 5 × Sensores IR (conector JST ou pin header).
- 2 × Terminal block ou pines para motores (2 polos cada un).
- 1 × Conector para batería (JST-SM ou pad para cable).
- 1 × Diode para protección de inversión de polaridade de batería (opcional).
- 1 × Conector micro-USB o pads para programación / alimentación (ou usar conector USB-C).
- Condensadores, resistencias, diodos de protección e ferrites.

## Esquema funcional (bloques)
- **Entrada batería** → proteción (fuse / diodo) → **buck 5V** → 5V rail
- 5V rail → **regulador 3.3V** → alimenta ESP32 (se o módulo non trae 3.3V)
- ESP32: pinos GPIO → drivers / sensores / I²C (se necesario)
- **Driver motores (TB6612)**: alimentado a 5–7V (VccM), sinais IN1/IN2 desde ESP32, pin PWM para velocidade (PWMA/PWMB)
- Sensores IR: 5 entradas analóxicas dixitalizadas (ADC) ou via divisor + comparador → conectadas a GPIOs ADC do ESP32
- Conectores: motores, batería, sensores, UART/USB.

## Proposta de asignación de pinos (exemplo)
> Nota: axusta segundo o teu módulo ESP32 e dispoñibilidade de pinos.

- **Motores**
  - Motor L: IN1 → GPIO 14, IN2 → GPIO 12, PWM(A) → GPIO 13 (PWM)
  - Motor R: IN1 → GPIO 27, IN2 → GPIO 26, PWM(B) → GPIO 25 (PWM)

- **Sensores IR** (5 canais → ADCs)
  - S1 → GPIO 32 (ADC1_CH4)
  - S2 → GPIO 33 (ADC1_CH5)
  - S3 → GPIO 34 (ADC1_CH6)  *(non pull-up)*
  - S4 → GPIO 35 (ADC1_CH7)  *(non pull-up)*
  - S5 → GPIO 39 (ADC1_CH3)  *(non pull-up)*

- **Periféricos**
  - I2C (opcional para sensores adicionais): SDA → GPIO 21, SCL → GPIO 22
  - RESET → botón a EN
  - BOOT/PROGRAM → botón a IO0 (opcional)
  - UART (debug/programación) → USB to Serial integrado no módulo

## Conectores e disposición na placa
- **Conector batería** (JST-SM 2 pin) preto da esquina para fácil conexión.
- **Terminais motores**: 2× terminal block de 2 polos (o máis robusto posible).
- **Header sensores**: 1×5 pinos JST ou pines 5×1 para conectar a tira de sensores IR.
- **Orificios de fixación**: 2–4 taladros (M3) se vas atornillar a placa ao chasis.

## Alimentación e estabilidade
- Se usas **LiPo 2S (7.4 V)** → alimenta Vmotor directo (VccM) e usa buck para 5V.
- Se usas **4×AA NiMH (~4.8 V)** → podes alimentar directamente VccM e tamén regular a 5V si é necesario.
- Engade **condensadores electrolíticos** (100–470 µF) preto do driver de motor para suavizar picos de corrente.
- Engade **diodes flyback** se o driver non inclúe proteción (TB6612 incorpora proteción interna en gran parte).


## Regras de enrutado do PCB (suxestións)
- Lóxica (3.3V) separada do plano de potencia (motores).
- Liñas de alimentación robustas para ruta motor.
- Coloca o condensador grande preto do driver de motor.
- Mantén as trazas PWM curtas entre ESP32 e driver.
- Pensa en separar a masa GND en "star" ou con boa viaje entre GND-motores e GND-logic para evitar ruído (un só plano GND con vias de unión funciona ben en 2 capas).

## Protección e seguridade
- Fusible rearmable (PTC) na entrada da batería.
- Diodo de protección contra conexión inversa (schottky).
- Indicador LED de encendido (5V) e LED de estado ESP32 (GPIO para status).
- No caso de LiPo, recomenda-se usar conector con protección externa ou BMS.

## Montaxe e comprobacións rápidas
1. Monta o ESP32 e o driver, conecta batería sen carga (comprobar tensións 5V/3.3V).
2. Medir continuidade GND/Vcc para evitar curto.
3. Cargar un firmware básico que puguex: inicializar GPIOs, probar PWM en motores con carga mínima (xogar con duty cycle baixo).
4. Conectar sensores e calibrar lecturas ADC con superficies clara/escura.


# Deseño de software

## 1. Obxectivos
- Ler os sensores IR para detectar a liña.
- Controlar a velocidade e dirección dos motores DC mediante PWM.
- Implementar un **algoritmo de control** que siga a liña con estabilidade.
- Permitir **calibración e axustes** de velocidade e PID desde unha interface serie ou Wi-Fi.
- Opcional: rexistrar datos de sensores e motores para análise.

## 2. Arquitectura xeral
- **Módulo principal:** ESP32
- **Drivers motores:** TB6612FNG (PWM + dirección)
- **Sensores IR:** 5 canles → entradas ADC
- **Subsistemas software:**
  1. **Lectura sensores** (ADC, calibración, filtrado)
  2. **Control motores** (PWM + dirección)
  3. **Lóxica de control** (PID ou algoritmo proporcional simple)
  4. **Comunicación** (UART/USB ou Wi-Fi opcional)
  5. **Inicialización e configuración** (setup de pinos, timers)

---

## 3. Fluxo básico do programa

1. **Setup**:
   - Inicializar GPIOs para motores e sensores.
   - Configurar PWM para velocidade.
   - Inicializar UART / Wi-Fi se se require comunicación.

2. **Loop principal**:
   - Ler os 5 sensores IR.
   - Calcular o erro respecto da liña central:
     ```
     erro = (S1* - 2*S2* - S3* + 2*S4* - S5*)  # esquema ponderado simple
     ```
   - Aplicar **controlador PID** (ou proporcional) sobre os motores:
     - Motor esquerdo: base_velocidade - Kp * erro
     - Motor dereito: base_velocidade + Kp * erro
   - Actualizar PWM e dirección dos motores.
   - Repetir cada 10–20 ms.

3. **Funcións auxiliares**:
   - `lerSensores()`: devolve array de valores calibrados.
   - `calcularErro()`: pondera sensores e devolve erro do centro.
   - `setMotorPWM(esq, dir_esq, der, dir_der)`: envia sinais ao driver.
   - `calibrarSensores()`: gravar valores máximo/mínimo para normalización.
   - Opcional: `debugSerial()`, `enviarDatosWiFi()`

---

## 4. Estrutura de carpetas suxerida no repo

softwawe/
├── src/
│ ├── main.cpp
│ ├── motores.cpp
│ ├── sensores.cpp
│ └── control.cpp
├── include/
│ ├── motores.h
│ ├── sensores.h
│ └── control.h
├── platformio.ini # se usas PlatformIO
└── README.md

- `motores.cpp/h`: drivers PWM e dirección dos motores.
- `sensores.cpp/h`: lectura e calibración de sensores IR.
- `control.cpp/h`: algoritmo PID ou proporcional.
- `main.cpp`: loop principal e inicialización.

---

## 5. Algoritmo de control (simplificado)
Control proporcional de velocidade

```c++
erro = calcularErro();
vel_esq = base_vel - Kp * erro;
vel_der = base_vel + Kp * erro;
setMotorPWM(vel_esq, vel_der);
```

# Referencias e bibliografía

## Robot segue-liñas e hardware
- [MicrocontrollersAndMore: Line Following Robot](https://www.microcontrollersandmore.com/line-following-robot) – Explicación básica de robots segue-liñas.
- [Arduino Project Hub: Line Follower Robot](https://create.arduino.cc/projecthub/projects/tags/line-follower) – Exemplos con Arduino, motores DC e sensores IR.
- “**Building Robots with LEGO Mindstorms**”, Cameron Hughes & Tracey Hughes – Inclúe conceptos de motores, sensores e control PID (aplicable a robots DIY).
- [Pololu: TB6612 Motor Driver](https://www.pololu.com/product/713) – Documentación e exemplos de uso do driver de motores dual.

## ESP32 e control de motores
- [Espressif ESP32 Official Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/) – Guía completa para programación, GPIOs, PWM, ADC e Wi-Fi.
- [Random Nerd Tutorials: ESP32 Motor Control](https://randomnerdtutorials.com/esp32-motor-driver-tutorial/) – Exemplos prácticos de control de motores DC con ESP32.
- “**Programming the ESP32**”, Neil Kolban – Libro detallado sobre hardware e software do ESP32.

## Software de control e algoritmos de segue-liñas
- [Control Tutorials for MATLAB and Simulink: PID Control](http://ctms.engin.umich.edu/CTMS/index.php?example=Introduction&section=ControlPID) – Teoría de control proporcional, integral e derivativo.
- [Arduino PID Library](https://playground.arduino.cc/Code/PIDLibrary/) – Biblioteca popular para control PID en microcontroladores.
- [All About Circuits: Line Following Algorithms](https://www.allaboutcircuits.com/projects/line-following-robot/) – Explicación de algoritmos de seguimento de liña.

## GitHub Pages / Jekyll
- [Jekyll Official Docs](https://jekyllrb.com/docs/) – Configuración e uso de Jekyll.
- [GitHub Pages Documentation](https://docs.github.com/en/pages) – Publicación de sitios estáticos con GitHub Pages.
- [GitHub Actions: Deploy Pages](https://docs.github.com/en/actions/deployment/deploying-to-github-pages) – Automatización de despliegues con GitHub Actions.

## Electrónica e mecánica básica
- “**Make: Electronics**”, Charles Platt – Fundamentos de electrónica, sensores e motores DC.
- “**Robot Building for Beginners**”, David Cook – Guía práctica de mecánica e electrónica de robots DIY.
- [All About Circuits](https://www.allaboutcircuits.com/) – Recursos en liña para electrónica e control de motores.
