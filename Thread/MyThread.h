#include <evdns.h>
#include <pthread.h>
#include <string>

class MyThread {
    static pthread_mutex_t mutex;
public:
    pthread_t threadID;
    MyThread() = default;
    int create(void *func, void* args);
    void join(){ pthread_join(threadID, 0); }

    static int initMutex();
    static int lockMutex(std::string id);
    static int unlockMutex(std::string id);
};