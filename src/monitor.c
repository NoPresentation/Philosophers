	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   monitor.c                                          :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2026/03/24 19:05:28 by anashwan          #+#    #+#             */
	/*   Updated: 2026/04/14 03:38:06 by anashwan         ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

#include "../inc/philo.h"

static void stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->simulation_lock);
	table->simulation = 0;
	pthread_mutex_unlock(&table->simulation_lock);
}

static void	announce_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%lld\t%d %s\n", get_time_ms() - philo->born_time, philo->id,
		"died");
	pthread_mutex_unlock(&philo->table->print_lock);
}

static int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_lock);
	if (get_time_ms() - philo->last_meal > philo->table->to_die)
	{
		stop_simulation(philo->table);
		pthread_mutex_unlock(&philo->meals_lock);
		announce_death(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->meals_lock);
	return (0);
}

static int	check_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_lock);
	if (philo->meals >= philo->table->must_eat)
	{
		pthread_mutex_unlock(&philo->meals_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meals_lock);
	return (0);
}

void	monitor(t_table *table)
{
	int	i;
	int	full_philos;

	while (!check_simulation_end(table))
	{
		i = 0;
		full_philos = 0;
		while (i < table->total)
		{
			if (check_dead(&table->philo[i]))
				return ;
			if (table->must_eat != -1 && check_full(&table->philo[i]))
				full_philos++;
			i++;
		}
		if (table->must_eat != -1 && full_philos >= table->total)
		{
			stop_simulation(table);
			return ;
		}
		usleep(500);
	}
}
