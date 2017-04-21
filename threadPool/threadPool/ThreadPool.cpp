//
//  ThreadPool.cpp
//  threadPool
//
//  Created by 仙女 on 17/4/21.
//  Copyright © 2017年 仙女. All rights reserved.
//

#include "ThreadPool.hpp"
static void* WorkFunction_InThread(void* arg)
{
    pthread_t threadid=pthread_self();
    printf("workfun id=%d\n",threadid);
    ThreadPool* pool=static_cast<ThreadPool*>(arg);
    while(true)
    {
        
        Task task=pool->takeTaskFromQueue();
        if (task) {
            task();
        }
    }
    
    
}

ThreadPool::ThreadPool(int threadnum):threadnum_(threadnum)
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    createpool();
    
}
void ThreadPool::createpool()
{
    threads=new pthread_t[threadnum_];
    for (int i=0; i<threadnum_; ++i)
    {
       pthread_create(&threads[i], NULL, WorkFunction_InThread, this);
        
    }
}
ThreadPool::~ThreadPool()
{
    
    delete []threads;
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}
void ThreadPool::addfunction(Task task)
{
    pthread_mutex_lock(&mutex);
    Task_queue.push(task);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    
}
Task ThreadPool::takeTaskFromQueue()
{
    
    pthread_mutex_lock(&mutex);
    while (Task_queue.empty()) {
        pthread_cond_wait(&cond, &mutex);
    }
    Task task=Task_queue.front();
    Task_queue.pop();
    pthread_mutex_unlock(&mutex);
    return task;
}