#ifndef __EVENTLOOP_H
#define __EVENTLOOP_H

#include <Poller.h>
#include <NonCopyable.h>
#include <util.h>


class EventLoop : public NonCopyable{
public:
    EventLoop();    
    void loop();
    void updateChannel(const std::shared_ptr<Channel> ch) {poller_.updateChannel(ch);}
private:
    using ChannelList = std::vector<std::shared_ptr<Channel> >;

    const pid_t threadId_;
    Poller poller_ {};
    ChannelList activeChannels_ {};
};

#endif