# include "../inc/philo.h"

int    simulation(int argc, ll *args)
{
    t_table *table;
    table = init_table(argc, args);
    if (!table)
        return (1);
    if (init_forks(table) != 0)
    {
        free(table);
        return (1);
    }
    if (init_simulation(table) != 0)
    {
        free(table->forks);
        free(table);
        return (1);
    }
    monitor(table);
    clean_up(table);
    return (0);
}