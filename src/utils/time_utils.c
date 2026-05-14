/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:06:02 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/14 22:19:08 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

long long	get_time_ms(void)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (time);
}


/*
	Why make a separate function fo
*/
int	ft_usleep(long duration, t_table *table)
{
	long	start;

	start = get_time_ms();
	while (!end_simulation(table))
	{
		if (end_simulation(table))
			return (FAILURE);
		if (get_time_ms() - start >= duration)
			break ;
		usleep(300);
	}
	return (SUCCESS);
}
