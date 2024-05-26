/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:29:36 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/26 06:00:42 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philo.h"
#include <stdio.h>
#include <stdlib.h>

static unsigned long	lenght_size(unsigned long n)
{
	unsigned long	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(unsigned long n)
{
	unsigned long	num;
	unsigned long	size;
	char	*str;

	num = n;
	size = lenght_size(num);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	size--;
	while (1)
	{
		if (size == 0)
		{
			str[size] = (num % 10) + 48;
			break;
		}
		str[size] = (num % 10) + 48;
		num /= 10;
		size--;
	}
	return (str);
}
