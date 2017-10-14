#ifndef USERPROG_SYSCALL_H
#include <user/syscall.h>
#define USERPROG_SYSCALL_H

void syscall_init (void);
void syscall_exit (int);


void halt (void);
void exit (int);
pid_t exec (const char *);
int wait (pid_t);
int read (int, void *, unsigned);
int write (int,  const void *, unsigned);


int pibonacci (int);
int sum_of_four_integers (int, int, int, int);

#endif /* userprog/syscall.h */
