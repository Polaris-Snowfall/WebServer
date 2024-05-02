#ifndef __LOGGING_H
#define __LOGGING_H
#include <string>
#include <sstream>
#include <functional>

class Logger{
public:

    enum class LogLevel{
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVELS
    
    };

    Logger(const std::string &file, int line);
    Logger(const std::string& filename, int line, LogLevel level, const std::string& func);
    Logger(const std::string& filename, int line, LogLevel level);
    ~Logger();

    static LogLevel logLevel() { return logLevel_;}
    static void setLogLevel(LogLevel logLevel) { logLevel_ = logLevel;}
    static void setOutputFunc(std::function<void(const std::string&)> func) { outputFunc_ = func;}

    std::stringstream& stream() { return stream_;}
private:
    static LogLevel logLevel_;
    static std::function<void(const std::string&)> outputFunc_;
    std::stringstream stream_;
    
    class LogMsgInfo{
    public:
        LogLevel logLevel_;
        std::string filename_;
        int line_;
        std::string func_;

        const std::string levelstr()
        {
            std::string fmtstr{};
            switch (logLevel_)
            {
            case LogLevel::TRACE:
                fmtstr += "[TRACE] ";
                break;
            case LogLevel::INFO:
                fmtstr += "[INFO] ";
                break;
            case LogLevel::DEBUG:
                fmtstr += "[DEBUG] ";
                break;
            case LogLevel::WARN:
                fmtstr += "[WARN] ";
                break;
            case LogLevel::ERROR:
                fmtstr += "[ERROR] ";
                break;
            case LogLevel::FATAL:
                fmtstr += "[FATAL] ";
                break;
            default:
                break;
            }

            return fmtstr;
        }

        const std::string fmt()
        {
            std::stringstream stream;
            stream << filename_ << " " << line_ << " " << func_ << "\n";    
            return stream.str();
        }
    }logMsgInfo;

};

#define LOG_TRACE if(Logger::logLevel() <= Logger::LogLevel::TRACE) \
    Logger(__FILE__,__LINE__,Logger::LogLevel::TRACE,__func__).stream()
#define LOG_DEBUG if (Logger::logLevel() <= Logger::LogLevel::DEBUG) \
  Logger(__FILE__, __LINE__, Logger::LogLevel::DEBUG, __func__).stream()
#define LOG_INFO if (Logger::logLevel() <= Logger::LogLevel::INFO) \
  Logger(__FILE__, __LINE__).stream()
#define LOG_WARN Logger(__FILE__, __LINE__, Logger::LogLevel::WARN).stream()
#define LOG_ERROR Logger(__FILE__, __LINE__, Logger::LogLevel::ERROR).stream()
#define LOG_FATAL Logger(__FILE__, __LINE__, Logger::LogLevel::FATAL).stream()
#define LOG_SYSERR Logger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL Logger(__FILE__, __LINE__, true).stream()

#endif