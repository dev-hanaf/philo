/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_of_day.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:11:45 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/26 00:10:57 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* 
The gettimeofday function is commonly used in Unix-like operating systems to retrieve the current time with microsecond precision. It is declared in the <sys/time.h> header file.
*/


/* 
int gettimeofday(struct timeval *tv, struct timezone *tz);
1-->struct timeval: Holds the time information that holds the seconds and microseconds since the Epoch (January 1, 1970).
    {
        //   __time64_t tv_sec;		/* Seconds.  */
        //   __suseconds64_t tv_usec;	/* Microseconds.  */
/*  }
2-->struct timezone: This is a structure used to represent the local timezone information (which is now obsolete), so you should pass NULL instead.
 */


/* 
The gettimeofday() function will fail if:

EINVAL
The structure pointed to by tp specifies an invalid time.

EPERM
A user other than the privileged user attempted to set the time or time zone.

Additionally, the gettimeofday() function will fail for 32-bit interfaces if:

EOVERFLOW
The system time has progressed beyond 2038, thus the size of the tv_sec member of the timeval structure pointed to by tp is insufficient to hold the current time in seconds.
 */


/* 
The tv_sec field holds the full seconds passed since the Unix epoch, while tv_usec stores any additional microseconds beyond that.
 */
int main(void)
{
    struct timeval  start;
    struct timeval  end;

    if (0 == gettimeofday(&start, (void*)0))
    {
        printf("time start millisecond --> %ld ms\n", start.tv_sec * 1000 +  start.tv_usec / 1000 );
        printf("time start millisecond --> %ld ms\n", start.tv_usec / 1000);
    }
    // sleep(5); //5 seconds
    // gettimeofday(&end, (void*)0);
    
  
    // printf("start --> %ld s \t\t   end --> %ld s\ntotol second --> %lds\ntotal milisecond --> %ld ms", start.tv_sec, end.tv_sec, (end.tv_sec  - start.tv_sec ), (end.tv_sec  - start.tv_sec )  * (1000)) ;
}
