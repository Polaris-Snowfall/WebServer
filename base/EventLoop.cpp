#include <EventLoop.h>
#include <Channel.h>
#include <unistd.h>

EventLoop::EventLoop()
: threadId_(getpid())
{

}

void EventLoop::loop()
{
    assert(activeChannels_.empty());

    while (true)
    {
        poller_.poll(-1,activeChannels_);

        std::for_each(activeChannels_.begin(),activeChannels_.end(),[](std::shared_ptr<Channel> ch){
            ch->handleEvent();
        });
        activeChannels_.clear();
    }
    
}