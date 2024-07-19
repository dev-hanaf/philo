/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:06:11 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/19 17:28:50 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void grab_forks(t_data *data, t_philo *philo, unsigned long i)
{
    unsigned long nbr_philos;
    
    nbr_philos = data->n_philos;
    if (philo->id % 2 == 0)//even
    {
        // printf("philo[%zu] takes right fork %zu\n", philo->id, i);
        philo->right_fork = &data->forks[i];
        philo->left_fork = &data->forks[(i + 1) % nbr_philos];
        // printf("philo[%zu] takes left fork %zu\n", philo->id, (i + 1) % nbr_philos);

    }
    else
    {
        // printf("philo[%zu] takes right fork %zu\n", philo->id, i);
        philo->right_fork = &data->forks[(i + 1) % nbr_philos];
        philo->left_fork = &data->forks[i];
        // printf("philo[%zu] takes left fork %zu\n", philo->id, (i + 1) % nbr_philos);
    }
}

int join_threads(t_data *data)
{
    unsigned long i;

    i = 0;
    while (i < data->n_philos)
    {
        if (pthread_join(data->philos[i].thread_id, NULL))
            return (1);
        i++;
    }
    return (0);
} 

int create_threads(t_data *data)
{
    unsigned long i;

    i = 0;
    while (i < data->n_philos)
    {
        if (pthread_create(&data->philos[i].thread_id, NULL, routine, &data->philos[i]))
            return (1);
        i++;
    }
    if (join_threads(data))
        return (1);
    if (pthread_join(data->monitor_th, NULL))
        return (1);
    return (0);
}

int initializer(t_data *data)
{
    unsigned long i;
    
    i = 0;
    data->start_time = get_time();
    data->end_simulation = FALSE;
    data->philos = malloc(sizeof(t_philo) * data->n_philos);
    if (!data->philos)
        return (1);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
    if (!data->forks)
        return (1); 
    while(i < data->n_philos)
    {
        data->philos[i].id = i + 1;
        data->thread_running_nbr = 0;
        data->philos[i].full = FALSE;
        data->philos[i].data = data;
        data->philos[i].last_meal_time = get_time();
        if (pthread_mutex_init(&data->philos[i].philo_mutex, NULL))
            return (1);
        if (pthread_mutex_init(&data->forks[i], NULL))
            return (1);
        grab_forks(data, &data->philos[i], i);
        i++;
    }
    if (pthread_mutex_init(&data->data_mutex, NULL))
        return (1);
    if (pthread_mutex_init(&data->write_mutex, NULL))
        return (1);
    if (pthread_create(&data->monitor_th, NULL, monitor, data))
        return (1);
    if (create_threads(data))
        return (1);
    //because also the monitor whaits for the variable end simulation.
    //so  if all start simualtion ends stop the monitor
    LOCK(&data->data_mutex);
    data->end_simulation = TRUE;
    UNLOCK(&data->data_mutex);
    return (0);
}
