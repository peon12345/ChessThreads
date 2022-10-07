#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <pthread.h>


#include <future>
#include <vector>
#include <queue>


class ThreadPool
{
public:
  ThreadPool(size_t nThreads);
  ThreadPool(const ThreadPool& pool ) = delete;
  ThreadPool(ThreadPool&& pool ) = delete;
  ThreadPool& operator = (const ThreadPool& pool ) = delete;
  ThreadPool& operator = (ThreadPool&& pool ) = delete;

  ~ThreadPool();
  void putTask(std::packaged_task<bool()> &&task);

  void stop();
  void resize(size_t nThreads);


  int threadActive() const;
private:
  std::vector<pthread_t> m_threads;
  pthread_mutex_t m_mutexCond;
  pthread_cond_t m_condition;
  std::queue<std::packaged_task<bool()>> m_tasks;
  bool m_shouldTerminate = false;

private:
  static void* loopHelper(void* obj);
  void *threadLoop();
};
#endif // THREADPOOL_H
