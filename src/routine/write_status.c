/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:31:56 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/17 15:01:03 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>


void    write_status(t_philo *philo, t_status status)
{
    size_t time;

    time = get_time() - philo->data->start_time;
    LOCK(&philo->data->write_mutex);
    LOCK(&philo->data->data_mutex);
    if ((status ==  TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !philo->data->end_simulation)
    {
        UNLOCK(&philo->data->data_mutex);
        printf("%zu %zu has taken a fork\n", time , philo->id);   
    }
    else if (status == EATING && !philo->data->end_simulation)
    {
        UNLOCK(&philo->data->data_mutex);
        printf("%zu %zu\t is eating\n", time, philo->id);   
    }
    else if (status == SLEEPING && !philo->data->end_simulation)
    {
        UNLOCK(&philo->data->data_mutex);
        printf("%zu %zu\t is sleeping\n", time, philo->id);   
    }
    else if (status == THINKING && !philo->data->end_simulation)
    {
        UNLOCK(&philo->data->data_mutex);
        printf("%zu %zu\t is thinking\n", time, philo->id);   
    }
    else if (status == DIED)
    {
        UNLOCK(&philo->data->data_mutex);
        printf("%zu %zu\t  died\n", time, philo->id);   
    }
    else
        UNLOCK(&philo->data->data_mutex);
    UNLOCK(&philo->data->write_mutex);
}
