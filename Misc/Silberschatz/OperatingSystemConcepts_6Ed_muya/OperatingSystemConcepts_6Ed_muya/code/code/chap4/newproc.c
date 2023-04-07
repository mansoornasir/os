/**
 * newproc.c
 *
 * Figure 4.8
 *
 * This program creates a separate child process.
 * The child process performs the "ls" command to 
 * output a directory listing.
 *
 * @author Greg Gagne, Peter Galvin, Avi Silberschatz
 * @version 1.0 - January 1, 2000 
 *
 * Copyright 2000 by Greg Gagne, Peter Galvin, Avi Silberschatz
 * Operating Systems Concepts - John Wiley and Sons, Inc.
 */

#include <stdio.h>

int main(void)
{
int pid;

	/* fork another process */
	pid = fork();

	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed\n");
		exit(-1);
	}
	else if (pid == 0) { /* child process */
		execlp("/bin/ls","ls",NULL);
	}
	else { /* parent process */
		/* parent will wait for the child to complete */
		wait(NULL);
		
		printf("Child Complete\n");
		exit(0);
	}
}
