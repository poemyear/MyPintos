#include "userprog/syscall.h"
#include <stdio.h>
#include <string.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "devices/shutdown.h"
#include "threads/vaddr.h"

// #include <user/syscall.h>

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
  // compare esep
  int SYS_STATUS = ((int*)f->esp)[0];
  void *esp = f->esp;
  uint8_t *eax = f->eax;


  printf("is_user_vaddr: %d\n", is_user_vaddr(esp));

  printf ("PHYS_BASE: [%d]\n", PHYS_BASE);

  if (!pagedir_get_page (thread_current()->pagedir, esp)) {
	  printf ("fail to get page\n");
  } else {
	  printf ("success to get page\n");
  }

  switch (SYS_STATUS) {
	  case SYS_HALT:
		  printf ("SYS_HALT\n");
		  break;
	  case SYS_EXIT:
		  printf ("SYS_EXIT\n");
		  break;
	  case SYS_EXEC:
		  printf ("SYS_EXEC\n");
		  break;
	  case SYS_WAIT:
		  printf ("SYS_WAIT\n");
		  break;
	  case SYS_READ:
		  printf ("SYS_READ\n");
		  break;
	  case SYS_WRITE:
		  printf ("SYS_WRITE\n");
		  break;
	  case SYS_FIBONACCI:
		  printf ("SYS_FIBONACCI\n");
		  break;
	  case SYS_SUM_OF_FOUR:
		  printf ("SYS_SUM_OF_FOUR\n");
		  break;
	  default:
		  printf ("NONE OF ABOVE\n");
		  break;
  }
  printf ("system call!\n");
  thread_exit ();
}

/*
   Terminates Pintos by calling shutdown_power_off() (declared in
   ‘devices/shutdown.h’). This should be seldom used, because you lose
   some information about possible deadlock situations, etc.
*/
void 
halt (void) 
{
	shutdown_power_off();
}

/*
	Terminates the current user program, returning status to the kernel. If the process’s
	parent waits for it (see below), this is the status that will be returned. Conventionally,
	a status of 0 indicates success and nonzero values indicate errors.
*/
void
exit (int status)
{
	return;
}


/*
   Runs the executable whose name is given in cmd line, passing any given arguments,
   and returns the new process’s program id (pid). Must return pid -1, which otherwise
   should not be a valid pid, if the program cannot load or run for any reason. Thus,
   the parent process cannot return from the exec until it knows whether the child
   process successfully loaded its executable. You must use appropriate synchronization
   to ensure this.
*/
pid_t
exec (const char *cmd_line)
{
	return 0;
}


/*
   Waits for a child process pid and retrieves the child’s exit status.
   If pid is still alive, waits until it terminates. Then, returns the status that pid passed
   to exit. If pid did not call exit(), but was terminated by the kernel (e.g. killed due
   to an exception), wait(pid) must return -1. It is perfectly legal for a parent process
   to wait for child processes that have already terminated by the time the parent calls
   wait, but the kernel must still allow the parent to retrieve its child’s exit status, or
   learn that the child was terminated by the kernel.
   wait must fail and return -1 immediately if any of the following conditions is true:
   • pid does not refer to a direct child of the calling process. pid is a direct child
   of the calling process if and only if the calling process received pid as a return
   value from a successful call to exec.
   Note that children are not inherited: if A spawns child B and B spawns child
   process C, then A cannot wait for C, even if B is dead. A call to wait(C) by
   process A must fail. Similarly, orphaned processes are not assigned to a new
   parent if their parent process exits before they do.
   • The process that calls wait has already called wait on pid. That is, a process
   may wait for any given child at most once.
   Processes may spawn any number of children, wait for them in any order, and may
   even exit without having waited for some or all of their children. Your design should
   consider all the ways in which waits can occur. All of a process’s resources, including
   its struct thread, must be freed whether its parent ever waits for it or not, and
   regardless of whether the child exits before or after its parent.
   You must ensure that Pintos does not terminate until the initial process exits.
   The supplied Pintos code tries to do this by calling process_wait() (in
   ‘userprog/process.c’) from main() (in ‘threads/init.c’). We suggest that you
   implement process_wait() according to the comment at the top of the function
   and then implement the wait system call in terms of process_wait().
   Implementing this system call requires considerably more work than any of the rest.
*/
int
wait (pid_t pid)
{

	return 0;
}


/*
   Reads size bytes from the file open as fd into buffer. Returns the number of bytes
   actually read (0 at end of file), or -1 if the file could not be read (due to a condition
   other than end of file). Fd 0 reads from the keyboard using input_getc().
*/
int
read (int fd, void *buffer, unsigned size)
{
	return 0;
}


/*
   Writes size bytes from buffer to the open file fd. Returns the number of bytes actually
   written, which may be less than size if some bytes could not be written.
   Writing past end-of-file would normally extend the file, but file growth is not implemented
   by the basic file system. The expected behavior is to write as many bytes as
   possible up to end-of-file and return the actual number written, or 0 if no bytes could
   be written at all.
   Fd 1 writes to the console. Your code to write to the console should write all of buffer
   in one call to putbuf(), at least as long as size is not bigger than a few hundred
   bytes. (It is reasonable to break up larger buffers.) Otherwise, lines of text output
   by different processes may end up interleaved on the console, confusing both human
   readers and our grading scripts.
*/
int
write (int fd, const void *buffer, unsigned size)
{

	return 0;
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


