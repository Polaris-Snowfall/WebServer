#ifndef __CHANNEL_H
#define __CHANNEL_H
#include <functional>
#include <cinttypes>
#include <sys/epoll.h>
#include <NonCopyable.h>
#include <EventLoop.h>
#include <memory>

class Channel : public NonCopyable,public std::enable_shared_from_this<Channel>{
public:
    using EventCallback = std::function<void()>;

    Channel(EventLoop* loop,int fd) : loop_(loop),internel_fd_(fd),tied_(false) {};

    const EventCallback setReadCallback(const EventCallback& cb);
    const EventCallback setWriteCallback(const EventCallback& cb);
    const EventCallback setErrorCallback(const EventCallback& cb);
    const EventCallback setCloseCallback(const EventCallback& cb);

    void setTie(std::weak_ptr<void> tie) { tie_ = tie;}

    void setRevents(const uint32_t revents) { revents_ = revents;}
    void enableReading() {events_ |= (readEvent); update();}
    void disableReading() {events_ &= ~(readEvent); update();}
    void enableWriting() {events_ |= writeEvent; update();}
    void disableWriting() {events_ &= ~writeEvent; update();}
    void disableAll() {events_ = nonEvent; update();};
    bool isNonEvent() { return events_ == nonEvent;}
    void update() {loop_->updateChannel(shared_from_this());} 

    const uint32_t events() { return events_; }
    const int fd() { return internel_fd_; }

    void handleEvent();
    void handleEventWithGuard();

    static const uint32_t nonEvent;
    static const uint32_t readEvent;
    static const uint32_t writeEvent;


private: 
    
    EventLoop* loop_;
    int internel_fd_ {};
    uint32_t events_ {};
    uint32_t revents_ {};
    
    std::weak_ptr<void> tie_; //与CPConnection关联
    bool tied_; //是否已经关联
    EventCallback readCallback_ {};
    EventCallback writeCallback_ {};
    EventCallback closeCallback_ {};
    EventCallback errorCallback_ {};
};

#endif