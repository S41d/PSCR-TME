#include <csignal>
#include <iostream>
#include <sched.h>
#include <sys/wait.h>
#include <unistd.h>

const int N = 3;

int main() {
  std::cout << "main pid=" << getpid() << std::endl;
  int childc = 0;

  for (int i = 1, j = N; i <= N && j == N; i++) {
    if (fork() == 0) {
      childc = 0;
      std::cout << " i=" << i << ", j=" << j << std::endl;
      // std::cout << " i:j " << i << ":" << j << std::endl;
      std::cout << "Je suis le fils " << i << " de pid " << getpid()
                << " de parent " << getppid() << std::endl;
      for (int k = 1; k <= i && j == N; k++) {
        if (fork() == 0) {
          j = 0;
          childc = 0;
          std::cout << " k=" << j << ", j=" << j << std::endl;
          std::cout << "Je suis le fils " << k << " de pid " << getpid()
                    << " de parent " << getppid() << std::endl;
          // std::cout << " k:j " << k << ":" << j << std::endl;
        } else {
          childc++;
        }
      }
    } else {
      childc++;
      break;
    }
  }

  for (int i = 0; i < childc; i++) {
    if (wait(NULL) == -1) {
      std::cout << "trop de wait" << getpid() << std::endl;
    } else {
      std::cout << "waited" << std::endl;
    }
  }
  if (wait(NULL) != -1) {
    std::cout << "il en reste" << std::endl;
  }
  return 0;
}

int hp = 3;

static void handler(int) {
  std::cout << "hit: " << getpid() << std::endl;
  hp--;
  if (hp == 0) {
    _exit(1);
  }
}

void attaque(pid_t adversaire) {
  struct sigaction sa;
  sa.sa_handler = &handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGINT, &sa, NULL);

  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);

  if (kill(adversaire, SIGINT) == -1) {
    exit(0);
  }
}

void defense() {
  struct sigaction sa;
  sa.sa_handler = SIG_IGN;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGINT, &sa, nullptr);
}

void combat(pid_t adversaire) {
  while(true) {
    attaque(adversaire);
    defense();
  }
}