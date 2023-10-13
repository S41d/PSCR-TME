#include "Compte.h"
#include <mutex>

using namespace std;

namespace pr {
void Compte::crediter(unsigned int val) {
  unique_lock<recursive_mutex> g(m);
  solde += val;
}
bool Compte::debiter(unsigned int val) {
  unique_lock<recursive_mutex> g(m);
  bool doit = solde >= val;
  if (doit) {
    solde -= val;
  }
  return doit;
}
int Compte::getSolde() const {
  unique_lock<recursive_mutex> g(m);
  return solde;
}
// NB : vector exige Copyable, mais mutex ne l'est pas...
Compte::Compte(const Compte &other) {
  other.m.lock();
  solde = other.solde;
  other.m.unlock();
}
void Compte::lock() { m.lock(); }
void Compte::unlock() { m.unlock(); }
bool Compte::try_lock() { return m.try_lock(); }

} // namespace pr
