/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:01:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/26 09:24:01 by ahanaf           ###   ########.fr       */
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

typedef struct  s_philo
{
    unsigned long         n_philos;
    unsigned long         time_to_die;
    unsigned long         time_to_eat;
    unsigned long         time_to_sleep;
    unsigned long         n_time_eat;
    pthread_t             id;
}   t_philo;

int check_arguments(int ac, char **av, unsigned long **array);

/*---------------------------------------- Routine ---------------------------------*/
int     create_philos(t_philo *philo);


#endif