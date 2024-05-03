#include <util.h>
#include <EventLoop.h>
#include <NonCopyable.h>
#include <thread>

class EventLoopThread : public NonCopyable{
public:
    EventLoopThread();
    void threadFunc();
    void start();
    EventLoop* eventLoop() { return &loop_;}
private:
    EventLoop loop_{};
    std::unique_ptr<std::thread> thread_ {};
};