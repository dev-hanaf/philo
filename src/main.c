/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:35:28 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/15 16:16:18 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	unsigned long	*array;

	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (1);
	}
	array = malloc((ac - 1) * sizeof(unsigned long));
	if (!array)
		return (1);
	if (check_arguments(ac, av, &array))
	{
		free(array);
		return (1);
	}
	if (initial_data(array, ac))
		return (1);
	return (0);
}
