/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simualation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:35:51 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/19 18:24:39 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>


void thinking(t_philo *philo)
{
    write_status(philo, THINKING);
}

void sleeping(t_philo *philo)
{
    write_status(philo, SLEEPING);
    ft_sleep(philo->data->time_to_sleep);
}

void eat(t_philo *philo)
{
    LOCK(philo->right_fork);
    write_status(philo, TAKE_FIRST_FORK);
    LOCK(philo->left_fork);
    write_status(philo, TAKE_SECOND_FORK);

   LOCK(&philo->philo_mutex);
   philo->last_meal_time = get_time();
   UNLOCK(&philo->philo_mutex);


    write_status(philo, EATING);
    philo->meal_counter++;

    ft_sleep(philo->data->time_to_eat);

    if (philo->data->meals_arg_exist && philo->meal_counter == philo->data->n_limit_meals)
    {
        LOCK(&philo->philo_mutex);
        philo->full = TRUE;
        UNLOCK(&philo->philo_mutex);
    }
   
    UNLOCK(philo->right_fork);
    UNLOCK(philo->left_fork);

}

void   increase_threads(t_data *data)
{
    LOCK(&data->data_mutex);
    data->thread_running_nbr++;
    UNLOCK(&data->data_mutex);
}


int all_threads_running(t_data *data)
{
    int result;

    result = FALSE;
    LOCK(&data->data_mutex); 
    if (data->thread_running_nbr == data->n_philos)
        result = TRUE;
    UNLOCK(&data->data_mutex);
    return (result);
}

void *routine(void *arg)
{
    t_philo *philo;
    int end;

    philo = (t_philo *)arg;

    LOCK(&philo->philo_mutex); 
    philo->last_meal_time = get_time();
    UNLOCK(&philo->philo_mutex); 

    increase_threads(philo->data);
    
    LOCK(&philo->data->data_mutex);
    end = philo->data->end_simulation;
    UNLOCK(&philo->data->data_mutex);

    while(!end)
    {                                                                                                 
        LOCK(&philo->data->data_mutex);
        end = philo->data->end_simulation;
        UNLOCK(&philo->data->data_mutex);   
        LOCK(&philo->philo_mutex);
        if (philo->full == TRUE)
        {
            UNLOCK(&philo->philo_mutex);
            break;
        }
        UNLOCK(&philo->philo_mutex);
        eat(philo);
        thinking(philo);
        sleeping(philo);

    }
    return (NULL);
}
