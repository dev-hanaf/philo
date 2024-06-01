/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:01:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/06/01 15:56:25 by ahanaf           ###   ########.fr       */
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
# include "utils.h"

/*--------------------------- BOOL ----------------------------*/
enum				e_bool
{
	FALSE,
	TRUE
};

/*--------------------------- DATA ----------------------------*/
typedef struct s_data
{
	unsigned long	id;
	unsigned long	n_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	n_limit_meals;
    int end_simulation; // TRUE --> a philo dies or all philos full
    size_t			start_time;
	struct s_philo	*philos;
	pthread_mutex_t			*forks;
	pthread_mutex_t	mutex;
	pthread_mutex_t	write_mutex;
	int				all_thread_ready;
}					t_data;

/*--------------------------- PHILO ----------------------------*/
typedef struct s_philo
{
	pthread_t       new_thread; // a philo is a thread
	unsigned long	times_ate;
	unsigned long	meal_counter;
	size_t          last_meal_time; // time passed from last meal
	int             full;              // TRUE --> philo ates all he's meals
	unsigned long	id;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			*left_fork;
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

int					check_arguments(int ac, char **av, unsigned long **array);
int					controller(t_data *data);
int					initial_data(unsigned long *array, int ac);

/*--------------------------- Routine ----------------------------*/
int					initializer(t_data *data);
int 				assign_forks(t_data *data);
void    			philo_takes_fork(t_philo *philo, pthread_mutex_t  *forks, unsigned long pos);
int 				create_philos(t_data *data);
int					join_threads(t_data *data);
void 				*routine(void *data);
void    			set_bool(t_data *data, int *dest,int value);
int   				get_bool(t_data *data, int value);
int 				simulation_finished(t_data *data);

void    			time_sitter(t_data *data, unsigned long  *dest,unsigned long  value);
// int    time_getter(t_data *data, int value);
void *monitor(void *data);


#endif