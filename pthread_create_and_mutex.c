/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_create_and_mutex.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:31:22 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/27 04:43:38 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

int mails = 0;
// int lock = 0; TODO lcok idea
pthread_mutex_t     mutex;

void *routine()
{
    for(int i= 0; i < 100000000; i++)
    {
        // if (lock == 1)
        // {
            // sleep(5);
        // }
        // lock = 1;
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);

        // lock = 0;
    }

    return (NULL);
}

/*------------------- Multiple threads --------------------
scenario1:
               |       t1         |      t2
------------------------------------------------------
// read mails  |       23         |      24
------------------------------------------------------
// increment   |       23         |      24
------------------------------------------------------
// write mails |       24         |      25
------------------------------------------------------
scenario2:
               |       t1         |      t2
------------------------------------------------------
// read mails  |       29         |      23
------------------------------------------------------
// increment   |       29         |      23
------------------------------------------------------
// write mails |       30         |      24
------------------------------------------------------
------------------- Race Condition  -------------------
 */


int main()
{
    pthread_t   philos[200];

    int n = 4;
     pthread_mutex_init(&mutex, NULL);
    for(int i = 0; i < n; i++)
    {
        if (pthread_create(&philos[i], NULL, &routine, NULL))
            return (1);
    }

    for(int i = 0; i < n; i++)
    {
        if (pthread_join(philos[i], NULL))
            return (1);
    }
    pthread_mutex_destroy(&mutex);

    printf("%d\n", mails);
}

int main2(void)
{
    pthread_t   new, new2, new3, new4;

    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&new, NULL, &routine, NULL))
        return (1);
    if (pthread_create(&new2, NULL, &routine, NULL))
        return (1);
    if (pthread_create(&new3, NULL, &routine, NULL))
        return (1);
    if (pthread_create(&new4, NULL, &routine, NULL))
        return (1);
    if (pthread_join(new, NULL))
        return (1);
    if (pthread_join(new2, NULL))
        return (1);
    if (pthread_join(new3, NULL))
        return (1);
    if (pthread_join(new4, NULL))
        return (1);
    printf("%d\n", mails);
    pthread_mutex_destroy(&mutex);

    return (0);   
}
