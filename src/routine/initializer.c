/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:06:11 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/29 08:13:28 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_up(t_data *data, t_status status, unsigned long i)
{
	if (status == ALL || status == FORKS || status == DATA || status == DEAD)
	{
		while (i < data->n_philos)
		{
			if (MUTEX_DEST(&data->forks[i]))
				return (1);
			i++;
		}
	}
	if (status == ALL || status == DATA || status == DEAD)
	{
		if (MUTEX_DEST(&data->data_mutex))
			return (1);
	}
	if (status == ALL || status == DEAD)
	{
		if (MUTEX_DEST(&data->dead_mutex))
			return (1);
	}
	if (status == ALL || status == FULL)
	{
		if (MUTEX_DEST(&data->full_mutex))
			return (1);
	}
	return (1);
}

int	init_forks(t_data *data)
{
	unsigned long	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (MUTEX_INIT(&data->forks[i], NULL))
			return (clean_up(data, FORKS, 0));
		i++;
	}
	if (MUTEX_INIT(&data->data_mutex, NULL))
		return (clean_up(data, DATA, 0));
	if (MUTEX_INIT(&data->dead_mutex, NULL))
		return (clean_up(data, DEAD, 0));
	if (MUTEX_INIT(&data->full_mutex, NULL))
		return (clean_up(data, ALL, 0));
	return (0);
}

int	init_philos(t_data *data)
{
	unsigned long	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time = get_time();
		data->philos[i].full = false;
		data->philos[i].meal_counter = 0;
		data->philos[i].data = data;
		data->philos[i].first_fork = &data->forks[i];
		data->philos[i].second_fork = &data->forks[(i + 1) % (data->n_philos)];
		if (data->n_philos - 1 == i)
		{
			data->philos[i].first_fork = &data->forks[(i + 1)
				% (data->n_philos)];
			data->philos[i].second_fork = &data->forks[i];
		}
		i++;
	}
	return (0);
}

int	create_theads(t_data *data)
{
	unsigned long	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->n_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &routine,
				&data->philos[i]))
			return (1);
		i++;
	}
	i = 0;
	if (monitor(data))
		return (1);
	while (i < data->n_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	initializer(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (1);
	if (init_forks(data))
		return (1);
	if (init_philos(data))
		return (1);
	if (create_theads(data))
		return (1);
	return (0);
}
