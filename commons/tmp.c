#include <time.h>
#include <stdio.h>

void main()
{
    int i =0;
    long timer;
    time_t t;
    while (i < 10) {

    timer = time(&t);
    printf("\ntimer: %lu ",timer);
    sleep(1);
    i++;
   }
}
