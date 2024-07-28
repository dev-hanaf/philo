/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:31:56 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/28 04:01:56 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>





int write_status(t_philo *philo, char *str)
{
	LOCK(&philo->data->dead_mutex);
	if (philo->data->end_simulation)
	{
		UNLOCK(&philo->data->dead_mutex);
		return (1);
	}
	printf("%zu %zu %s\n", get_time() -  philo->data->start_time ,philo->id, str);
	UNLOCK(&philo->data->dead_mutex);
	return (0);
}
