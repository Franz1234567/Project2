#include <timer_msec.h>
#include <encoder.h>
#include <digital_out.h>
#include <avr/interrupt.h>
#include <p_controller.h>
#include <Arduino.h>

Encoder encA(1);
Encoder encB(2);

Digital_out led(5);
P_controller control(5);

const int max_speed = 3000;
const float speed_63_ref = max_speed*0.63;
bool speed_63_found = 0;
int current_speed;
const double ref = 2500;


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

  if (encA.count == 0){
    timer_speed.count_speed = 0;
    speed_63_found = 0;
  }

  if((speed_63_ref <= abs(encA.count)) && (speed_63_found == 0)){
    int speed_63 = encA.count;
    float time_cst = timer_speed.count_speed * 0.008; // 0.008s each 125 clock cycle (see report for more details)
    speed_63_found = 1;

    Serial.print("----------Speed 63%: ");
    Serial.print(speed_63);
    Serial.print("pps\n");

    Serial.print("----------Time cst: ");
    Serial.print(time_cst);
    Serial.print("ms\n");
  }

  if(timer_speed.count_speed == 125){
    current_speed = encA.count;
    encA.count = 0;
    timer_speed.count_speed = 0;
    Serial.println(current_speed);
  }
}
ISR(TIMER1_COMPA_vect){
  error = control.update(ref, (double)current_speed);
  
}
