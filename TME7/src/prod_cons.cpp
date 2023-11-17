#include "Stack.h"
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;
using namespace pr;

void producteur(Stack<char> *stack) {
  while (true) {
    stack->push('a');
  }
}

void consomateur(Stack<char> *stack) {
  while (true) {
    char c = stack->pop();
    cout << c << flush;
  }
}

int main() {
  size_t len = sizeof(Stack<char>);
  void *adr = mmap(nullptr, len, PROT_READ | PROT_WRITE,
                   MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  Stack<char> *s = new (adr) Stack<char>;

  pid_t pp = fork();
  if (pp == 0) {
    producteur(s);
    return 0;
  }

  pid_t pc = fork();
  if (pc == 0) {
    consomateur(s);
    return 0;
  }

  wait(0);
  wait(0);

  munmap(adr, len);
  delete s;
  return 0;
}
