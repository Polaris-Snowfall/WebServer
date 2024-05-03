#include <TCPConnection.h>

TCPConnection::TCPConnection(int fd,const sockaddr_storage& cliAddr,EventLoop* loop)
: fd_(fd),loop_(loop),cliAddr_(*reinterpret_cast<const sockaddr_in*>(&cliAddr)),
  channel_(std::make_shared<Channel>(loop_,fd))
{
    channel_->setReadCallback([this](){
        
        std::cout << "Received: ";
        while(read(fd_,buf_,200))
        {
            std::cout << buf_ ;
        }
        std::cout << "\n";
    });
    // channel_->setWriteCallback([this](){
    //     if(buf_[0] != '\0')
    //     {
    //         write(fd_,buf_,200);
    //     }
    //     memset(buf_,0,200);
    // });
    // channel_->enableWriting();
    channel_->enableReading();
}
