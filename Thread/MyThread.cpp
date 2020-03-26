//
// Created by sp00nyman on 26.03.2020.
//

#include <iostream>
#include "MyThread.h"

//func is a function executable by thread
//args is a Client
int MyThread::create(void *func, void *args) {
    //TODO хуй знает, вряд-ли это будет работать хоть как-то
    if(pthread_create(&threadID, NULL, (void*(*)(void*))func, args))
    {
        std::cerr << "Error creating thread\n";
        return -1;
    }
    return 0;
}

int MyThread::initMutex() {
    if(__gthrw_pthread_mutex_init(&MyThread::mutex, NULL) < 0)
    {
        std::cerr << "Error initializing mutex\n";
        return -1;
    }
    return 0;
}

int MyThread::lockMutex(std::string id) {
    if(pthread_mutex_lock(&MyThread::mutex) == 0)
        return 0;
    std::cerr << "Error locking mutex by: " + id << std::endl;
    return -1;
}

int MyThread::unlockMutex(std::string id) {
    if(pthread_mutex_unlock(&MyThread::mutex) == 0)
        return 0;
    std::cerr << "Error unlocking mutex by: " + id << std::endl;
    return -1;
}
