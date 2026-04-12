/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:05:21 by anashwan          #+#    #+#             */
/*   Updated: 2026/04/12 19:26:48 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	end_simulation(t_table *table)
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
		print_action(philo, "has taken a fork");
		ft_usleep(philo->table->to_die, philo->table);
		return (1);
	}
	return (0);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (single_philo(philo) != 0)
		return (NULL);
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
