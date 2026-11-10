# Lab9_SystemCalls

CPE 2600 Lab 9 - System Calls

Name: Jonathan Vang

This lab has four programs that use Linux system calls.

Programs
info - prints system info (time in nanoseconds, hostname, OS name/release/version, hardware type, number of CPUs, total and free memory in bytes)
pinfo - prints the priority and scheduling method of a process. Takes an optional PID, uses the current process if none is given.
pmod - lowers its own priority by 10, sleeps for 1,837,272,638 ns, prints goodbye, and exits
finfo - prints the type, permissions, owner, size, and last modified time of a file
Build
make
Run
./info
./pinfo [pid]
./pmod
./finfo <file>
Notes
finfo uses lstat so symbolic links show up as links.
Tested with valgrind and compared output against ps, top, stat, free, and uname.
