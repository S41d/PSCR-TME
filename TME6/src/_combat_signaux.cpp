#include <csignal>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

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

  if (kill(adversaire, SIGINT) == -1) {
    std::cout << "gangé: " << getpid() << std::endl;
    exit(0);
  }
  float r = 0.3 + static_cast<float>(rand()) /
                      (static_cast<float>(RAND_MAX / (1 - .3)));
  usleep(r * 1000000);
}

void defense() {
  struct sigaction sa;
  sa.sa_handler = SIG_IGN;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGINT, &sa, nullptr);

  float r = 0.3 + static_cast<float>(rand()) /
                      (static_cast<float>(RAND_MAX / (1 - .3)));
  usleep(r * 1000000);
}

void combat(pid_t adversaire) {
  while (true) {
    defense();
    attaque(adversaire);
  }
}

int main() {
  pid_t fils1 = fork();
  if (fils1 == 0) {
    combat(getppid());
    // pid_t fils2 = fork();
    // if (fils2 == 0) {
    //   combat(fils1);
    // }
    // combat(fils2);
  }
  combat(fils1);
}