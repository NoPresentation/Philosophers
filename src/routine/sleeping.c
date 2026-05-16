/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:30:55 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/15 15:31:03 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *philo)
{
	if (check_simulation_end(philo->table))
		return (FAILURE);
	print_action(philo, "is sleeping");
	if (smart_sleep(philo->table->to_sleep, philo->table) == FAILURE)
		return (FAILURE);
	return (OK);
}
