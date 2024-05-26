/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 05:55:54 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/25 05:59:00 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
    return ;
}

void ft_putstr_fd(char *str, int fd)
{
    size_t i;
    
    if (!str)
        return ;
    i = 0;
    while (str[i])
        ft_putchar_fd(str[i++], fd);
    return;
}
