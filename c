#include <avr/io.h>
#include <util/delay.h>

#define RED_LED PB0
#define GREEN_LED PB1
#define YELLOW_LED PB2
#define BUZZER PB3

#define SENSOR1 PC0
#define SENSOR2 PC1
#define SENSOR3 PC2

void init_pins() {
    DDRB |= (1 << RED_LED) | (1 << GREEN_LED) | (1 << YELLOW_LED) | (1 << BUZZER);
    DDRC &= ~((1 << SENSOR1) | (1 << SENSOR2) | (1 << SENSOR3));
}

void turn_on_led(uint8_t led) {
    PORTB |= (1 << led);
}

void turn_off_led(uint8_t led) {
    PORTB &= ~(1 << led);
}

void check_sensors() {
    if (PINC & (1 << SENSOR1) || PINC & (1 << SENSOR2) || PINC & (1 << SENSOR3)) {
        turn_on_led(YELLOW_LED);
    } else {
        turn_off_led(YELLOW_LED);
    }
}

void activate_alarm() {
    turn_on_led(RED_LED);
    turn_off_led(GREEN_LED);
    PORTB |= (1 << BUZZER);
}

void deactivate_alarm() {
    turn_off_led(RED_LED);
    turn_on_led(GREEN_LED);
    PORTB &= ~(1 << BUZZER);
}

int main() {
    init_pins();
    deactivate_alarm();

    while (1) {
        check_sensors();
        // Lógica para leer el teclado y verificar el código aquí
    }
}
