
#include <timer_msec.h>
#include <encoder.h>
#include <digital_out.h>
#include <avr/interrupt.h>
#include <Arduino.h>

Encoder encA(1);
Encoder encB(2);

Digital_out led(5);

int waiting_time_us = 280;
bool last_state_A = encA.is_low();
bool last_state_B = encB.is_low();
bool curr_state_A;
bool curr_state_B;

Timer_msec timer_sampling;
Timer_msec timer_speed;


int  main(){
    Serial.begin(9600);
    led.init();
    timer_sampling.init_sampling(waiting_time_us);
    timer_speed.init_speed();
    timer_speed.count_speed  = 0;
    sei();
    
    while(1){
    }
}

ISR(TIMER1_COMPA_vect)
{
    if(last_state_A == last_state_B){
      curr_state_A = encA.is_low();
      if(curr_state_A != last_state_A){
        encA.count++;
        led.toggle();
      }
      else{ 
        curr_state_B  = encB.is_low();
        if(curr_state_B != last_state_B){
          encA.count--;
          led.toggle();
        }
      }
    }
    else{
      curr_state_A = encA.is_low();
      if(curr_state_A != last_state_A){
        encA.count--;
        led.toggle();
      }
      else{ 
        curr_state_B  = encB.is_low();
        if(curr_state_B != last_state_B){
          encA.count++;
          led.toggle();
        }
      }
    }
    last_state_A = curr_state_A;
    last_state_B = curr_state_B;
  }

ISR(TIMER0_COMPA_vect){
  timer_speed.count_speed++;
  if(timer_speed.count_speed == 125){
    int speed = encA.count;
    encA.count = 0;
    timer_speed.count_speed = 0;
    Serial.println(speed);
  }
}
