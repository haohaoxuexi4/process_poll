//
//  main.cpp
//  threadPool
//
//  Created by 仙女 on 17/4/21.
//  Copyright © 2017年 仙女. All rights reserved.
//

#include <iostream>
#include "ThreadPool.hpp"
#include <functional>
using namespace std;

void Func()
{
    printf("hellowordk thread=%d\n",pthread_self());
    
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    ThreadPool pool(3);
    
    //int Func(int x, int y);
    //auto bf1 = std::bind(Func);

    for (int i=0; i<10; i++) {
        pool.addfunction(std::bind(Func));
    }
    return 0;
}
