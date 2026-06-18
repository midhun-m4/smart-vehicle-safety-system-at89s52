#include <reg52.h>

/* -------- PIN DEFINITIONS -------- */

sbit LDR_OUT  = P1^0;
sbit LED_HEAD = P1^1;

sbit TRIG     = P3^0;
sbit ECHO     = P3^1;

sbit IN1      = P2^0;
sbit IN2      = P2^1;
sbit ENA      = P2^2;

sbit IN3      = P2^3;
sbit IN4      = P2^4;
sbit ENB      = P2^5;

/* -------- GLOBAL VARIABLES -------- */

unsigned char pwm_counter = 0;
unsigned char duty_cycle = 100;

/* -------- TIMER0 PWM (HEADLIGHT) -------- */

void timer0_ISR(void) interrupt 1
{
    TH0 = 0xFF;
    TL0 = 0xA4;   // ~100us interrupt

    pwm_counter++;

    if(pwm_counter >= 100)
        pwm_counter = 0;

    LED_HEAD = (pwm_counter < duty_cycle) ? 1 : 0;
}

/* -------- DELAYS -------- */

void delay_us(unsigned int us)
{
    while(us--);
}

void delay_ms(unsigned int ms)
{
    unsigned int i, j;

    for(i = 0; i < ms; i++)
        for(j = 0; j < 123; j++);
}

/* -------- ULTRASONIC FUNCTION -------- */

unsigned int get_distance(void)
{
    unsigned int count = 0;
    unsigned int timeout = 0;

    TRIG = 0;
    delay_us(2);

    TRIG = 1;
    delay_us(10);
    TRIG = 0;

    /* Wait for ECHO HIGH */
    while(ECHO == 0)
    {
        timeout++;

        if(timeout > 20000)
            return 0;
    }

    /* Measure pulse width */
    while(ECHO == 1)
    {
        count++;
        delay_us(1);

        if(count > 20000)
            break;
    }

    if(count == 0 || count > 20000)
        return 0;

    return (count / 58);   // Distance in cm
}

/* -------- MOTOR CONTROL -------- */

void motors_forward(void)
{
    ENA = 1;
    ENB = 1;

    IN1 = 1;
    IN2 = 0;

    IN3 = 1;
    IN4 = 0;
}

void motors_stop(void)
{
    IN1 = 0;
    IN2 = 0;

    IN3 = 0;
    IN4 = 0;
}

/* -------- MAIN PROGRAM -------- */

void main(void)
{
    unsigned int dist;

    TMOD = 0x01;   // Timer0 Mode 1

    TH0 = 0xFF;
    TL0 = 0xA4;

    ET0 = 1;       // Enable Timer0 interrupt
    EA  = 1;       // Global interrupt enable
    TR0 = 1;       // Start Timer0

    motors_stop();

    while(1)
    {
        /* -------- LDR AUTO DIM -------- */

        if(LDR_OUT == 0)
            duty_cycle = 30;      // Dim headlight
        else
            duty_cycle = 100;     // Full brightness

        /* -------- ULTRASONIC AUTO BRAKE -------- */

        dist = get_distance();

        if(dist != 0 && dist <= 5)
        {
            motors_stop();        // Automatic braking
        }
        else
        {
            motors_forward();     // Normal movement
        }

        delay_ms(100);
    }
}
