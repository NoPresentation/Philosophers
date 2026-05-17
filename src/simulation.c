/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:05:40 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/17 16:35:12 by anashwan         ###   ########.fr       */
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
	destroy_locks(table, table->total);
}

static int	init_simulation(t_table *table)
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

static int	init_sim_fail(t_table *table)
{
	destroy_forks(table, table->total);
	free(table->forks);
	return (FAILURE);
}

int	simulation(int argc, long long *args)
{
	t_table	table;

	init_table(&table, argc, args);
	if (init_forks(&table) != OK)
		return (FAILURE);
	if (init_simulation(&table) != OK)
	{
		init_sim_fail(&table);
	}
	monitor(&table);
	clean_up(&table);
	return (OK);
}
