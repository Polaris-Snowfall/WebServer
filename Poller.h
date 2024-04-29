#include <vector>
#include <memory>
#include <map>
#include <NonCopyable.h>

struct epoll_event;
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

    int poll_fd_ {};
    EventList eventslist_ {};
    ChannelMap channels_ {};
};


