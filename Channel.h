#include <functional>
#include <cinttypes>
#include <NonCopyable.h>
#include <memory>

class Channel : public NonCopyable{
public:
    using EventCallback = std::function<void()>;

    Channel(int fd,std::shared_ptr<void> tie) : internel_fd_(fd),tie_(tie) {};

    const EventCallback setReadCallback(const EventCallback& cb);
    const EventCallback setWriteCallback(const EventCallback& cb);
    const EventCallback setErrorCallback(const EventCallback& cb);
    const EventCallback setCloseCallback(const EventCallback& cb);

    void setevents(const uint32_t events) { events_ = events;}
    void setRevents(const uint32_t revents) { revents_ = revents;}

    const uint32_t events() { return events_; }
    const int fd() { return internel_fd_; }

    void handleEvent();
    void handleEventWithGuard();

    bool isNonEvent() { return events_ == nonEvent;}
    static const uint32_t nonEvent;
    static const uint32_t readEvent;
    static const uint32_t writeEvent;


private: 

    int internel_fd_ {};
    uint32_t events_ {};
    uint32_t revents_ {};
    
    std::weak_ptr<void> tie_;
    EventCallback readCallback_ {};
    EventCallback writeCallback_ {};
    EventCallback closeCallback_ {};
    EventCallback errorCallback_ {};
};