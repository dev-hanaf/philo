/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 05:48:10 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/25 07:02:32 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_arguments(int ac, char **av, int **array)
{
    int i;
    int j;
    int result;
    int sign;
    int is_ok;
    (void)array;
    i = 1;
    while(i < ac)
    {
        j= 0;
        sign = 1;
        result = 0;
        is_ok = 0;
        while(av[i][j] == 32 || (av[i][j] >= 9 && av[i][j] <= 13))
            j++;
        if (av[i][j] == '+' || av[i][j] == '-')
        {
            if (av[i][j] == '-')
                sign *= -1;
            j++;
        }
        while(av[i][j] >= 48 && av[i][j] <= 59)
        {
            is_ok = 1;
            result = result * 10 + (av[i][j] - 48);
            j++;
        }
        if (!is_ok)
        {
            ft_putstr_fd("Error: Wrong argument\n", 2);
            return (1);
        }
        if (av[i][j] != '\0')
        {
            ft_putstr_fd("Error: Wrong argument\n", 2);
            return (1);
        }
        if (sign == -1)
        {
            ft_putstr_fd("Error: Wrong argument\n", 2);
            return (1); 
        }
        (*array)[i - 1] = result;
        i++;
    }
    return (0);
}
