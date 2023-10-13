#pragma once
#include <mutex>
#include <thread>

namespace pr {

class Compte {
  mutable std::recursive_mutex m;
  int solde;

public:
  Compte(int solde = 0) : solde(solde) {}
  Compte(const Compte &other);
  void crediter(unsigned int val);
  bool debiter(unsigned int val);
  int getSolde() const;
  void lock();
  void unlock();
  bool try_lock();
};

} // namespace pr
