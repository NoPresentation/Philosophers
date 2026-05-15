/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:05:40 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/15 15:37:07 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->simulation_lock);
	table->simulation = 0;
	pthread_mutex_unlock(&table->simulation_lock);
}

static void	thread_fail_cleanup(t_table *table, int threads)
{
	stop_simulation(table);
	destroy_threads(table, threads);
}

int	init_simulation(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->total);
	if (!table->philo)
		return (FAILURE);
	if (init_locks(table) != 0)
	{
		free(table->philo);
		return (FAILURE);
	}
	table->start_time = get_time_ms();
	while (i < table->total)
	{
		init_philo(table, i);
		if (pthread_create(&table->philo[i].thread, NULL, routine,
				&table->philo[i]) != 0)
		{
			thread_fail_cleanup(table, i);
			free(table->philo);
			return (FAILURE);
		}
		i++;
	}
	return (OK);
}

int	simulation(int argc, long long *args)
{
	t_table	*table;

	table = init_table(argc, args);
	if (!table)
		return (FAILURE);
	if (init_forks(table) != OK)
	{
		free(table);
		return (FAILURE);
	}
	if (init_simulation(table) != OK)
	{
		free(table->forks);
		free(table);
		return (FAILURE);
	}
	monitor(table);
	clean_up(table);
	return (OK);
}
