/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 06:37:56 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/27 07:01:01 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_data *data)
{
	unsigned long	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_join(data->philos[i].new_thread, NULL))
            return (1);
		i++;
	}
    return (0);
}
