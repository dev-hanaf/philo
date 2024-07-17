/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:01:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/17 11:52:17 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H



# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include "colors.h"
#include  "utils.h"

/*--------------------------- BOOL ----------------------------*/
enum				e_bool
{
	FALSE,
	TRUE,
};

typedef enum	e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
}	t_status;


#define LOCK pthread_mutex_lock
#define UNLOCK pthread_mutex_unlock
/*--------------------------- DATA ----------------------------*/
typedef struct s_data
{
	unsigned long	id;
	unsigned long	n_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	n_limit_meals;
    int 			end_simulation;
	int				meals_arg_exist;
    size_t			start_time;
	unsigned long	thread_running_nbr;
	pthread_t		monitor_th;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	write_mutex;
	struct s_philo	*philos;
}					t_data;

/*--------------------------- PHILO ----------------------------*/
typedef struct s_philo
{
	unsigned long	id;
	pthread_t       thread_id;
	unsigned long	meal_counter;
	size_t          last_meal_time;
	int				full;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			philo_mutex;//useful for races with monitors
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



int	check_arguments(int ac, char **av, unsigned long **array);
int initializer(t_data *data);
int	initial_data(unsigned long *array, int ac);

void *routine(void *arg);




/* FUNCTIONS */
void   increase_threads(t_data *data);
int all_threads_running(t_data *data);
void *monitor(void *arg);
void    write_status(t_philo *philo, t_status status);

#endif