#include <Channel.h>
#include <sys/epoll.h>

const uint32_t Channel::nonEvent = 0;
const uint32_t Channel::readEvent = EPOLLIN | EPOLLPRI;
const uint32_t Channel::writeEvent = EPOLLOUT;


const Channel::EventCallback Channel::setReadCallback(const EventCallback &cb)
{
    const EventCallback prev = readCallback_;
    readCallback_ = cb;
    return prev;
}


const Channel::EventCallback Channel::setWriteCallback(const EventCallback &cb)
{
    const EventCallback prev = writeCallback_;
    writeCallback_ = cb;
    return prev;
}


const Channel::EventCallback Channel::setCloseCallback(const EventCallback &cb)
{
    const EventCallback prev = closeCallback_;
    closeCallback_ = cb;
    return prev;
}

const Channel::EventCallback Channel::setErrorCallback(const EventCallback &cb)
{
    const EventCallback prev = errorCallback_;
    errorCallback_ = cb;
    return prev;
}

void Channel::handleEvent()
{
    if(tie_.lock())
        handleEventWithGuard();
}

void Channel::handleEventWithGuard()
{
if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
  {
    if (closeCallback_) closeCallback_();
  }

  if (revents_ & (EPOLLERR))
  {
    if (errorCallback_) errorCallback_();
  }
  if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
  {
    if (readCallback_) readCallback_();
  }
  if (revents_ & EPOLLOUT)
  {
    if (writeCallback_) writeCallback_();
  }
}