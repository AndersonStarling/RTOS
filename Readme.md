/* RTC and control LED project */

1. Software Requirement
- IDE: STM32 IDE(Windown 10/11, Linux, Mac)
- Compiler: GNU Gcc
- FreeRTOS Library: https://freertos.org/a00125.html

2. Hardware Requirement
- STM32F4x
- USB To TTL
- 3 LED
- UART configure as 115200 baudrate

3. Wiring Guide(applicable on STM32F411)
- UART: TX - PA9
        RX - PA10
- LED_0 - PC10
- LED_1 - PC12
- LED_2 - PB7

4. Project Details
- Project display realtime clock(date and time) and support configure date and time through UART
- Project run on a OS firmware that base on FreeRTOS enviroment
- There are two main OS task in project:

+ Task 1: Configure time
Configure date: day, month, year
Configure time: hour, min, second

+ Task 2: Configure LED effect to 3 mode
Mode 0: Turn on 3 LED
Mode 1: Turn on 2 LED
MOde 2: Turn on 1 LED







