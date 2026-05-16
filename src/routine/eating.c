/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:18:40 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/15 17:18:43 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	release_forks(pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

static int	grab_forks(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	if (check_simulation_end(philo->table))
	{
		pthread_mutex_unlock(first);
		return (FAILURE);
	}
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second);
	if (check_simulation_end(philo->table))
	{
		release_forks(first, second);
		return (FAILURE);
	}
	print_action(philo, "has taken a fork");
	return (OK);
}

static int	update_meals(t_philo *philo)
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

static void	set_forks(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	else
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
}

int	eating(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	set_forks(philo, &first, &second);
	if (check_simulation_end(philo->table))
		return (FAILURE);
	if (grab_forks(philo, first, second) == FAILURE)
		return (FAILURE);
	if (update_meals(philo) == FAILURE)
	{
		release_forks(first, second);
		return (FAILURE);
	}
	release_forks(first, second);
	return (OK);
}
