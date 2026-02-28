# include "../inc/philo.h"

void    clean_up(t_table *table)
{
    int i;

    i = 0;
    while (i < table->N)
    {
        pthread_join(table->philo[i].thread, NULL);
        i++;
    }
    free(table->forks);
    free(table->philo);
    free(table);
}
t_table *init_table(ll *args)
{
    t_table *table;

    table = malloc(sizeof(t_table));
    if (!table)
        return (NULL);
    table->N = args[0];
    table->to_die = args[1];
    table->to_eat = args[2];
    table->to_sleep = args[3];
    table->full = args[4];
        table->simulation = 1;
    return (table);
}

int init_simulation(t_table *table)
{
    int i;

    i = 0;
    table->philo = malloc(sizeof(t_philo) * table->N);
    if (!table->philo)
        return (1);
    pthread_mutex_init(&table->simulation_lock, NULL);
    pthread_mutex_init(&table->print_lock, NULL);
    while (i < table->N)
    {
        table->philo[i].table = table;
        table->philo[i].id = i;
        table->philo[i].right_fork = &table->forks[(i + 1) % table->N];
        table->philo[i].left_fork = &table->forks[i];
        table->philo[i].last_meal = get_time_ms();
        pthread_mutex_init(&table->philo[i].last_meal_lock, NULL);
        pthread_create(&table->philo[i].thread, NULL, routine, &table->philo[i]);
        i++;
    }
    return (0);
}

int init_forks(t_table *table)
{
    int i;

    i = 0;
    table->forks = malloc(sizeof(pthread_mutex_t) * table->N);
    if (!table->forks)
        return (1);
    while (i < table->N)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        i++;
    }
    return (0);
}

int    simulation(ll *args)
{
    t_table *table;
    table = init_table(args);
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

