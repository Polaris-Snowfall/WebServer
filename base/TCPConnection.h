#include <Channel.h>
#include <sys/socket.h>
#include <netinet/in.h>

class TCPConnection{
public:
    TCPConnection(int fd,const sockaddr_storage& cliAddr,EventLoop* loop);
private:
    int fd_;
    EventLoop* loop_;
    const sockaddr_in cliAddr_;
    std::shared_ptr<Channel> channel_;
    char buf_[200]{0};
};