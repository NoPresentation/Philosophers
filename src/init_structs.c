/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:05:33 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/15 15:37:07 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->total);
	if (!table->forks)
		return (FAILURE);
	while (i < table->total)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			destroy_forks(table, i);
			free(table->forks);
			return (FAILURE);
		}
		i++;
	}
	return (OK);
}

void	init_philo(t_table *table, int i)
{
	table->philo[i].table = table;
	table->philo[i].id = i + 1;
	table->philo[i].right_fork = &table->forks[(i + 1) % table->total];
	table->philo[i].left_fork = &table->forks[i];
	table->philo[i].last_meal = table->start_time;
	table->philo[i].meals = 0;
}

t_table	*init_table(int argc, long long *args)
{
	t_table	*table;
	
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->total = args[TOTAL];
	table->to_die = args[TIME_TO_DIE];
	table->to_eat = args[TIME_TO_EAT];
	table->to_sleep = args[TIME_TO_SLEEP];
	if (argc == 6)
		table->must_eat = args[MEAL_LIMIT];
	else
		table->must_eat = -1;
	table->simulation = 1;
	return (table);
}

static int	init_philo_locks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->total)
	{
		if (pthread_mutex_init(&table->philo[i].meals_lock, NULL) != 0)
		{
			destroy_locks(table, i);
			return (FAILURE);
		}
		i++;
	}
	return (OK);
}

int	init_locks(t_table *table)
{
	if (pthread_mutex_init(&table->simulation_lock, NULL) != 0)
		return (FAILURE);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->simulation_lock);
		return (FAILURE);
	}
	if (init_philo_locks(table) != 0)
		return (FAILURE);
	return (OK);
}
