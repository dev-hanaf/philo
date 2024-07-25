/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:06:26 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/25 03:03:05 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_data *data)
{
	unsigned long	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->philos[i].philo_mutex);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->write_mutex);
}

int	controller(t_data *data)
{
	data->forks = NULL;
	data->philos = NULL;
	if (initializer(data))
	{
		clean(data);
		free(data->philos);
		free(data->forks);
		return (1);
	}
	clean(data);
	free(data->forks);
	free(data->philos);
	return (0);
}

void	*one_thread(void *arg)
{
	t_philo	*philo;
	int		end;

	end = FALSE;
	philo = (t_philo *)arg;
	LOCK(&philo->philo_mutex);
	philo->last_meal_time = get_time();
	UNLOCK(&philo->philo_mutex);
	increase_threads(philo->data);
	write_status(philo, "has take a fork");
	LOCK(&philo->data->data_mutex);
	end = philo->data->end_simulation;
	UNLOCK(&philo->data->data_mutex);
	while (!end)
	{
		LOCK(&philo->data->data_mutex);
		end = philo->data->end_simulation;
		UNLOCK(&philo->data->data_mutex);
		usleep(200);
	}
	return (NULL);
}

int	one_thread_init(t_data *data)
{
	data->start_time = get_time();
	data->end_simulation = FALSE;
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (1);
	data->philos[0].id = 1;
	data->philos[0].full = 0;
	data->philos[0].data = data;
	data->philos[0].last_meal_time = get_time();
	if (pthread_mutex_init(&data->philos[0].philo_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->data_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->write_mutex, NULL))
		return (1);
	if (pthread_create(&data->monitor_th, NULL, monitor, data))
		return (1);
	if (pthread_create(&data->philos[0].thread_id, NULL, one_thread,
			&data->philos[0]))
		return (1);
	if (pthread_join(data->philos[0].thread_id, NULL))
		return (1);
	if (pthread_join(data->monitor_th, NULL))
		return (1);
	return (0);
}

int	initial_data(unsigned long *array, int ac)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (ac > 5)
	{
		data.n_limit_meals = array[4];
		data.meals_arg_exist = TRUE;
	}
	data.n_philos = array[0];
	data.time_to_die = array[1];
	data.time_to_eat = array[2];
	data.time_to_sleep = array[3];
	free(array);
	if (data.n_philos == 0)
		return (1);
	if (data.n_philos == 1)
	{
		if (one_thread_init(&data))
			return (1);
		return (0);
	}
	if (controller(&data))
		return (1);
	return (0);
}
