#include <util.h>
#include <memory>
#include <thread>
#include <condition_variable>
#include <EventLoopThread.h>


class EventLoopThreadPool{
public:
    EventLoopThreadPool(const size_t initial_nthreads);
    void start();
    EventLoop* next_loop();
private:

    const size_t initial_nthreads_;
    int next_{};
    std::vector<std::unique_ptr<EventLoopThread> > threads_ {};
    std::mutex mutex_ {};
    std::condition_variable cond_ {};
};