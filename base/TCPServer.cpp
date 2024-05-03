#include <TCPServer.h>
#include <functional>

TCPServer::TCPServer(EventLoop *loop, const sockaddr_storage &listenAddr)
: loop_(loop),acceptor_(std::make_unique<Acceptor>(loop_,listenAddr)),pool_(1)
{
    acceptor_->setAcceptCb(std::bind(&TCPServer::newConnection,this,std::placeholders::_1,std::placeholders::_2));
}

void TCPServer::start()
{
    pool_.start();
    acceptor_->listen();
}

void TCPServer::newConnection(int sockfd,const sockaddr_storage& sockad)
{
    LOG_INFO << "NewConnection from " << inet_ntoa(reinterpret_cast<const sockaddr_in*>(&sockad)->sin_addr) << ":" << reinterpret_cast<const sockaddr_in*>(&sockad)->sin_port;

    connections_.emplace_back(std::make_shared<TCPConnection>(sockfd,sockad,pool_.next_loop()));
}