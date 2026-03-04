# include "../inc/philo.h"

static int check_all_full(t_table *table)
{
    int full_philos;
    int i;
    int meals;

    i = 0;
    full_philos = 0;
    while (i < table->N)
    {
        pthread_mutex_lock(&table->philo[i].meals_lock);
        meals = table->philo[i].meals;
        pthread_mutex_unlock(&table->philo[i].meals_lock);
        if (meals >= table->full)
            full_philos++;
        i++;
    }
    if (full_philos == table->N)
    {
        pthread_mutex_lock(&table->simulation_lock);
        table->simulation = 0;
        pthread_mutex_unlock(&table->simulation_lock);
        clean_up(table);
        return (1);
    }
    return (0);
}

static int check_dead(t_philo *philo)
{
    ll  death_time;
    int dead_id;

    pthread_mutex_lock(&philo->last_meal_lock);
    if (get_time_ms() - philo->last_meal > philo->table->to_die)
    {
        pthread_mutex_unlock(&philo->last_meal_lock);
        pthread_mutex_lock(&philo->table->simulation_lock);
        philo->table->simulation = 0;
        pthread_mutex_unlock(&philo->table->simulation_lock);
        death_time = get_time_ms() - philo->table->start_time;
        dead_id = philo->id;
        clean_up(philo->table);
        pthread_mutex_lock(&philo->table->print_lock);
        printf("%lld\t%d died\n", death_time, dead_id);
        pthread_mutex_unlock(&philo->table->print_lock);
        return 1;
    }
    pthread_mutex_unlock(&philo->last_meal_lock);
    return (0);
}

void    monitor(t_table *table)
{
    int i;

    while (1)
    {
        i = 0;
        while (i < table->N)
        {
            if (check_dead(&table->philo[i]))
                return ;
            i++;
        }
        if (table->full != -1 && check_all_full(table))
            return ;
    }
}
