/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:06:26 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/16 09:51:00 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	controller(t_data *data)
{
	data->forks = NULL;
	data->philos = NULL;
	if (initializer(data))
	{
		free(data->philos);
		free(data->forks);
		return (1);
	}

	free(data->forks);
	free(data->philos);
	return (0);
}

/*          ms		 ms      ms      ms    
./philo		5		800		200		200		[5]
		  av[1]	   av[2]    av[3]   av[4]
 */
int	initial_data(unsigned long *array, int ac)
{
	t_data	data;
	
	memset(&data, 0, sizeof(t_data));
	if (ac > 5)
	{
		data.n_limit_meals = array[4];
	}
	else 
		data.meals_arg_exist = TRUE;
	data.n_philos = array[0];
	data.time_to_die = array[1];
	data.time_to_eat = array[2];
	data.time_to_sleep = array[3];
	free(array);
	if (data.n_philos ==  0)
	{
		printf("should be at least 1 philosofres\n");
		return (1);
	}
	if (data.n_philos == 1)
		return (1);
	// 	//TODO fix that
	if(controller(&data))
		return (1);
	return (0);
}
