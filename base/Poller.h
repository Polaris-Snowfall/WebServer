#ifndef __POLLER_H
#define __POLLER_H
#include <vector>
#include <memory>
#include <map>
#include <NonCopyable.h>
#include <sys/epoll.h>

class Channel;

class Poller : public NonCopyable{
public:
    using ChannelList = std::vector<std::shared_ptr<Channel> >;
    using ChannelMap = std::map<int,std::shared_ptr<Channel>>;

    Poller();
    ~Poller();

    void poll(int timeoutMs, ChannelList& activeChannels);
    void updateChannel(std::shared_ptr<Channel> channel);


private:    
    using EventList = std::vector<struct epoll_event>; 

    void update(int operation,std::shared_ptr<Channel> channel);

    static const int initial_nevents;
    int poll_fd_ {};
    EventList eventslist_ {};
    ChannelMap channels_ {};
};


#endif