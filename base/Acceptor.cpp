#include <Acceptor.h>

Acceptor::Acceptor(EventLoop* loop, const sockaddr_storage& listenAddr)
: loop_(loop),listening_(false)
{
    listenfd_ = socket(listenAddr.ss_family,SOCK_STREAM,IPPROTO_TCP);
    if(listenfd_ == -1)
    {
        errorExit("Acceptor::socket");
    }

    if(bind(listenfd_,reinterpret_cast<const struct sockaddr*>(&listenAddr),sizeof(listenAddr)) == -1)
    {
        errorExit("Acceptor::bind");
    }

    channel_ = std::make_shared<Channel>(loop,listenfd_);
    if(channel_ == nullptr)
    {
        errorExit("Acceptor::make_shared<Channel>");
    }

    channel_->setReadCallback(std::bind(&Acceptor::accept,this));

}

void Acceptor::listen()
{
    if(::listen(channel_->fd(),SOMAXCONN) == -1)
    {
        errorExit("Acceptor::listen");
    }
    channel_->enableReading();
    listening_ = true;
}

void Acceptor::accept()
{
    sockaddr_in cliaddr{};
    socklen_t cliaddrLen = sizeof(cliaddr);
    int clifd = ::accept(channel_->fd(),reinterpret_cast<struct sockaddr*>(&cliaddr),&cliaddrLen);
    if(clifd < 0)
    {
        errorExit("Acceptor::accept");
    }
    acceptCallback_(clifd,*reinterpret_cast<sockaddr_storage*>(&cliaddr));
}

