/* demo using pipe to communicate between parent and child processes */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// unix standard library for fork, pipe, etc.

int main() {
  int fd[2];      // file descriptor for pipe
  pid_t childPid; // process id
  int valus[] = {7, 10, 9, 10};
  int status; // status of close
  if (pipe(fd) < 0) {
    fprintf(stderr, "pipe failed\n");
    return 1;
  }

  childPid = fork(); // create a child process
  switch (childPid) {
  case -1: { // fork failed
             // print error message
    perror("fork failed");
    exit(1);
  }
  case 0: {                          // child process
    close(fd[1]);                    // close write end of pipe
    char buf[100];                   // buffer to read from pipe
    read(fd[0], buf, 100);           // read from pipe
    printf("Child read: %s\n", buf); // print read message
    close(fd[0]);                    // close read end of pipe
    break;
  }
  default: {               // parent process
                           // close read end of pipe
    status = close(fd[0]); // 0 is read file descriptor; 1 is write file
                           // descriptor for pipe;
    if (status < 0) {
      perror("close failed");
      exit(1);
    }

    char msg[] = "Hello from parent"; // message to write
                                      // write message to pipe
                                      //
    write(fd[1], msg, sizeof(msg));
  }
    return 0;
  }
}
