/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:19:37 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/14 22:21:46 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	release_forks(pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

static int	grab_forks(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	if (end_simulation(philo->table))
		return (FAILURE);
	pthread_mutex_lock(first);
	if (end_simulation(philo->table))
	{
		pthread_mutex_unlock(first);
		return (FAILURE);
	}
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second);
	if (end_simulation(philo->table))
	{
		release_forks(first, second);
		return (FAILURE);
	}
	print_action(philo, "has taken a fork");
	return (SUCCESS);
}

static int	update_meals(t_philo *philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meals_lock);
	philo->last_meal = get_time_ms();
	if (ft_usleep(philo->table->to_eat, philo->table) == FAILURE)
	{
		pthread_mutex_unlock(&philo->meals_lock);
		return (FAILURE);
	}
	philo->meals++;
	pthread_mutex_unlock(&philo->meals_lock);
	return (SUCCESS);
}

/*
Changes and reasons:
1. Add functions like: grab_forks, release_forks, update_meals - Reasons:
	- Better separation of concerns
	- Better responsibility separation
	- Easier to track simulation state
	- Overall better readability (i think)
2. Add return value - Reasons:
	- Better for reporting if the action has been successfully done
*/
static int	eat(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	if (grab_forks(philo, first, second))
		return (FAILURE);
	if (end_simulation(philo->table))
	{
		release_forks(first, second);
		return (FAILURE);
	}
	if (update_meals(philo) == FAILURE)
	{
		release_forks(first, second);
		return (FAILURE);
	}
	release_forks(first, second);
	return (SUCCESS);
}


/*
Changes and their reasons:
- Clearer fork aquisition: to avoid duplicate logic and to allow for clearer error handling for the return value of eat()
- Add return value: To stop simulation accurately
*/
int	eating(t_philo *philo)
{
	pthread_mutex_t *first;
	pthread_mutex_t *second;

	if (philo->id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	if (eat(philo, first, second) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->table->to_sleep, philo->table);
}

void	thinking(t_philo *philo)
{
	print_action(philo, "is thinking");
	usleep(500);
}


/*
void	thinking(t_philo *philo)
{
	long long	think_time;

	print_action(philo, "is thinking");
	think_time = philo->table->to_die - philo->table->to_eat
		- philo->table->to_sleep;
	if (think_time < 0)
	{
		think_time = philo->table->to_eat / 2;
	}
	ft_usleep(think_time, philo->table);
}

*/