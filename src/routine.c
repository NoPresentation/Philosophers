# include "../inc/philo.h"

int end_simulation(t_table *table)
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

static int    eating(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(&philo->table->print_lock);
    // if (end_simulation(philo->table))
    // {
    //     pthread_mutex_unlock(philo->left_fork);
    //     pthread_mutex_unlock(philo->right_fork);
    //     pthread_mutex_unlock(&philo->table->print_lock);
    //     return (1);
    // }
    pthread_mutex_lock(&philo->last_meal_lock);
    philo->last_meal = get_time_ms();
    pthread_mutex_unlock(&philo->last_meal_lock);
    printf("%lld\t%d has taken a fork\n", get_time_ms() - philo->table->start_time, philo->id);
    printf(BLUE "%lld\t%d is eating\tmeals: %d\n" RESET, get_time_ms() - philo->table->start_time, philo->id, philo->meals);
    pthread_mutex_unlock(&philo->table->print_lock);
    ft_usleep(philo->table->to_eat, philo->table);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_lock(&philo->meals_lock);
    philo->meals++;
    pthread_mutex_unlock(&philo->meals_lock);
    return (0);
}

static int     thinking(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->print_lock);
    // if (end_simulation(philo->table))
    // {
    //     pthread_mutex_unlock(&philo->table->print_lock);
    //     return (1);
    // }
    printf("%lld\t%d is thinking\n", get_time_ms() - philo->table->start_time, philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);
    return (0);
}

static int     sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->print_lock);
    // if (end_simulation(philo->table))
    // {
    //     pthread_mutex_unlock(&philo->table->print_lock);
    //     return (1);
    // }
    printf("%lld\t%d is sleeping\n", get_time_ms() - philo->table->start_time, philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);
    ft_usleep(philo->table->to_sleep, philo->table);
    return (0);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        if (end_simulation(philo->table))
            break;
        if (philo->table->N == 1)
        {
            pthread_mutex_lock(&philo->table->print_lock);
            printf("%lld\t%d has taken a fork\n", get_time_ms() - philo->table->start_time, philo->id);
            pthread_mutex_unlock(&philo->table->print_lock);
            usleep(philo->table->to_die);
            break;
        }
        if (eating(philo) != 0)
            break;
        if (sleeping(philo) != 0)
            break;
        if (thinking(philo) != 0)
            break;
    }
    return (NULL);
}
