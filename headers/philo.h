/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:01:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/28 04:21:52 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "colors.h"
# include "utils.h"
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define LOCK pthread_mutex_lock
# define UNLOCK pthread_mutex_unlock
# define MUTEX_INIT pthread_mutex_init
/*--------------------------- DATA ----------------------------*/
typedef struct s_data
{
	unsigned long	n_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	n_limit_meals;
	bool			end_simulation;
	bool			meals_arg_exist;
	size_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	full_mutex;
	struct s_philo	*philos;
}					t_data;

/*--------------------------- PHILO ----------------------------*/
typedef struct s_philo
{
	unsigned long	id;
	pthread_t		thread_id;
	unsigned long	meal_counter;
	size_t			last_meal_time;
	bool			full;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_data			*data;
}					t_philo;

/*--------------------------- Parsing ----------------------------*/

typedef struct s_parser
{
	int				i;
	int				j;
	unsigned long	result;
	int				sign;
	int				is_ok;
}					t_parser;

/*--------------------------- Routine ----------------------------*/

int					check_arguments(int ac, char **av, unsigned long **array);
int					initializer(t_data *data);
int					initial_data(unsigned long *array, int ac);
void				*routine(void *arg);
void				ft_sleep(unsigned long time);
size_t				get_time(void);
int					monitor(t_data *data);
int					write_status(t_philo *philo, char *str);
int					write_philo_info(t_philo *philo);

/* FUNCTIONS */

#endif