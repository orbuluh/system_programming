#pragma once

/*
Modified from
https://www.cs.cmu.edu/afs/cs/academic/class/15213-f05/code/conc/csapp.h
*/

#include <signal.h>

/* Signal wrappers */
typedef void handler_t(int);
handler_t* Signal(int signum, handler_t* handler);
void Sigprocmask(int how, const sigset_t* set, sigset_t* oldset);
void Sigemptyset(sigset_t* set);
void Sigfillset(sigset_t* set);
void Sigaddset(sigset_t* set, int signum);
void Sigdelset(sigset_t* set, int signum);
int Sigismember(const sigset_t* set, int signum);