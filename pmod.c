/**********************************************
* Filename: finfo.c
* Description: displays file information
* Author: Jonathan Vang
* Date: 11/3/2026
***********************************************/

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(){
    errno = 0;
    int new_nice = nice(10);
    if (new_nice == -1 && errno != 0) {
        perror("failed to set nice value");
    } else {
        printf("New nice value: %d\n", new_nice);
    }

    struct timespec sleep_time;
    sleep_time.tv_sec = 1;
    sleep_time.tv_nsec = 837272638;

    if(nanosleep(&sleep_time, NULL) == -1) {
        perror("failed to sleep");
        return 1;
    }
    printf("Goodbye\n");
    return 0;
}