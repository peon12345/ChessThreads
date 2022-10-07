#include "threadpool.h"

#include <iostream>

ThreadPool::ThreadPool(size_t nThreads) : m_shouldTerminate(false)
{
  pthread_mutex_init(&m_mutexCond, NULL);
  // pthread_mutex_init(&m_mutexQueue, NULL);
  pthread_cond_init(&m_condition, NULL);

  resize(nThreads);
}

ThreadPool::~ThreadPool()
{
  pthread_mutex_destroy(&m_mutexCond);
  pthread_cond_destroy(&m_condition);
  stop();
}

void ThreadPool::putTask(std::packaged_task<bool ()> &&task)
{
  pthread_mutex_lock(&m_mutexCond);
  m_tasks.push(std::move(task));
  pthread_cond_signal(&m_condition);

  pthread_mutex_unlock(&m_mutexCond);



}

void ThreadPool::stop()
{
  m_shouldTerminate = true;


  pthread_cond_broadcast(&m_condition);

  for (pthread_t tid : m_threads)
    {
      pthread_join(tid,NULL);
    }


  m_threads.clear();



}

void ThreadPool::resize(size_t nThreads)
{
  if (nThreads <= 0)
    {
      nThreads = 1;
    }

  if (nThreads < m_threads.size())
    {
      stop();
    }
  else
    {
      m_threads.resize(nThreads);
    }


  for (uint32_t i = 0; i < nThreads; i++)
    {

      int s = pthread_create(&m_threads[i], NULL, &ThreadPool::loopHelper, this);

      if(s != 0) {
          throw "Thread create error";
        }

    }

}

int ThreadPool::threadActive() const
{
  return m_threads.size();
}

void* ThreadPool::loopHelper(void *obj)
{
  return ((ThreadPool*)obj)->threadLoop();
}

void* ThreadPool::threadLoop()
{
  while (true)
    {

      pthread_mutex_lock(&m_mutexCond);
      while(m_tasks.empty()){
          if (m_shouldTerminate)
            {
              pthread_mutex_unlock(&m_mutexCond);
              pthread_exit(NULL);
              return 0;
            }
          pthread_cond_wait(&m_condition , &m_mutexCond);
        }

      std::packaged_task<bool()> task;


      if(!m_tasks.empty()){
          task = std::move(m_tasks.front());
          m_tasks.pop();
        }

      pthread_mutex_unlock(&m_mutexCond);


      if( task.valid()){
          task();
        }

    }



  return 0;
}
