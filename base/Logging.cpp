#include <Logging.h>
#include <unistd.h>

Logger::LogLevel Logger::logLevel_ = Logger::LogLevel::INFO;


Logger::Logger(const std::string& filename, int line)
  : logMsgInfo{Logger::LogLevel::INFO,filename,line}
{

}

Logger::Logger(const std::string& filename, int line, LogLevel level, const std::string& func)
  : logMsgInfo{level,filename,line}
{

}

Logger::Logger(const std::string& filename, int line, LogLevel level)
  : logMsgInfo{level,filename,line}
{

}

Logger::~Logger()
{
    std::string log = logMsgInfo.levelstr();
    log += "\"" + stream_.str() + "\" ";
    log += logMsgInfo.fmt();
    outputFunc_(log);
}

void defaultOutputFunc(const std::string& data)
{
    write(2,data.c_str(),data.size());
}

std::function<void(const std::string&)> Logger::outputFunc_ = defaultOutputFunc;