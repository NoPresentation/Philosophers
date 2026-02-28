#include "../../inc/philo.h"

ll get_time_ms()
{
    ll time;

    struct timeval tv;
    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
    return (time);
}