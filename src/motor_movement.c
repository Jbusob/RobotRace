#include <motor_movement.h>

void init_timer0_pwm(void)
{
    // Fast PWM mode (WGM00 and WGM01 set) 
    // Non-inverting output on both channels A and B
    TCCR0A = (1 << WGM00) | (1 << WGM01)
           | (1 << COM0A1) | (1 << COM0B1);

    // Prescaler = 64: (1 << CS01) | (1 << CS00) -> CPU clock / 64
    TCCR0B = (1 << CS01) | (1 << CS00);

    // Initialize compare registers to 0 (motors off)
    OCR0A = 0;  
    OCR0B = 0;  
}

// -------------------------
// Configure I/O pins
// -------------------------
void init_io(void)
{
    // Direction pins as outputs
    ML_Ctrl_DDR |= (1 << ML_Ctrl_PIN);
    MR_Ctrl_DDR |= (1 << MR_Ctrl_PIN);

    // PWM pins as outputs
    ML_PWM_DDR |= (1 << ML_PWM_PIN);
    MR_PWM_DDR |= (1 << MR_PWM_PIN);
}

// -------------------------
// Motor Actions
// -------------------------
void move_forward(void)
{
    // Both direction pins HIGH
    ML_Ctrl_PORT |= (1 << ML_Ctrl_PIN);
    MR_Ctrl_PORT |= (1 << MR_Ctrl_PIN);

    // PWM duty cycles (example: 55 out of 255)
    OCR0B = 200;  // Left motor (OC0B)
    OCR0A = 187;  // Right motor (OC0A)

    _delay_ms(3000);
}

void move_backward(void)
{
    // Both direction pins LOW
    ML_Ctrl_PORT &= ~(1 << ML_Ctrl_PIN);
    MR_Ctrl_PORT &= ~(1 << MR_Ctrl_PIN);

    // PWM duty cycles (example: 200 out of 255)
    OCR0B = 40; // Left motor
    OCR0A = 70; // Right motor

    _delay_ms(3000);
}

void turn_left(void)
{
    // Left motor LOW, Right motor HIGH
    ML_Ctrl_PORT &= ~(1 << ML_Ctrl_PIN);
    MR_Ctrl_PORT |=  (1 << MR_Ctrl_PIN);

    // Left motor speed 200, Right motor speed 55
    OCR0B = 70; 
    OCR0A = 40;  

    _delay_ms(2000);
}

void turn_right(void)
{
    // Left motor HIGH, Right motor LOW
    ML_Ctrl_PORT |=  (1 << ML_Ctrl_PIN);
    MR_Ctrl_PORT &= ~(1 << MR_Ctrl_PIN);

    // Left motor speed 55, Right motor speed 200
    OCR0B = 40;  
    OCR0A = 70; 

    _delay_ms(2000);
}

void stop_motors(void)
{
    // For simplicity, direction pins LOW, PWM = 0
    ML_Ctrl_PORT &= ~(1 << ML_Ctrl_PIN);
    MR_Ctrl_PORT &= ~(1 << MR_Ctrl_PIN);

    OCR0B = 0; 
    OCR0A = 0; 

    _delay_ms(2000);
}