#ifndef LED_MODE_H
#define LED_MODE_H

/* Led 0 */
#define PORT_LED_0   GPIOC
#define PIN_LED_0    GPIO_PIN_10

/* Led 1 */
#define PORT_LED_1   GPIOC
#define PIN_LED_1    GPIO_PIN_12

/* Led 2 */
#define PORT_LED_2   GPIOB
#define PIN_LED_2    GPIO_PIN_7

void LED_Mode_0(void);
void LED_Mode_1(void);
void LED_Mode_2(void);
void LED_Mode_Off(void);

#endif /* LED_MODE_H */









