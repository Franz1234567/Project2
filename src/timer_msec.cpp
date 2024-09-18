#include <timer_msec.h>
#include <avr/io.h>


Timer_msec::Timer_msec(){}

void Timer_msec::init_sampling(int period_us, double duty_cycle){
    TCCR1A = 0;                    // set timer1 to normal operation (all bits in control registers A and B set to zero)
    TCCR1B = 0;
    TCNT1 = 0;                     // initialize counter value to 0
    OCR1A = (16000000.0/1024.0) * (period_us/1000000.0) -1;   // assign target count to compare register A (must be less than 65536)
    OCR1B = (16000000.0/1024.0) * (0.6/1000.0) -1;
    OCR1C = OCR1A * (duty_cycle/100.0) - 1;
    TCCR1B |= (1 << WGM12);        // clear the timer on compare match A
    TIMSK1 |= (1 << OCIE1A);       // set interrupt on compare match A
    TIMSK1 |= (1 << OCIE1B);       // set interrupt on compare match B
    TCCR1B |= (1 << CS10) | (1 << CS12); // set prescaler to 1024 and start the timer
}

void Timer_msec::init_speed(){
    // timer of 1 second using timer0 (which has 8 bits)
    TCCR0A = 0;
    TCCR0B = 0;
    TCNT0 = 0;

    OCR0A = 124; // see report for explanation about this target count
    TCCR0B |= (1 << WGM02); // clear timer on compare match
    TIMSK0 |= (1 << OCIE0A); // set interrupt 
    TCCR0B |= (1 << CS00) | (1 << CS02); // prescaler of 1024
}
