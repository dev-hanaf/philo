/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:47:06 by ahanaf            #+#    #+#             */
/*   Updated: 2024/06/02 15:10:33 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int create_philos(t_data *data)
{
    unsigned long   i;
    pthread_t       th;
    i = 0;
    data->start_time = get_time();
    while(i < data->n_philos)
    {
        data->philos[i].last_meal_time = get_time();
        if (pthread_create(&data->philos[i].new_thread , NULL, routine, &data->philos[i]))
            return (1);
        i++;
    }
    if (pthread_create(&th, NULL, monitor, data))
        return (1);
    if (pthread_join(th, NULL))
        return (1);
    if (join_threads(data))
        return (1);
    i = 0;
    while (i < data->n_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        // pthread_mutex_destroy(&data->p[i]);
        i++;
    }
    return (0);
}