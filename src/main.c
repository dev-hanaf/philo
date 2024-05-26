/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:35:28 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/26 06:22:08 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initial_data(unsigned long *array, int ac)
{
	t_philo	philo;
	
	memset(&philo, 0, sizeof(t_philo));
	if (ac > 5)
	{
		philo.n_time_eat = array[4];
		if (!array[4])
		{
			free(array);
			return (1);
		}
	}	
	philo.n_philos = array[0];
	philo.time_to_die = array[1];
	philo.time_to_eat = array[2];
	philo.time_to_sleep = array[3];
	free(array);
	if (create_philos(&philo))
		return (1);
	return (0);
}

int main(int ac ,char **av) 
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (1);
	}
	unsigned long *array;
	array = malloc((ac -1)  * sizeof(unsigned long));
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