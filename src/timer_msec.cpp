#include <timer_msec.h>
#include <avr/io.h>


Timer_msec::Timer_msec(){}

void Timer_msec::init_sampling(int period_ms){
    TCCR1A = 0;                    // set timer1 to normal operation (all bits in control registers A and B set to zero)
    TCCR1B = 0;
    TCNT1 = 0;                     // initialize counter value to 0
    
    OCR1A = (16000000.0/1024.0) * (period_ms/1000000.0) -1;   // assign target count to compare register A (must be less than 65536)
    TCCR1B |= (1 << WGM12);        // clear the timer on compare match A
    TIMSK1 |= (1 << OCIE1A);       // set interrupt on compare match A
    TCCR1B |= (1 << CS10) | (1 << CS12); // set prescaler to 1024 and start the timer
}

void Timer_msec::init_speed(){
    TCCR2B = 0;
    TCCR2B = 0
    TCNT2 = 0;
}
