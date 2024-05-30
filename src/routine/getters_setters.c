/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:57:52 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/30 10:33:26 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_bool(t_data *data, int *dest,int value)
{
    pthread_mutex_lock(&data->mutex);
    *dest = value;
    pthread_mutex_unlock(&data->mutex);
}

int    get_bool(t_data *data, int value)
{
    int ret;
    
    pthread_mutex_lock(&data->mutex);
    ret = value;
    pthread_mutex_unlock(&data->mutex);
    return (ret);
}

int simulation_finished(t_data *data)
{
    return (get_bool(data, data->end_simulation));
}
