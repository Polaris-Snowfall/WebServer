#include <Acceptor.h>
#include <EventLoop.h>
#include <EventLoopThreadPool.h>
#include <TCPConnection.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class TCPServer{
public:
    TCPServer(EventLoop* loop,const sockaddr_storage& listenAddr);
    void start();
    void newConnection(int sockfd, const sockaddr_storage& sockad);

private:
    EventLoop* loop_;
    std::unique_ptr<Acceptor> acceptor_;
    EventLoopThreadPool pool_;
    std::vector<std::shared_ptr<TCPConnection> > connections_{};
};