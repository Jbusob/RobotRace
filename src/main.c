
#include <avr/io.h>
#include <util/delay.h>
#include <motor_movement.h>

void setup(void)
{
    init_io();
    init_timer0_pwm();
}

void loop(void)
{
// Forward for 2s
    move_forward();
            
    // Backward for 2s
    move_backward();

    // Turn left for 2s
    turn_left();

    // Turn right for 2s
    turn_right();

    // Stop for 2s
    stop_motors();
}

int main(void)
{

    setup();

    while (1)
    {
       loop(); 
    }

    return 0;
}
