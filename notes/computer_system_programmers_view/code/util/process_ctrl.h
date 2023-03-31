#pragma once

/*
Modified from
https://www.cs.cmu.edu/afs/cs/academic/class/15213-f05/code/conc/csapp.h
*/

#include <sys/types.h>

/* Process control wrappers */
pid_t Fork();
void Execve(const char* filename, char* const argv[], char* const envp[]);
pid_t Wait(int *status);
pid_t Waitpid(pid_t pid, int *iptr, int options);
void Kill(pid_t pid, int signum);
unsigned int Sleep(unsigned int secs);
void Pause();
unsigned int Alarm(unsigned int seconds);
void Setpgid(pid_t pid, pid_t pgid);
pid_t Getpgrp();