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

    BIT_TOGGLE(buffer[0], 4);

    // FOR PRINTING
    for (int i = 0; i < (NROF_PIECES / 128) + 1; i++)
    {
        printf("buffer[%.2d] : %lx%016lx\n", i, HI(buffer[i]), LO(buffer[i]));
    }

    return (0);
}
