/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:19:37 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/06 16:10:45 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	eat(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meals_lock);
	philo->last_meal = get_time_ms();
	philo->meals++;
	pthread_mutex_unlock(&philo->meals_lock);
	ft_usleep(philo->table->to_eat, philo->table);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		eat(philo, philo->right_fork, philo->left_fork);
	}
	else
	{
		eat(philo, philo->left_fork, philo->right_fork);
	}
}

void	sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->table->to_sleep, philo->table);
}

void	thinking(t_philo *philo)
{
	long long	think_time;

	print_action(philo, "is thinking");
	think_time = philo->table->to_die - philo->table->to_eat
		- philo->table->to_sleep;
	if (think_time <= 0)
		think_time = 1;
	else
		think_time = think_time / 2;
	ft_usleep(think_time, philo->table);
}
