# include "../inc/philo.h"

bool check_dead(t_philo *philo)
{
    pthread_mutex_lock(&philo->meals_lock);
    if (get_time_ms() - philo->last_meal >= philo->table->to_die)
    {
        pthread_mutex_lock(&philo->table->simulation_lock);
        philo->table->simulation = 0;
        pthread_mutex_unlock(&philo->table->simulation_lock);
        pthread_mutex_unlock(&philo->meals_lock);
		printf("%lld\t%d %s\n", get_time_ms() - philo->born_time, philo->id, "died");
        return (true);
    } 
    pthread_mutex_unlock(&philo->meals_lock);
    return (false);
}

bool    check_full(t_philo *philo)
{
    pthread_mutex_lock(&philo->meals_lock);
    if (philo->meals >= philo->table->must_eat)
    {
        pthread_mutex_unlock(&philo->meals_lock);
        return (1);
    }
    pthread_mutex_unlock(&philo->meals_lock);
    return (0);
}

void    monitor(t_table *table)
{
    int i;
    int full_philos;

    while (true)
    {
        i = 0;
        full_philos = 0;
        while (i < table->N)
        {
            if (check_dead(&table->philo[i]))
                return ;
            if (table->must_eat != -1 && check_full(&table->philo[i]))
                full_philos++;
            i++;
        }
        if (table->must_eat != - 1 && full_philos >= table->N)
        {
            pthread_mutex_lock(&table->simulation_lock);
            table->simulation = 0;
            pthread_mutex_unlock(&table->simulation_lock);
            return ;
        }
    }
}
