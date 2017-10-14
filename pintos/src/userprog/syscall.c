#include "userprog/syscall.h"
#include <stdio.h>
#include <string.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

#include <user/syscall.h>

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

void
syscall_exit (int exitstatus) 
{
  struct thread *cur = thread_current();
  char *save_ptr=NULL, *token=NULL;
  char tmp[129];
  strlcpy (tmp, cur->name, strlen(cur->name) + 1);
  token = strtok_r (tmp, " ", &save_ptr);
  printf ("%s: exit(%d)\n", token, exitstatus);
  thread_exit ();
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  printf ("system call!\n");
  thread_exit ();
}



int 
pibonacci (int n) 
{
	int n1 = 1, n2 = 1, tmp, i;
	for (i=0; i<n; i++) {
		tmp = n2;
		n2 += n1;
		n1 = tmp;
	}
	return n2;
}

int 
sum_of_four_integers (int a, int b, int c, int d) 
{
	return a+b+c+d;
}


