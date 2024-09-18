#pragma once

class Timer_msec
{
public:
    Timer_msec();
    void init_sampling(int period_us);
    void init_speed();
    int count_speed;
};