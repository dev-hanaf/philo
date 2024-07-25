/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simualation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:35:51 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/25 02:55:24 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	thinking(t_philo *philo)
{
	if (write_status(philo, "is thinking"))
		return (1);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (write_status(philo, "is sleeping"))
		return (1);
	ft_sleep(philo->data->time_to_sleep);
	return (0);
}

int	eat(t_philo *philo)
{
	// if (philo->id % 2 == 0)
	// {	
		LOCK(philo->right_fork);
		if (write_status(philo, "has taken a fork"))
		{
			UNLOCK(philo->right_fork);
			return (1);
		}
		LOCK(philo->left_fork);
		if (write_status(philo, "has taken a fork"))
		{
			UNLOCK(philo->right_fork);
			UNLOCK(philo->left_fork);
			return (1);
		}
	// }
	// else
	// {
	// 	LOCK(philo->left_fork);
		// write_status(philo, TAKE_SECOND_FORK);
		// LOCK(philo->right_fork);
		// write_status(philo, TAKE_FIRST_FORK);
	// }
	LOCK(&philo->philo_mutex);
	philo->last_meal_time = get_time();
	UNLOCK(&philo->philo_mutex);
	if (write_status(philo, "eating"))
	{
		UNLOCK(philo->right_fork);
		UNLOCK(philo->left_fork);
		return (1);
	}
	philo->meal_counter++;
	ft_sleep(philo->data->time_to_eat);
	if (philo->data->meals_arg_exist
		&& philo->meal_counter == philo->data->n_limit_meals)
	{
		LOCK(&philo->philo_mutex);
		philo->full = TRUE;
		UNLOCK(&philo->philo_mutex);
	}
	UNLOCK(philo->right_fork);
	UNLOCK(philo->left_fork);
	return (0);
}

void	increase_threads(t_data *data)
{
	LOCK(&data->data_mutex);
	data->thread_running_nbr++;
	UNLOCK(&data->data_mutex);
}

int	all_threads_running(t_data *data)
{
	int	result;

	result = FALSE;
	LOCK(&data->data_mutex);
	if (data->thread_running_nbr == data->n_philos)
		result = TRUE;
	UNLOCK(&data->data_mutex);
	return (result);
}

void	wait_for_threads(t_philo *philo)
{
	while (1)
	{
		LOCK(&philo->data->data_mutex);
		if (philo->data->is_all_thread_created)
		{
			UNLOCK(&philo->data->data_mutex);
			break ;
		}
		UNLOCK(&philo->data->data_mutex);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// wait_for_threads(philo);
	// LOCK(&philo->philo_mutex);
	// philo->last_meal_time = get_time();
	// UNLOCK(&philo->philo_mutex);
	increase_threads(philo->data);
	while (TRUE)
	{
		// LOCK(&philo->philo_mutex);
		// if (philo->full == TRUE)
		// {
		// 	UNLOCK(&philo->philo_mutex);
		// 	break ;
		// }
		// UNLOCK(&philo->philo_mutex);
		if (thinking(philo))
			break;
		if (eat(philo))
			break;
		if (sleeping(philo))
			break;
		ft_sleep((philo->data->time_to_die - (get_time() - philo->last_meal_time)) / 2);
	}
	return (NULL);
}
