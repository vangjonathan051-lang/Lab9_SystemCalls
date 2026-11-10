/**********************************************
* Filename: finfo.c
* Description: displays file information
* Author: Jonathan Vang
* Date: 11/3/2026
***********************************************/ 

#include <time.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

// Print file type in a readable form
void print_file_type(mode_t mode) {
    printf("File Type: ");
    if (S_ISREG(mode))       printf("Regular File\n");
    else if (S_ISDIR(mode))  printf("Directory\n");
    else if (S_ISCHR(mode))  printf("Character Device\n");
    else if (S_ISBLK(mode))  printf("Block Device\n");
    else if (S_ISFIFO(mode)) printf("FIFO\n");
    else if (S_ISLNK(mode))  printf("Symbolic Link\n");
    else if (S_ISSOCK(mode)) printf("Socket\n");
    else                     printf("Unknown\n");
}

// Print permissions like rwxr-xr--
void print_permissions(mode_t mode) {
    printf("Permissions: %c%c%c%c%c%c%c%c%c\n",
        (mode & S_IRUSR) ? 'r' : '-', (mode & S_IWUSR) ? 'w' : '-',
        (mode & S_IXUSR) ? 'x' : '-', (mode & S_IRGRP) ? 'r' : '-',
        (mode & S_IWGRP) ? 'w' : '-', (mode & S_IXGRP) ? 'x' : '-',
        (mode & S_IROTH) ? 'r' : '-', (mode & S_IWOTH) ? 'w' : '-',
        (mode & S_IXOTH) ? 'x' : '-');
}



int main(int argc, char *argv[]){
   if (argc != 2) {
    fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
    exit(1);
   }
   struct stat sb;
  
   if(stat(argv[1], &sb) == -1) {
       perror("lstat");
       exit(1);
   }
   print_file_type(sb.st_mode);
   print_permissions(sb.st_mode);
   printf("Owner UID: %u\n", (unsigned int)sb.st_uid);
   printf("Size: %lld bytes\n", (long long)sb.st_size);

   char time_buffer[64];
    struct tm *tm_info = localtime(&sb.st_mtime);
    if (tm_info == NULL ||
        strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", tm_info) == 0) {
        fprintf(stderr, "Error formatting time\n");
    }
    printf("Last Modified: %s\n", time_buffer);
}
