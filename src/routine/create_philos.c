/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:06:11 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/26 09:43:31 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_thinkig(t_philo *philo)
{
    static int i;
    char    *itoa;

    itoa = ft_itoa(philo->id);
    ft_putstr_fd("philo |",1);
    ft_putstr_fd(itoa,1);
    free(itoa);
    ft_putstr_fd("| is thinking 🤔\n",1);
    i++;
    sleep(1);
    return (0);
}

void *start_routine(t_philo *philo)
{
    is_thinkig(philo);
    return (NULL);
}
int create_philos(t_philo *philo)
{
    unsigned long i;
    
    i = 0;
    while (i < philo->n_philos)
    {
        pthread_t   new_thread;
        if (0 != pthread_create(&new_thread, NULL, (void *)start_routine, philo))
            return (1);
        philo->id = i + 1;
        if (0 != pthread_join(new_thread, NULL))
            return (1);
        i++;
    }
    return (0);
}
