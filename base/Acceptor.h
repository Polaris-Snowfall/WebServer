#ifndef __ACCEPTOR_H
#define __ACCEPTOR_H
#include <memory>
#include <Channel.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <util.h>
#include <functional>

class Acceptor : public NonCopyable, 
                 public std::enable_shared_from_this<Acceptor>
{
public:
    using NewConnCallback = std::function<void(int sockfd,const sockaddr_storage& sockad)>;
    Acceptor(EventLoop* loop,const sockaddr_storage& listenAddr);    
    void listen();
    bool listening() {return listening_;}
    void setAcceptCb(const NewConnCallback& cb) {acceptCallback_ = cb;}
    void accept();
private:

    EventLoop* loop_;
    int listenfd_;
    bool listening_;
    NewConnCallback acceptCallback_ {};
    std::shared_ptr<Channel> channel_ {};
};

#endif