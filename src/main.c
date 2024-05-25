/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:35:28 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/25 07:06:47 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int loop(int ac, int *array)
{
  int i;

  i = 0;
  while (i < ac -1)
  {
    printf("array[%d] --> %d\n", i, array[i]);
    i++;
  }
  free_allocator();
  return (0);
}

int main(int ac ,char **av) 
{
  if (ac < 5)
  {
    ft_putstr_fd("Error: Wrong number of arguments\n", 2);
    return (1);
  }
  int *array;
  array = ft_allocator((ac -1)  * sizeof(int), "array");
  if (!array)
    return (1);
  if (check_arguments(ac, av, &array))
  {
      free_allocator();
      return (1);
  }
  loop(ac ,array);
  return (0);
}
