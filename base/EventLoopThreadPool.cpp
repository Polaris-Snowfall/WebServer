#include <EventLoopThreadPool.h>

EventLoopThreadPool::EventLoopThreadPool(const size_t initial_nthreads)
: initial_nthreads_(initial_nthreads) 
{

}

void EventLoopThreadPool::start()
{
    for(int i = 0;i<initial_nthreads_;++i)
    {
        threads_.push_back(std::make_unique<EventLoopThread>());
        threads_.at(i)->start();
    }
}

EventLoop* EventLoopThreadPool::next_loop()
{
    EventLoop* ret{};
    if(!threads_.empty())
    {
        if(next_ >= threads_.size())
        next_ = 0;
        return threads_.at(next_++)->eventLoop();
    }
    return nullptr;
}