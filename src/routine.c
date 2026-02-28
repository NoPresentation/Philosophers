# include "../inc/philo.h"

static void    eating(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);

    pthread_mutex_lock(&philo->table->print_lock);
    pthread_mutex_lock(&philo->table->simulation_lock);
    if (!philo->table->simulation)
    {
        pthread_mutex_unlock(&philo->table->simulation_lock);
        pthread_mutex_unlock(&philo->table->print_lock);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return ;
    }
    pthread_mutex_unlock(&philo->table->simulation_lock);
    printf("%lld %d has taken a fork\n", get_time_ms(), philo->id);
    printf("%lld %d is eating\n", get_time_ms(), philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);

    usleep(philo->table->to_eat * 1000);

    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);

    pthread_mutex_lock(&philo->last_meal_lock);
    philo->last_meal = get_time_ms();
    pthread_mutex_unlock(&philo->last_meal_lock);
    philo->meals++;
}

static void     thinking(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->print_lock);
    pthread_mutex_lock(&philo->table->simulation_lock);
    if (!philo->table->simulation)
    {
        pthread_mutex_unlock(&philo->table->simulation_lock);
        pthread_mutex_unlock(&philo->table->print_lock);
        return ;
    }
    pthread_mutex_unlock(&philo->table->simulation_lock);
    printf("%lld %d is thinking\n", get_time_ms(), philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);
}

static void     sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->print_lock);
    pthread_mutex_lock(&philo->table->simulation_lock);
    if (!philo->table->simulation)
    {
        pthread_mutex_unlock(&philo->table->simulation_lock);
        pthread_mutex_unlock(&philo->table->print_lock);
        return;
    }
    pthread_mutex_unlock(&philo->table->simulation_lock);
    printf("%lld %d is sleeping\n", get_time_ms(), philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);
    usleep(philo->table->to_sleep * 1000);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        pthread_mutex_lock(&philo->table->simulation_lock);
        if (!philo->table->simulation)
        {
            pthread_mutex_unlock(&philo->table->simulation_lock);
            break;
        }
        pthread_mutex_unlock(&philo->table->simulation_lock);
        thinking(philo);
        eating(philo);
        sleeping(philo);
    }
    return (NULL);
}

void    monitor(t_table *table)
{
    int i;

    while (1)
    {
        i = 0;
        while (i < table->N)
        {
            pthread_mutex_lock(&table->philo[i].last_meal_lock);
            if (get_time_ms() - table->philo[i].last_meal > table->to_die)
            {
                pthread_mutex_unlock(&table->philo[i].last_meal_lock);
                pthread_mutex_lock(&table->print_lock);
                printf("%lld %d died\n", get_time_ms(), table->philo[i].id);
                pthread_mutex_unlock(&table->print_lock);
                pthread_mutex_lock(&table->simulation_lock);
                table->simulation = 0;
                pthread_mutex_unlock(&table->simulation_lock);
                return ;
            }
            pthread_mutex_unlock(&table->philo[i].last_meal_lock);
            i++;
        }
    }
}