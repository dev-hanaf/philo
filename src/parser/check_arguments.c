/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 07:48:59 by ahanaf            #+#    #+#             */
/*   Updated: 2024/07/12 04:05:12 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_parser	*getter(void)
{
	static t_parser	var;

	return (&var);
}

int	is_error(char **av)
{
	if (!getter()->is_ok)
	{
		ft_putstr_fd("Error: Wrong argument should enter a digit\n", 2);
		return (1);
	}
	if (av[getter()->i][getter()->j] != '\0')
	{
		ft_putstr_fd("Error: Wrong argument accepts only digits\n", 2);
		return (1);
	}
	if (getter()->sign == -1)
	{
		ft_putstr_fd("Error: Wrong argument only positives\n", 2);
		return (1);
	}
	return (0);
}

void	init_vars(void)
{
	getter()->j = 0;
	getter()->sign = 1;
	getter()->result = 0;
	getter()->is_ok = 0;
}

void	sign_check(char **av)
{
	if (av[getter()->i][getter()->j] == '+'
		|| av[getter()->i][getter()->j] == '-')
	{
		if (av[getter()->i][getter()->j] == '-')
			getter()->sign *= -1;
		getter()->j++;
	}
}

int	check_arguments(int ac, char **av, unsigned long **array)
{
	t_parser	*var;

	var = getter();
	var->i = 1;
	while (var->i < ac)
	{
		init_vars();
		while (av[var->i][var->j] == 32 || (av[var->i][var->j] >= 9
				&& av[var->i][var->j] <= 13))
			var->j++;
		sign_check(av);
		while (av[var->i][var->j] >= 48 && av[var->i][var->j] <= 59)
		{
			var->is_ok = 1;
			var->result = var->result * 10 + (av[var->i][var->j] - 48);
			var->j++;
		}
		if (is_error(av))
			return (1);
		(*array)[var->i - 1] = var->result;
		var->i++;
	}
	return (0);
}
