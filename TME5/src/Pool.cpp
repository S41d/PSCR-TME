#include "Pool.h"
#include <memory>
#include "Job.h"
#include "Queue.h"


void poolWorker(pr::Queue<pr::Job> &queue) {
    while(true) {
      pr::Job *j = queue.pop();
      if (j == nullptr) break;
      j->run();
    }
}

void pr::Pool::start(int nbthread) {
    threads.reserve(nbthread);
    for(int i = 0; i < nbthread; ++i) {
        threads.emplace_back(&poolWorker, std::ref(queue));
    }
}
void pr::Pool::stop() {
    // queue.setBlocking(false);
    for(auto &t : threads) t.join();
    threads.clear();
}

void pr::Pool::submit(Job *job) {
    queue.push(job);
}

pr::Pool::Pool(int qsize): queue(qsize) {}
pr::Pool::~Pool() {
    delete &queue;
}
