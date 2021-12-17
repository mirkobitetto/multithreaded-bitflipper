/* 
 * Operating Systems  (2INCO)  Practical Assignment
 * Threaded Application
 *
 * STUDENT_NAME_1 (STUDENT_NR_1)
 * STUDENT_NAME_2 (STUDENT_NR_2)
 *
 * Grading:
 * Students who hand in clean code that fully satisfies the minimum requirements will get an 8. 
 * Extra steps can lead to higher marks because we want students to take the initiative. 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h> // for perror()
#include <pthread.h>

#include "uint128.h"
#include "flip.h"

#include <unistd.h>

// create a bitmask where bit at position n is set
#define BITMASK(n) (((uint128_t)1) << (n))

// check if bit n in v is set
#define BIT_IS_SET(v, n) (((v)&BITMASK(n)) == BITMASK(n))

// set bit n in v
#define BIT_SET(v, n) ((v) = (v) | BITMASK(n))

// clear bit n in v
#define BIT_CLEAR(v, n) ((v) = (v) & ~BITMASK(n))

//toggle bit n in v (TESTING THIS, was not present in threaded_basic)
#define BIT_TOGGLE(v, n) ((v) = (v) ^ BITMASK(n))

void flip(int modulo)
{

    for (int i = 1; i < NROF_PIECES; i++)
    {
        if (i % modulo == 0)
        {
            BIT_TOGGLE(buffer[i / 128], i % 128);
        }
    }
}

static void *
my_thread(void *arg)
{
    int *argi;
    int i;
    int *rtnval;

    argi = (int *)arg; // proper casting before dereferencing (could also be done in one statement)
    i = *argi;         // get the integer value of the pointer
    free(arg);         // we retrieved the integer value, so now the pointer can be deleted

    fprintf(stderr, "        %lx: thread started; parameter=%d\n", pthread_self(), i);

    flip(i);

    //sleep(1);

    // a return value to be given back to the calling main-thread
    rtnval = malloc(sizeof(int)); // will be freed by the parent-thread
    *rtnval = 42;                 // assign an arbitrary value...
    return (rtnval);              // you can also use pthread_exit(rtnval);
}

int main(void)
{
    // TODO: start threads to flip the pieces and output the results
    // (see thread_test() and thread_mutex_test() how to use threads and mutexes,
    //  see bit_test() how to manipulate bits in a large integer)

    // set all bits to 1
    for (int i = 0; i < (NROF_PIECES / 128) + 1; i++)
    {
        buffer[i] = ~0;
    }

    //Flipping with no parallelism
    int modulo = 2;
    int count_of_threads = 0;
    while (modulo != NROF_PIECES)
    {

        int *parameter;
        int *rtnval;
        pthread_t thread_id;

        // thread
        if (count_of_threads < NROF_THREADS)
        {

            // parameter to be handed over to the thread
            parameter = malloc(sizeof(int)); // memory will be freed by the child-thread
            *parameter = modulo;             // assign an arbitrary value...

            fprintf(stderr, "%lx: starting thread ...\n", pthread_self());
            pthread_create(&thread_id, NULL, my_thread, parameter);

            //sleep(3);

            modulo++;
            count_of_threads++;
        }
        else if (count_of_threads == NROF_THREADS)
        {
            // wait for the thread, and we are interested in the return value
            fprintf(stderr, "\n");
            fprintf(stderr, "----- WAITING FOR THREAD TO FINISH ------\n");

            pthread_join(thread_id, (void **)&rtnval);

            fprintf(stderr, "%lx: thread ready; return value=%d\n", pthread_self(), *rtnval);
            free(rtnval); // free the memory thas has been allocated by the thread
            fprintf(stderr, "\n");

            count_of_threads--;
        }
    }

    // FOR PRINTING
    for (int i = 1; i < NROF_PIECES; i++)
    {
        if (BIT_IS_SET(buffer[i / 128], i % 128))
        {
            printf("%d\n", i);
        }
    }

    return (0);
}
