#pragma once

#include "Job.h"
#include "Queue.h"
#include <thread>
#include <vector>

namespace pr {

class Pool {
  Queue<Job> queue;
  std::vector<std::thread> threads;

public:
  Pool(int qsize);
  void start(int nbthread);
  void submit(Job *job);
  void stop();
  ~Pool();
};

} // namespace pr
