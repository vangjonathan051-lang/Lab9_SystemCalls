/**********************************************
* Filename: finfo.c
* Description: displays file information
* Author: Jonathan Vang
* Date: 11/3/2026
***********************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>

// Convert a scheduling policy number to text
static const char *policy_name(int policy) {
    switch (policy) {
        case SCHED_OTHER: return "SCHED_OTHER";
        case SCHED_FIFO:  return "SCHED_FIFO";
        case SCHED_RR:    return "SCHED_RR";
        case SCHED_BATCH: return "SCHED_BATCH";
        case SCHED_IDLE:  return "SCHED_IDLE";
        default:          return "Unknown";
    }
}

int main(int argc, char *argv[]) {
    pid_t pid = 0;  // 0 means the calling process

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [pid]\n", argv[0]);
      
    }
    if (argc == 2) {
        char *end;
        errno = 0;
        long val = strtol(argv[1], &end, 10);
        if (errno != 0 || *end != '\0' || end == argv[1] || val < 0) {
            fprintf(stderr, "Invalid process id: %s\n", argv[1]);
           
        }
        pid = (pid_t)val;
    }

    // -1 is a valid priority value, so errno must be checked
    errno = 0;
    int priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1 && errno != 0) {
        perror("getpriority");
      
    }

    int policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("sched_getscheduler");
    }

    if (pid == 0) {
        printf("Process: current\n");
    } else {
        printf("Process: %d\n", (int)pid);
    }
    printf("Priority: %d\n", priority);
    printf("Scheduling method: %s\n", policy_name(policy));
    return EXIT_SUCCESS;
}
