/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:52:23 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/30 10:24:37 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	// while (!get_bool(philo->data))
		// ;
	printf("%ld\n", philo->id);

	return (NULL);
}