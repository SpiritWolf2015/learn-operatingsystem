/*
在线运行C语言(GCC 9.2.0)
https://www.bejson.com/runcode/c920/
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	printf("hello world (pid:%d)\n", (int) getpid());
	int rc = fork();
	if (rc < 0) { // fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {  // child: redirect standard output to a fi
		close(STDOUT_FILENO);
		open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	
		// now exec "wc"...
		char *myargs[3];
		myargs[0] = strdup("wc"); // program: "wc" (word count
		myargs[1] = strdup("p4.c"); // argument: file to count
		myargs[2] = NULL; // marks end of array
		execvp(myargs[0], myargs); // runs word count
	} else { // parent goes down this path (main)
		int wc = wait(NULL);		
	}
	return 0;
}