#include <TCPServer.h>
#include <EventLoop.h>
#include <sys/socket.h>

int main()
{
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(7777);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    EventLoop main_loop;
    TCPServer serv(&main_loop,*reinterpret_cast<sockaddr_storage*>(&servaddr));

    serv.start();
    main_loop.loop();
}