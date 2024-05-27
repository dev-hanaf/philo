/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:01:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/27 06:54:47 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "colors.h"
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include "utils.h"
# include <limits.h>
# include <string.h>
# include <sys/time.h>
# include <stdio.h>


typedef struct  s_philo
{
    pthread_t             new_thread;
    int                   finished;
    unsigned long         times_ate;
    size_t                last_meal;
    unsigned long         id;
    pthread_mutex_t       r_fork;
    pthread_mutex_t       l_fork;
    struct  s_data        *data;
}   t_philo;

typedef struct s_data
{
    unsigned long         id;
    unsigned long         n_philos;
    unsigned long         time_to_die;
    unsigned long         time_to_eat;
    unsigned long         time_to_sleep;
    unsigned long         n_time_eat;
    size_t                start_time;
    t_philo               philos[200];
    // pthread_mutex_t	      forks;
}       t_data;

int check_arguments(int ac, char **av, unsigned long **array);

/*---------------------------------------- Routine ---------------------------------*/
int     create_philos(t_data *data);
int	    join_threads(t_data *data);


#endif