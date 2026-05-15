/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:30:23 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/15 15:30:37 by anashwan         ###   ########.fr       */
/*                                            h                                */
/* ************************************************************************** */

# include "philo.h"

static void	release_forks(pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

static int	grab_forks(t_philo *philo, pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	if (check_simulation_end(philo->table))
	{
		pthread_mutex_unlock(first_fork);
		return (FAILURE);
	}
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	if (check_simulation_end(philo->table))
	{
		release_forks(first_fork, second_fork);
		return (FAILURE);
	}
	print_action(philo, "has taken a fork");
	return (OK);
}

static int update_meals(t_philo *philo)
{
	if (check_simulation_end(philo->table))
		return (FAILURE);
	pthread_mutex_lock(&philo->meals_lock);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meals_lock);
	if (check_simulation_end(philo->table))
		return (FAILURE);
	print_action(philo, "is eating");
	if (smart_sleep(philo->table->to_eat, philo->table) == FAILURE)
		return (FAILURE);
	if (check_simulation_end(philo->table))
		return (FAILURE);
	pthread_mutex_lock(&philo->meals_lock);
	philo->meals++;
	pthread_mutex_unlock(&philo->meals_lock);
	return (OK);
}

static void	set_forks(t_philo *philo, pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
	else
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
}

int	eating(t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;

	set_forks(philo, &first_fork, &second_fork);
	if (check_simulation_end(philo->table))
		return (FAILURE);
	if (grab_forks(philo, first_fork, second_fork) == FAILURE)
		return (FAILURE);
	if (update_meals(philo) == FAILURE)
	{
		release_forks(first_fork, second_fork);
		return (FAILURE);
	}
	release_forks(first_fork, second_fork);
	return (OK);
}
