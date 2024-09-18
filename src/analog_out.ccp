# include <analog_out.h>
# include <digital_out.h>

Analog_out::Analog_out(int pin):pin_digi(pin){
    pin_digi.init();
}

void Analog_out::init(int period_ms  = 1000){
    timer.init(period_ms, 50);
}

void Analog_out::set(int duty_cycle){
    timer.set_duty_cycle(duty_cycle);
}