/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:06:11 by ahanaf            #+#    #+#             */
/*   Updated: 2024/06/03 11:35:41 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int assign_data_to_philo(t_data *data)
{
    unsigned long i;
    
    i = 0;
    while (i < data->n_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].full = FALSE;
        data->philos[i].meal_counter = 0;
        data->philos[i].data = data;
        philo_takes_fork(&data->philos[i], data->forks, i);
        i++;
    }
    return (0);
}
int initializer(t_data *data)
{
    data->philos = malloc(sizeof(t_philo) * data->n_philos);
    if (!data->philos)
        return (1);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
    if (!data->forks)
        return (1);
    if (assign_forks(data))
        return (1);
    if (assign_data_to_philo(data))
        return (1);
    if (pthread_mutex_init(&data->mutex, NULL))
        return (1);
    if (pthread_mutex_init(&data->write_mutex, NULL))
        return (1);
    if (create_philos(data))
        return (1);
    if (pthread_mutex_destroy(&data->mutex))
        return (1);
    if (pthread_mutex_destroy(&data->write_mutex))
        return (1);
    return (0);
}
