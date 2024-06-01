/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:52:23 by ahanaf            #+#    #+#             */
/*   Updated: 2024/06/01 16:00:57 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void message(t_philo *philo, const char *s)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	printf("%ld\t\t %ld\t\t %s\n", get_time(), philo->id, s);
	pthread_mutex_unlock(&philo->data->write_mutex);
}


int eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	message(philo, " has taken a right fork");

	pthread_mutex_lock(philo->left_fork);
	message(philo, " has taken a left fork");
	//TODO pthraead_mutex!!
	time_sitter(philo->data, &philo->last_meal_time , get_time());
	message(philo, GREEN"is eating"NC);
	philo->meal_counter++;
	ft_sleep(philo->data->time_to_eat);	
	

	
	pthread_mutex_unlock(philo->right_fork);
	message(philo, "has left a right fork");
	pthread_mutex_unlock(philo->left_fork);
	message(philo, "has left a left fork");

	return (0);
}


int think(t_philo *philo)
{
	message(philo, BLUE"is thinking"NC);
	return (0);
}

int _sleep(t_philo *philo)
{
	message(philo, YELLOW"is sleeping"NC);
	ft_sleep(philo->data->time_to_sleep);	

	return (0);
}


void	*routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	while (!simulation_finished(philo->data))
	{
		eat(philo);
		_sleep(philo);
		think(philo);
	}
	return (NULL);
}
