/* ************************************************************************** */
/*                                                                            */
/*                                         threads in c                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:31:22 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/27 09:36:12 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

/* 
------------------------------------------------------------ Shared Resources -----------------------------------------------------------------
1--> Global Variables: Global variables are accessible to all threads in the program. However, caution is needed when modifying them concurrently to avoid race conditions.
2--> Heap Memory: Memory allocated dynamically (e.g., with malloc) is shared among threads. However, thread safety mechanisms such as mutexes or other synchronization techniques are often needed to prevent data corruption when multiple threads access and modify shared heap memory concurrently
3--> File Descriptors: File descriptors opened by one thread can typically be used by other threads within the same process.
4--> Code Section: The code section (text segment) of the program is shared among all threads. Since code is read-only, there's no risk of concurrent modification issues.
------------------------------------------------------------ Non-shared Resources -----------------------------------------------------------------
1--> Stack Memory: Each thread has its own stack memory for function calls and local variables. Changes to the stack of one thread don't affect the stacks of other threads.
2--> Thread-Specific Data: Thread-specific data, accessed via functions like pthread_setspecific and pthread_getspecific in POSIX systems, allows each thread to have its own unique data. This data is not shared among threads.
3--> Registers: Each thread has its own set of CPU registers, which are not shared with other threads.
4--> Thread Control Block (TCB): Each thread typically has its own TCB, which contains information about the thread's state, such as its register values, stack pointer, and so on. These are not shared among threads.
 */



/* 
Some essential resources every process needs are registers, a program counter, and a stack. 
The “registers” are data holding places that are part of the computer processor (CPU).
A register may hold an instruction, a storage address, or other kind of data needed by the process. 
The “program counter,” also called the “instruction pointer,” keeps track of where a computer is in its program sequence.
The “stack” is a data structure that stores information about the active subroutines of a computer program and is used as scratch space for the process.
It is distinguished from dynamically allocated memory for the process that is known as the “heap.”
 
 */
 

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
