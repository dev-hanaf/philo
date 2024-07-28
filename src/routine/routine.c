/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 00:31:58 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/28 04:11:51 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    check_full(t_philo *philo)
{
    LOCK(&philo->data->full_mutex);
    if (philo->data->meals_arg_exist && philo->meal_counter
        >= philo->data->n_limit_meals)
    {
        philo->full = true;
        UNLOCK(&philo->data->full_mutex);
        return (1);
    }
    UNLOCK(&philo->data->full_mutex);
    return (0);
}

int eat(t_philo *philo)
{
    if (philo->data->n_philos == 1)
    {
        if (write_status(philo, "has taken a fork"))
            return (1);
        return (1337);
    }
    LOCK(philo->first_fork);
    if (write_status(philo, "has taken a fork"))
    {
        UNLOCK(philo->first_fork);
        return (1);
    }
    LOCK(philo->second_fork);
    LOCK(&philo->data->data_mutex);
    philo->last_meal_time = get_time();
    philo->meal_counter++;
    UNLOCK(&philo->data->data_mutex);
    if (write_status(philo, "has taken a fork"))
    {
        UNLOCK(philo->first_fork);
        UNLOCK(philo->second_fork);
        return (1);
    }
    if (write_status(philo, "is eating"))
    {
        UNLOCK(philo->first_fork);
        UNLOCK(philo->second_fork);
        return (1);
    }
    ft_sleep(philo->data->time_to_eat);
    UNLOCK(philo->first_fork);
    UNLOCK(philo->second_fork);
    return (0);
} 

int think(t_philo *philo)
{
    if (write_status(philo, "is thinking"))
        return (1);
    return (0);
}

int _sleep(t_philo *philo)
{
    if (write_status(philo, "is sleeping"))
        return (1);
    ft_sleep(philo->data->time_to_sleep);
    return (0);
}

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        ft_sleep(60);
    LOCK(&philo->data->dead_mutex);
    while (philo->data->end_simulation == false)
    {
        UNLOCK(&philo->data->dead_mutex);
        if (eat(philo))
            return (NULL);
        if (check_full(philo))
            return (NULL);
        if (_sleep(philo))
            return (NULL);
        if (think(philo))
            return (NULL);
        ft_sleep((philo->data->time_to_die - (get_time() - philo->last_meal_time)) / 2);
        LOCK(&philo->data->dead_mutex);
    }
    UNLOCK(&philo->data->dead_mutex);
    return (NULL);
}
