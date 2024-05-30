/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:01:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/30 10:34:01 by ahanaf           ###   ########.fr       */
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

/*--------------------------- FORKS ----------------------------*/
typedef struct s_fork
{
	pthread_mutex_t	fork;
	unsigned long	fork_id;
}					t_fork;

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
	t_fork			*forks;
	pthread_mutex_t	mutex;
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
	t_fork			*right_fork;
	t_fork			*left_fork;
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
void    			philo_takes_fork(t_philo *philo, t_fork *forks, unsigned long pos);
int 				create_philos(t_data *data);
int					join_threads(t_data *data);
void 				*routine(void *data);
void    			set_bool(t_data *data, int *dest,int value);
int   				get_bool(t_data *data, int value);
int 				simulation_finished(t_data *data);



#endif