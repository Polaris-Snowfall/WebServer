#include <Poller.h>
#include <Channel.h>
#include <util.h>

const int  Poller::initial_nevents = 16;

Poller::Poller() : eventslist_(initial_nevents)
{
    LOG_DEBUG << "Thread " << gettid() << " "<< "Poller create";
    poll_fd_ = epoll_create1(0);
    if(poll_fd_ == -1)
    {
        errorExit("Poller::epoll_create1:");
    }
}

Poller::~Poller()
{
    LOG_DEBUG << "Thread " << gettid() << " "<< "Poller destroy";
    int ret = close(poll_fd_);
    if(ret < 0)
        errorExit("~Poller::close");
}

void Poller::poll(int timeoutMs,ChannelList& activeChannels)
{
    LOG_INFO << "Thread " << gettid() << " "<< "Poller wait";
    int numEvents = epoll_wait(poll_fd_,eventslist_.data(),
                                static_cast<int>(eventslist_.size()),timeoutMs);
    LOG_INFO << "Thread " << gettid() << " "<< "Poller weakup";
    if (numEvents == -1) 
    {
        if(errno != EINTR)
            errorExit("Poller::epoll_wait"); 
    }

    // 如果最大events数量等于本次返回事件数量,将其加倍.
    if(numEvents == static_cast<int>(eventslist_.size()))
    {
        LOG_DEBUG << "Thread " << gettid() << " "<<"Poller resize";
        eventslist_.resize(2*eventslist_.size());
    }
    
    //更新activeChannels
    std::for_each_n(eventslist_.begin(),numEvents,[this,&activeChannels](struct epoll_event& ev){

        channels_[ev.data.fd]->setRevents(ev.events);
        activeChannels.emplace_back(channels_[ev.data.fd]);

    });
}

void Poller::updateChannel(std::shared_ptr<Channel> channel)
{
    int operation;
    if(channels_.find(channel->fd()) != channels_.end())
    {
        LOG_DEBUG << "Thread " << gettid() << " "<< "Poller Mod/Del Channel";
        operation = channel->isNonEvent() ? EPOLL_CTL_DEL : EPOLL_CTL_MOD;
    }
    else
    {
        LOG_DEBUG << "Thread " << gettid() << " "<< "Poller add Channel";
        operation = EPOLL_CTL_ADD;
        channels_[channel->fd()] = channel;
    }
    update(operation,channel);
}

void Poller::update(int operation,std::shared_ptr<Channel> channel)
{
    struct epoll_event ev;

    ev.events = channel->events();
    ev.data.fd = channel->fd();

    if(epoll_ctl(poll_fd_,operation,channel->fd(),&ev) == -1)
    {
        errorExit("Poller::epoll_ctl");
    }

}