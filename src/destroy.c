/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:05:30 by anashwan          #+#    #+#             */
/*   Updated: 2026/04/12 18:58:03 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	destroy_forks(t_table *table, int forks)
{
	int	i;

	i = 0;
	while (i < forks)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}

void	destroy_threads(t_table *table, int threads)
{
	int	i;

	i = 0;
	while (i < threads)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
}

void	destroy_locks(t_table *table, int philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->simulation_lock);
	pthread_mutex_destroy(&table->print_lock);
	while (i < philos)
	{
		pthread_mutex_destroy(&table->philo[i].meals_lock);
		i++;
	}
}

void	clean_up(t_table *table)
{
	destroy_threads(table, table->total);
	destroy_forks(table, table->total);
	destroy_locks(table, table->total);
	free(table->forks);
	free(table->philo);
	free(table);
}
