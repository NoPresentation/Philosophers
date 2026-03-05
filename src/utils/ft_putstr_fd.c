/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:16:54 by anashwan          #+#    #+#             */
/*   Updated: 2026/03/05 18:11:28 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

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

void    print_action(t_philo *philo, char *state)
{
	if (!end_simulation(philo->table))
	{
		pthread_mutex_lock(&philo->table->print_lock);
		printf("%lld\t%d %s\n", get_time_ms() - philo->born_time, philo->id, state);
		pthread_mutex_unlock(&philo->table->print_lock);
	}
}