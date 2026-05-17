/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:05:35 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/17 16:32:05 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	long long	args[5];

	if ((argc != 6 && argc != 5) || get_args(argc, args, argv) == FAILURE)
	{
		ft_putstr_fd("Invalid arguments.\n", 2);
		return (EXIT_FAILURE);
	}
	if (simulation(argc, args) != 0)
	{
		ft_putstr_fd("Error\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
