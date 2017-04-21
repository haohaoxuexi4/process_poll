//
//  ThreadPool.hpp
//  threadPool
//
//  Created by 仙女 on 17/4/21.
//  Copyright © 2017年 仙女. All rights reserved.
//

#ifndef ThreadPool_hpp
#define ThreadPool_hpp

#include <stdio.h>
#include <functional>
#include <vector>
#include <queue>
#include <pthread.h>

typedef std::function<void()> Task;
class ThreadPool
{
public:
    ThreadPool(int threadnum);
    ~ThreadPool();
    void createpool();
    void addfunction(const Task& task) ;
    Task takeTaskFromQueue();
private:
    int threadnum_;
    std::queue<Task> Task_queue;
    pthread_t* threads;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    
};
#endif /* ThreadPool_hpp */
