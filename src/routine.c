# include "../inc/philo.h"

bool end_simulation(t_table *table)
{
    pthread_mutex_lock(&table->simulation_lock);
    if (!table->simulation)
    {
        pthread_mutex_unlock(&table->simulation_lock);
        return (1);    
    }
    pthread_mutex_unlock(&table->simulation_lock);
    return (0);
}

void    eating(t_philo *philo)
{
    if (philo->id % 2 == 0)
        usleep(1000);
    pthread_mutex_lock(philo->right_fork);
    print_action(philo, "has taken a fork");
    pthread_mutex_lock(philo->left_fork);
    print_action(philo, "has taken a fork");
    pthread_mutex_lock(&philo->meals_lock);
    philo->last_meal = get_time_ms();
    philo->meals++;
    pthread_mutex_unlock(&philo->meals_lock);
    print_action(philo, "is eating");
    ft_usleep(philo->table->to_eat, philo->table);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void    sleeping(t_philo *philo)
{
    print_action(philo, "is sleeping");
    ft_usleep(philo->table->to_sleep, philo->table);
}

void    thinking(t_philo *philo)
{
    print_action(philo, "is thinking");
}

void    *routine(void *p)
{
    t_philo *philo;

    philo = (t_philo *)p;
    philo->last_meal = get_time_ms();
    philo->born_time = get_time_ms();
    if (philo->table->N == 1)
    {
        print_action(philo, "has taken a fork");
        ft_usleep(philo->table->to_die, philo->table);
		printf("%lld\t%d %s\n", get_time_ms() - philo->born_time, philo->id, "died");
        return (NULL) ;       
    }
    while (true)
    {
        if (end_simulation(philo->table))
            return (NULL);
        eating(philo);
        if (end_simulation(philo->table))
            return (NULL);
        sleeping(philo);
        if (end_simulation(philo->table))
            return (NULL);
        thinking(philo);
    }
    return (NULL);
}
