/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:51:18 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/20 00:24:35 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int is_full(t_data *data)
{
    unsigned long i;
    // unsigned long counter = 0;
    i =  0;
    
    while (i < data->n_philos)
    {
        LOCK(&data->philos[i].philo_mutex);
        if (data->philos[i].full == FALSE)
        {
            UNLOCK(&data->philos[i].philo_mutex);
            return (FALSE);
        }
        UNLOCK(&data->philos[i].philo_mutex);
        i++;
    }
    return (TRUE);
}

int philo_died(t_philo *philo)
{
    size_t time;
    size_t time_to_die;

    unsigned long t_last_meal;
    int is_full;
    
    LOCK(&philo->philo_mutex);
    is_full = philo->full; 
    UNLOCK(&philo->philo_mutex);
    if (is_full)
        return (FALSE);

    LOCK(&philo->philo_mutex);
    t_last_meal = philo->last_meal_time; 
    UNLOCK(&philo->philo_mutex);

    time = get_time() - t_last_meal;

    time_to_die = philo->data->time_to_die;
    if (time > time_to_die)
        return (TRUE);
    return (FALSE);
}


void *monitor(void *arg)
{
    t_data *data;
    unsigned long i;
    int end = FALSE;
    
    data = (t_data *)arg;
    while (!all_threads_running(data))
    ;
    LOCK(&data->data_mutex);
    end = data->end_simulation;
    UNLOCK(&data->data_mutex);
    while(!end)
    {

        i = 0;
        if (i < data->n_philos &&  !end)
        {
            if (is_full(data))
            {
               LOCK(&data->data_mutex);
                data->end_simulation = TRUE;
                UNLOCK(&data->data_mutex);
                break;       
            }
            if (philo_died(&data->philos[i]))
            {
                LOCK(&data->data_mutex);
                data->end_simulation = TRUE;
                UNLOCK(&data->data_mutex);
                write_status(&data->philos[i], DIED);
                break;
            }
            i++;
        }        
        LOCK(&data->data_mutex);
        end = data->end_simulation;
        UNLOCK(&data->data_mutex);
    }
    return (NULL);
}