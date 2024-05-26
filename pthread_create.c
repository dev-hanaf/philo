/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:01:44 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/26 05:26:16 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 
thread_create,
pthread_detach,
pthread_join,
pthread_mutex_init,
pthread_mutex_destroy,
pthread_mutex_lock,
pthread_mutex_unlock
 */

/* -----------------------------------------------POSIX----------------------------------------------------------------------------------------------------------------------------------
Before Posix, the Unix family tree was becoming very diverse and incompatible. A program written for one Unix was not compatible with a different Unix without significant porting effort.

Posix was one of the attempts to present a common set of utilities and programming interfaces so that your software would be portable to multiple versions of Unix.
 */


/* void *routine(void *name)
{
    (void)name;
    printf("hello word from routine\n");
    return (NULL);
}


int main(void)
{
    pthread_t   id;
    pthread_create(&id, NULL, routine, NULL);
    pthread_join(id, NULL);
}
 */

void *myturn(void *arg)
{
    (void)arg;
    int i = 0;
    while(i++ < 8)
    {
        sleep(1);
        write(1, "My turn! ", 9);   
        char c = i + 48; 
        write(1, &c, 1);
        write(1, "\n", 1);   
    }
    return (NULL);
}

void yourturn()
{
    int i = 0;
    while (i++ < 3)
    {
        sleep(2);
        write(1, "Your turn! ", 11);   
        char c = i + 48; 
        write(1, &c, 1);
        write(1, "\n", 1);   


    }
    return;
}

int main(void)
{
    pthread_t newthread;

    pthread_create(&newthread, NULL, myturn, NULL);
    
    // printf("id -->%d\n", newthread);
    yourturn();
    // if yourturn finished the programm is exit. so we need to join the main thread with a newthead
    pthread_join(newthread, NULL);
    return (0);
}
