#include <EventLoopThread.h>

EventLoopThread::EventLoopThread()
{
    
}

void EventLoopThread::threadFunc()
{
    loop_.loop();
}

void EventLoopThread::start()
{
    thread_ = std::make_unique
                <std::thread>(std::bind(&EventLoopThread::threadFunc,this));


}


