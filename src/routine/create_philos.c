/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:47:06 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/30 10:41:03 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int create_philos(t_data *data)
{
    unsigned long   i;
    
    i = 0;
    // set_bool(data, &data->all_thread_ready, FALSE);
    while(i < data->n_philos)
    {
        if (pthread_create(&data->philos[i].new_thread , NULL, routine, &data->philos[i]))
            return (1);
        i++;
    }
    // set_bool(data, &data->all_thread_ready, TRUE);
    // data->start_time = get_time();
    if (join_threads(data))
        return (1);
    return (0);
}