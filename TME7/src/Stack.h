#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>

namespace pr {

#define STACKSIZE 100

template <typename T> class Stack {
  T tab[STACKSIZE];
  size_t sz;
  sem_t sem_mut;
  sem_t sem_push;
  sem_t sem_pop;

public:
  Stack() : sz(0) {
    memset(tab, 0, sizeof tab);
    sem_init(&sem_mut, 1, 1);
    sem_init(&sem_pop, 1, 0);
    sem_init(&sem_push, 1, STACKSIZE);
  }

  T pop() {
    // bloquer si vide
    sem_wait(&sem_pop);
    T toret = tab[--sz];
    sem_post(&sem_push);
    return toret;
  }

  void push(T elt) {
    // bloquer si plein
    sem_wait(&sem_push);
    tab[sz++] = elt;
    sem_post(&sem_pop);
  }
};

} // namespace pr
