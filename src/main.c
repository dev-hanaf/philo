/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:35:28 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/27 06:49:40 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int controller(t_data *data)
{
	if (create_philos(data))
		return (1);
	
	return (0);
}


int	initial_data(unsigned long *array, int ac)
{
	t_data	data;
	
	memset(&data, 0, sizeof(t_data));
	if (ac > 5)
	{
		data.n_time_eat = array[4];
		if (!array[4])
		{
			free(array);
			return (1);
		}
	}	
	data.n_philos = array[0];
	data.time_to_die = array[1];
	data.time_to_eat = array[2];
	data.time_to_sleep = array[3];
	free(array);
	if (data.n_philos == 1 || 0 )
	{
		printf("should be at least 2 philosofres\n");
		return (1);
	}
	if (controller(&data))
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
