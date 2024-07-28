/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:10:09 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/28 04:00:53 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_is_full(t_data *data)
{
	unsigned long	i;

	i = 0;
	while (i < data->n_philos)
	{
		LOCK(&data->full_mutex);
		if (data->philos[i].full == false)
		{
			UNLOCK(&data->full_mutex);
			return (1);
		}
		UNLOCK(&data->full_mutex);
		i++;
	}
	return (0);
}

void	is_full(t_data *data, bool *flag)
{
	unsigned long	i;

	i = 0;
	while (i < data->n_philos && *flag)
	{
		if (!all_is_full(data))
		{
			LOCK(&data->dead_mutex);
			data->end_simulation = true;
			UNLOCK(&data->dead_mutex);
			*flag = false;
			break ;
		}
		i++;
	}
}

void	is_dead(t_data *data, bool *flag)
{
	unsigned long	i;

	i = 0;
	while (i < data->n_philos && *flag)
	{
		LOCK(&data->data_mutex);
		if (data->philos[i].last_meal_time != 0 && get_time()
			- data->philos[i].last_meal_time > data->time_to_die)
		{
			UNLOCK(&data->data_mutex);
			LOCK(&data->dead_mutex);
			data->end_simulation = true;
			printf("%zu %zu %s\n", get_time() - data->start_time,
				data->philos[i].id, "dead");
			UNLOCK(&data->dead_mutex);
			*flag = false;
			break ;
		}
		UNLOCK(&data->data_mutex);
		i++;
	}
}

int	monitor(t_data *data)
{
	bool	flag;

	flag = true;
	while (flag)
	{
		is_full(data, &flag);
		if (flag)
			is_dead(data, &flag);
	}
	return (0);
}
