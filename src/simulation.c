/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:05:40 by anashwan          #+#    #+#             */
/*   Updated: 2026/03/24 20:37:42 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_simulation(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->total);
	if (!table->philo)
		return (1);
	if (init_locks(table) != 0)
	{
		free(table->philo);
		return (1);
	}
	table->start_time = get_time_ms();
	while (i < table->total)
	{
		init_philo(table, i);
		if (pthread_create(&table->philo[i].thread, NULL, routine,
				&table->philo[i]) != 0)
		{
			destroy_threads(table, i);
			free(table->philo);
			return (1);
		}
		i++;
	}
	return (0);
}

int	simulation(int argc, long long *args)
{
	t_table	*table;

	table = init_table(argc, args);
	if (!table)
		return (1);
	if (init_forks(table) != 0)
	{
		free(table);
		return (1);
	}
	if (init_simulation(table) != 0)
	{
		free(table->forks);
		free(table);
		return (1);
	}
	monitor(table);
	clean_up(table);
	return (0);
}
