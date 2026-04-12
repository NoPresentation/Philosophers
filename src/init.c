/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:05:33 by anashwan          #+#    #+#             */
/*   Updated: 2026/04/12 18:58:15 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->total);
	if (!table->forks)
		return (1);
	while (i < table->total)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			destroy_forks(table, i);
			free(table->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_philo(t_table *table, int i)
{
	table->philo[i].table = table;
	table->philo[i].id = i + 1;
	table->philo[i].right_fork = &table->forks[(i + 1) % table->total];
	table->philo[i].left_fork = &table->forks[i];
	table->philo[i].last_meal = get_time_ms();
	table->philo[i].born_time = get_time_ms();
}

t_table	*init_table(int argc, long long *args)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->total = args[0];
	table->to_die = args[1];
	table->to_eat = args[2];
	table->to_sleep = args[3];
	if (argc == 6)
		table->must_eat = args[4];
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
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_locks(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->simulation_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->simulation_lock);
		return (1);
	}
	i = 0;
	if (init_philo_locks(table) != 0)
		return (1);
	return (0);
}
