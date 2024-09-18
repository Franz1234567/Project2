#pragma once

class Timer_msec
{
public:
    Timer_msec();
    void init_sampling(int period_us, double duty_cycle);
    void init_speed();
    int count_speed;
};