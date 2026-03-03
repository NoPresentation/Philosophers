# include "../inc/philo.h"

void    destroy_forks(t_table *table, int forks)
{
    int i;

    i = 0;
    while (i < forks)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
}

void    destroy_threads(t_table *table, int threads)
{
    int i;

    i = 0;
    while (i < threads)
    {
        pthread_join(table->philo[i].thread, NULL);
        i++;
    }
}

void    destroy_locks(t_table *table, int philos)
{
    int i;

    i = 0;
    pthread_mutex_destroy(&table->simulation_lock);
    pthread_mutex_destroy(&table->print_lock);
    while (i < philos)
    {
        pthread_mutex_destroy(&table->philo[i].last_meal_lock);
        pthread_mutex_destroy(&table->philo[i].meals_lock);
        i++;
    }
}

void    clean_up(t_table *table)
{
    destroy_threads(table, table->N);
    destroy_forks(table, table->N);
    destroy_locks(table, table->N);
    free(table->forks);
    free(table->philo);
    free(table);
}