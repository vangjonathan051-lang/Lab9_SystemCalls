/**********************************************
* Filename: change.c
* Description: makes low pass pgm
* Author: Jonathan Vang
* Date: 10/26/2026
***********************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

static void print_if_set(const char *label, const char *value) {
    if (value != NULL && value[0] != '\0') {
        printf("%s: %s\n", label, value);
    }
}

int main(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        perror("clock_gettime");
    }
    long long ns = (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
    printf("Time of day (ns): %lld\n", ns);

    char hostname[HOST_NAME_MAX + 1];
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        perror("gethostname");
    }
    hostname[HOST_NAME_MAX] = '\0';
    print_if_set("Network name", hostname);

    struct utsname sys;
    if (uname(&sys) == -1) {
        perror("uname");
    }
    print_if_set("OS name", sys.sysname);
    print_if_set("OS release", sys.release);
    print_if_set("OS version", sys.version);
    print_if_set("Hardware type", sys.machine);

    printf("Number of CPUs: %d\n", get_nprocs());

    long page = getpagesize();
    long phys = sysconf(_SC_PHYS_PAGES);
    long avail = sysconf(_SC_AVPHYS_PAGES);
    if (page == -1 || phys == -1 || avail == -1) {
        perror("sysconf");
    }
    printf("Total memory (bytes): %lld\n", (long long)phys * page);
    printf("Free memory (bytes): %lld\n", (long long)avail * page);
}
