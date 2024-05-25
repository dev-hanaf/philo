/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:01:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/25 06:26:24 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "colors.h"
# include "header.h"
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include "utils.h"
typedef struct  s_philo
{
    int         time_of_luanch_program;
    int         time_to_deth;
    int         time_to_eat;
    int         time_to_sleep;
    int         check_routine;
}   t_philo;

int check_arguments(int ac, char **av, int **array);

#endif