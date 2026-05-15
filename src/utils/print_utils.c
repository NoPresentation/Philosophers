/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:54 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/15 17:19:48 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	print_action(t_philo *philo, char *state)
{
	if (check_simulation_end(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->print_lock);
	if (check_simulation_end(philo->table))
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return ;
	}
	printf("%lld\t%d %s\n", get_time_ms() - philo->table->start_time, philo->id,
		state);
	pthread_mutex_unlock(&philo->table->print_lock);
}
