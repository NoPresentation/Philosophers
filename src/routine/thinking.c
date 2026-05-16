/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:31:16 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/16 15:54:20 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_philo *philo)
{
	if (check_simulation_end(philo->table))
		return (FAILURE);
	print_action(philo, "is thinking");
	usleep(1000);
	return (OK);
}
