/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:05:21 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/16 16:04:17 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simulation_end(t_table *table)
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

int	single_philo(t_philo *philo)
{
	if (philo->table->total == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		smart_sleep(philo->table->to_die, philo->table);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (single_philo(philo))
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_simulation_end(philo->table))
			return (NULL);
		if (eating(philo) == FAILURE || sleeping(philo) == FAILURE
			|| thinking(philo) == FAILURE)
			return (NULL);
	}
	return (NULL);
}
