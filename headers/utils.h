/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 05:59:28 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/26 11:48:03 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

// int     free_and_return(t_philo *philo, int ret);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
size_t	ft_strlen(const char *s);
char	*ft_itoa(unsigned long n);
void	ft_sleep(int time);
size_t	get_time(void);

#endif