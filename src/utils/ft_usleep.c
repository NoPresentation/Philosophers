# include "../../inc/philo.h"

void ft_usleep(long duration, t_table *table)
{
    long start = get_time_ms();

    while (!end_simulation(table))
    {
        if (get_time_ms() - start >= duration)
            break;
        usleep(300); // sleep tiny bit
    }
}