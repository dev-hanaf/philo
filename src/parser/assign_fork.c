/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:30:33 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/30 09:25:48 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int assign_forks(t_data *data)
{
    unsigned long   i;

    i = 0;
    while (i < data->n_philos)
    {
        if (pthread_mutex_init(&data->forks[i].fork, NULL))
            return (1);
        data->forks[i].fork_id = i;//for debug
        i++;
    }
    return (0);
}

/* 
right_fork  = philo->id -1;
left_fork   = (philo->id + 1) % n_philos;
            ==> (5 + 1) % 5 = 1


if (odd) first_left;
elif (even) first_right;
 */

void    philo_takes_fork(t_philo *philo, t_fork *forks, unsigned long pos)
{
    unsigned long philo_nbr;

    philo_nbr = philo->data->n_philos;
    if (philo->id % 2) // odd
    {
        philo->right_fork = &forks[pos];
        philo->left_fork = &forks[(pos + 1) % philo_nbr];
    }
    else
    {
        philo->right_fork = &forks[(pos + 1) % philo_nbr];
        philo->left_fork = &forks[pos];
    }
}
