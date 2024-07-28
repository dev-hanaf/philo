/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:31:56 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/28 04:20:33 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	write_status(t_philo *philo, char *str)
{
	LOCK(&philo->data->dead_mutex);
	if (philo->data->end_simulation)
	{
		UNLOCK(&philo->data->dead_mutex);
		return (1);
	}
	printf("%zu %zu %s\n", get_time() - philo->data->start_time, philo->id,
		str);
	UNLOCK(&philo->data->dead_mutex);
	return (0);
}

int	write_philo_info(t_philo *philo)
{
	LOCK(philo->first_fork);
	if (write_status(philo, "has taken a fork"))
	{
		UNLOCK(philo->first_fork);
		return (1);
	}
	LOCK(philo->second_fork);
	LOCK(&philo->data->data_mutex);
	philo->last_meal_time = get_time();
	philo->meal_counter++;
	UNLOCK(&philo->data->data_mutex);
	if (write_status(philo, "has taken a fork"))
	{
		UNLOCK(philo->first_fork);
		UNLOCK(philo->second_fork);
		return (1);
	}
	return (0);
}
