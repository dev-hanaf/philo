/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:49:58 by ahanaf            #+#    #+#             */
/*   Updated: 2024/06/02 14:58:20 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void *monitor(void *arg)
{
    t_data *data;
    unsigned long i;
    unsigned long count = 0;
    data = (t_data *)arg;
    while (!simulation_finished(data))
    {
        i = 0;
        while (i < data->n_philos)
        {
            if (get_time() - data->philos[i].last_meal_time >= data->time_to_die)
            {
                printf("%ld\t\t%ld\t\tdied\n", get_time() - data->start_time, data->philos[i].id);
                set_bool(data, &data->end_simulation, TRUE);
                break;
            }
            if ((int)data->n_limit_meals != -1)
            {
                count = 0;
                unsigned long j = 0;
                while (j < data->n_philos)
                {
                    if (data->philos[j].full)
                    {
                        count++;
                    }
                    j++;
                }
                if (count == data->n_philos)
                {
                    set_bool(data, &data->end_simulation, TRUE);
                    break;
                }
            }
            i++;
        }    
        
    }

    return (NULL);
}
