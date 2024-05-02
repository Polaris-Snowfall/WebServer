#include <util.h>


void errorExit(const std::string& errorMsg)
{
    LOG_FATAL << errorMsg << ":" << strerror(errno);
    exit(-1);
}