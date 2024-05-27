/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:06:11 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/27 08:38:29 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int is_thinkig(t_data *data)
// {
//     static int i = 1;

//     pthread_mutex_lock(data->philos);
//     printf("philo |%d| is sleeping 🤔😴\n", i);
//     i++;
//      pthread_mutex_unlock(data->philos);// TODO learn how to lock and unlock
//     ft_sleep(data->time_to_sleep);
//     return (0);
// }

void *start_routine(t_philo *philo)
{
    // (void)philo;
    // is_thinkig(data);
    // pthread_mutex_lock(&philo->r_fork);
    printf("philo: %ld\n", philo->id);
    sleep(1);
    // pthread_mutex_unlock(&philo->r_fork);
    // free(i);
    // ft_sleep(data->time_to_sleep);
    return (NULL);
}

int create_philos(t_data *data)
{
    unsigned long i;
    data->start_time = get_time();
    i = 0;
    while (i < data->n_philos)
    {
        data->id = i;
        data->philos[i].data = data;
        data->philos[i].id = i;
        data->philos[i].finished = 0;
        data->philos[i].last_meal = get_time();
        data->philos[i].times_ate = 0;
       if(pthread_mutex_init(&data->philos[i].r_fork, NULL))
            return (1);
        i++;
    }
    i = 0;
    while (i < data->n_philos)
    {
        // unsigned long  *a = malloc(sizeof(unsigned long));// TODO know should allocated before pass it to the routine
        // if (!a)
        //     return (1);
        // *a = i;  
        if (pthread_create(&data->philos[i].new_thread, NULL, (void *)start_routine, &data->philos[i]))
            return (1);
        i++;
    }
    	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_join(data->philos[i].new_thread, NULL))
            return (1);
		i++;
	}
    // if (join_threads(data))
    //     return (1);
    return (0);
}
