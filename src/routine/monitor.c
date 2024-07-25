/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:51:18 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/25 02:59:20 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	is_full(t_data *data)
{
	unsigned long	i;

	i = 0;
	while (i < data->n_philos)
	{
		LOCK(&data->philos[i].philo_mutex);
		if (data->philos[i].full == FALSE)
		{
			UNLOCK(&data->philos[i].philo_mutex);
			return (FALSE);
		}
		UNLOCK(&data->philos[i].philo_mutex);
		i++;
	}
	return (TRUE);
}

int	philo_died(t_philo *philo)
{
	size_t			time;
	size_t			time_to_die;
	unsigned long	t_last_meal;
	int				is_full;

	LOCK(&philo->philo_mutex);
	is_full = philo->full;
	UNLOCK(&philo->philo_mutex);
	if (is_full)
		return (FALSE);
	LOCK(&philo->philo_mutex);
	t_last_meal = philo->last_meal_time;
	UNLOCK(&philo->philo_mutex);
	time = get_time() - t_last_meal;
	time_to_die = philo->data->time_to_die;
	if (time > time_to_die)
		return (TRUE);
	return (FALSE);
}

void	*monitor(void *arg)
{
	t_data			*data;
	unsigned long	i;
	int				end;

	end = FALSE;
	data = (t_data *)arg;
	while (!all_threads_running(data))
		;
	LOCK(&data->data_mutex);
	end = data->end_simulation;
	UNLOCK(&data->data_mutex);
	i = 0;
	while (TRUE)
	{
		LOCK(&data->data_mutex);
		end = data->end_simulation;
		if (end)
		{
			UNLOCK(&data->data_mutex);
			break;
		}
		UNLOCK(&data->data_mutex);
		if (i < data->n_philos && !end)
		{
			if (is_full(data))
			{
				LOCK(&data->data_mutex);
				data->end_simulation = TRUE;
				UNLOCK(&data->data_mutex);
				break ;
			}
			if (philo_died(&data->philos[i]))
			{
				write_status(&data->philos[i], "died");
				LOCK(&data->data_mutex);
				data->end_simulation = TRUE;
				UNLOCK(&data->data_mutex);
				break ;
			}
			i++;
			if (i == data->n_philos)
				i = 0;
		}

	}
	return (NULL);
}

/* int	is_full(t_data *data)
{
	unsigned long	i;

	i = 0;
	while (i < data->n_philos)
	{
		LOCK(&data->philos[i].philo_mutex);
		if (data->philos[i].full == false)
		{
			UNLOCK(&data->philos[i].philo_mutex);
			return (false);
		}
		UNLOCK(&data->philos[i].philo_mutex);
		i++;
	}
	return (true);
}

int	philo_died(t_philo *philo)
{
	size_t			time;
	size_t			time_to_die;
	unsigned long	t_last_meal;
	int				is_full;

	LOCK(&philo->philo_mutex);
	is_full = philo->full;
	UNLOCK(&philo->philo_mutex);
	if (is_full)
		return (false);
	LOCK(&philo->philo_mutex);
	t_last_meal = philo->last_meal_time;
	UNLOCK(&philo->philo_mutex);
	time = get_time() - t_last_meal;
	time_to_die = philo->data->time_to_die;
	if (time > time_to_die)
		return (true);
	return (false);
}

void	*monitor(void *arg)
{
	t_data			*data;
	unsigned long	i;
	int				end;

	end = false;
	data = (t_data *)arg;
	while (true)
	{
		LOCK(&data->data_mutex);
		if(data->thread_running_nbr == data->n_philos)
		{
			UNLOCK(&data->data_mutex);
			break;
		}	
		UNLOCK(&data->data_mutex);
	}
	LOCK(&data->data_mutex);
	end = data->end_simulation;
	UNLOCK(&data->data_mutex);
	i = 0;
	while (!end)
	{
		if (i < data->n_philos && !end)
		{
			if (is_full(data))
			{
				LOCK(&data->data_mutex);
				data->end_simulation = true;
				UNLOCK(&data->data_mutex);
				break ;
			}
			if (philo_died(&data->philos[i]))
			{
				LOCK(&data->data_mutex);
				data->end_simulation = true;
				UNLOCK(&data->data_mutex);
				write_status(&data->philos[i], DIED);
				break ;
			}
			i++;
			if (i == data->n_philos)
				i = 0;
		}
		LOCK(&data->data_mutex);
		end = data->end_simulation;
		UNLOCK(&data->data_mutex);

	}
	return (NULL);
}
 
*/

/* int	check_if_somone_died(t_philo *philo)
{
	size_t	time_stamp;
	size_t	last_meal_time;

	LOCK(&philo->philo_mutex);
	if (philo->full == 1)
	{
		UNLOCK(&philo->philo_mutex);
		return (0);
	}
	UNLOCK(&philo->philo_mutex);
	LOCK(&philo->philo_mutex);
	last_meal_time = philo->last_meal_time;
	UNLOCK(&philo->philo_mutex);
	time_stamp = get_time() - last_meal_time;
	if (time_stamp > philo->data->time_to_die)
		return (1);
	return (0);
}

void	help_func(t_data *data)
{
	unsigned long	i;
	
	i = 0;
	UNLOCK(&data->data_mutex);
	while (1)
	{
		LOCK(&data->data_mutex);
		if (!(i < data->n_philos && !data->end_simulation))
		{
			i++;
			UNLOCK(&data->data_mutex);
			break ;
		}
		if (check_if_somone_died(data->philos + i))
			write_status(&data->philos[i], DIED);
		UNLOCK(&data->data_mutex);
	}
}

void	*monitor(void *arg)
{
	t_data	*data;
	
	data = (t_data *)arg;
	while (TRUE)
	{
		LOCK(&data->data_mutex);
		if(data->thread_running_nbr == data->n_philos)
		{
			UNLOCK(&data->data_mutex);
			break;
		}	
		UNLOCK(&data->data_mutex);
	}
	while (TRUE)
	{
		LOCK(&data->data_mutex);
		if (data->end_simulation)
		{
			UNLOCK(&data->data_mutex);
			break ;
		}
		help_func(data);
	}
	return (NULL);
} */