/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:31:56 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/25 02:15:54 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>





int write_status(t_philo *philo, char *str)
{
	LOCK(&philo->data->data_mutex);
	if (philo->data->end_simulation)
	{
		UNLOCK(&philo->data->data_mutex);
		return (1);
	}
	UNLOCK(&philo->data->data_mutex);
	LOCK(&philo->data->write_mutex);
	printf("%zu %zu %s\n", get_time() -  philo->data->start_time ,philo->id, str);
	UNLOCK(&philo->data->write_mutex);
	return (0);
}



// void	next_write_status(t_philo *philo, t_status status)
// {
// 	if (status == THINKING && !philo->data->end_simulation)
// 	{
// 		UNLOCK(&philo->data->data_mutex);
// 		printf("%zu %zu\t is thinking\n", get_time() - philo->data->start_time,
// 			philo->id);
// 	}
// 	else if (status == DIED)
// 	{
// 		UNLOCK(&philo->data->data_mutex);
// 		printf("%zu %zu\t  died\n", get_time() - philo->data->start_time,
// 			philo->id);
// 	}
// 	else
// 		UNLOCK(&philo->data->data_mutex);
// }

// int	write_status(t_philo *philo, t_status status)
// {
// 	LOCK(&philo->data->write_mutex);
// 	LOCK(&philo->data->data_mutex);
// 	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
// 		&& !philo->data->end_simulation)
// 	{
// 		UNLOCK(&philo->data->data_mutex);
// 		printf("%zu %zu has taken a fork\n", get_time()
// 			- philo->data->start_time, philo->id);
// 	}
// 	else if (status == EATING && !philo->data->end_simulation)
// 	{
// 		UNLOCK(&philo->data->data_mutex);
// 		printf("%zu %zu\t is eating\n", get_time() - philo->data->start_time,
// 			philo->id);
// 	}
// 	else if (status == SLEEPING && !philo->data->end_simulation)
// 	{
// 		UNLOCK(&philo->data->data_mutex);
// 		printf("%zu %zu\t is sleeping\n", get_time() - philo->data->start_time,
// 			philo->id);
// 	}
// 	else
// 		next_write_status(philo, status);
// 	UNLOCK(&philo->data->write_mutex);
// }
