#include <util.h>
#include <thread>

void errorExit(const std::string& errorMsg)
{
    LOG_FATAL <<"Thread " << gettid() << " "<< errorMsg << ":" << strerror(errno);
    exit(-1);
}