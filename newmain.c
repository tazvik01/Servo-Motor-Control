#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
    // Set PB3 (OC1A) as output
    DDRB |= (1 << PB3);

    // Configure Timer1 for Fast PWM mode with ICR1 as TOP
    TCCR1A = (1 << COM1A1) | (1 << WGM11); // Non-inverting mode, Fast PWM
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler = 8

    // Set TOP value for 50 Hz PWM frequency
    ICR1 = 2499;

    // Set initial pulse width to 1.5 ms (center position)
    OCR1A = 188;

    while (1)
    {
        // Adjust OCR1A between 125 and 250 to control servo position
        // For example, move servo from 0° to 180°
        for (uint16_t position = 125; position <= 250; position += 5)
        {
            OCR1A = position;
            _delay_ms(20);
        }

        // Reverse direction
        for (uint16_t position = 250; position >= 125; position -= 5)
        {
            OCR1A = position;
            _delay_ms(20);
        }
    }

    return 0;
}
