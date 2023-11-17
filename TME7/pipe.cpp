#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <sched.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid_fils;
  int pipeDesc[2];
  int pipe_i = 1;
  for (; pipe_i < argc; ++pipe_i) {
    if (strcmp(argv[pipe_i], "|") == 0) {
      break;
    }
  }

  if (pipe(pipeDesc) != 0) {
    perror("pipe");
    exit(1);
  }

  if ((pid_fils = fork()) == -1) {
    perror("fork");
    exit(2);
  }

  argv[pipe_i] = 0x0;
  if (pid_fils == 0) {
    dup2(pipeDesc[1], STDOUT_FILENO);
    close(pipeDesc[1]);
    close(pipeDesc[0]);
    if (execv(argv[1], argv+1) == -1) {
      perror("execv");
      exit(3);
    }
  } else {
    dup2(pipeDesc[0], STDIN_FILENO);
    close(pipeDesc[0]);
    close(pipeDesc[1]);
    if (execv(argv[pipe_i + 1], argv + pipe_i + 1) == -1) {
      perror("execv");
      exit(3);
    }
  }
}