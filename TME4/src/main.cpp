#include "Banque.h"
#include "Compte.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
using namespace pr;

const int NB_THREAD = 10;

void transfere_job(Banque &banque) {
  for (int _i = 0; _i < 1000; ++_i) {
    size_t i = rand() % banque.size();
    size_t j = rand() % banque.size();
    int m = rand() % 100 + 1;

    // std::cout << "i:  " << i << ", j: " << j << ", m: " << m << std::endl;
    banque.transfert(i, j, m);
    banque.comptabiliser(1000);

    // int sleep = rand() % 21;
    // this_thread::sleep_for(std::chrono::milliseconds(sleep));
  }
}

int main() {
  Banque banque(10, 100);
  vector<thread> threads;
  // TODO : creer des threads qui font ce qui est demandé
  for (int k = 0; k < NB_THREAD; ++k) {
    // auto t = thread(&Banque::transfert, &banque, i, j, m);
    threads.emplace_back(transfere_job, ref(banque));
  }

  for (auto &t : threads) {
    t.join();
  }

  // TODO : tester solde = NB_THREAD * JP
  return 0;
}
