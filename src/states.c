/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:19:37 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/15 04:00:57 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	release_forks(pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

static int	grab_forks(t_philo *philo, pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	if (end_simulation(philo->table))
	{
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	if (end_simulation(philo->table))
	{
		release_forks(first_fork, second_fork);
		return (1);
	}
	print_action(philo, "has taken a fork");
	return (0);
}

static int update_meals(t_philo *philo)
{
	if (end_simulation(philo->table))
		return (1);
	pthread_mutex_lock(&philo->meals_lock);
	print_action(philo, "is eating");
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meals_lock);
	if (end_simulation(philo->table))
		return (1);
	if (end_simulation(philo->table))
		return (1);
	ft_usleep(philo->table->to_eat, philo->table);
	pthread_mutex_lock(&philo->meals_lock);
	philo->meals++;
	pthread_mutex_unlock(&philo->meals_lock);
	return (0);
}

static void	eat(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	if (grab_forks(philo, first, second))
		return ;
	if (update_meals(philo))
	{
		release_forks(first, second);
		return ;
	}
	release_forks(first, second);
}

void	eating(t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;
	
	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	eat(philo, first_fork, second_fork);
}

void	sleeping(t_philo *philo)
{
	if (end_simulation(philo->table))
		return ;
	print_action(philo, "is sleeping");
	ft_usleep(philo->table->to_sleep, philo->table);
}

void thinking(t_philo *philo)
{
    if (end_simulation(philo->table))
		return ;
	usleep(500);
}