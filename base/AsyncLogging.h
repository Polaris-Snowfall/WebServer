#ifndef __ASYNCLOGGING_H
#define __ASYNCLOGGING_H
// #include <string>
// #include <vector>
// #include <FixedBuffer.h>
// #include <memory>
// #include <condition_variable>
// #include <NonCopyable.h>


// template <typename BufferSize>
// class AsyncLogging : NonCopyable{
// public:
//     AsyncLogging(const std::string& basename);
//     ~AsyncLogging();

//     void append(const std::string& data);

// private:

//     using Buffer = FixedBuffer<BufferSize>;
//     using BufferPtr = std::unique_ptr<Buffer>;
//     using BufferVec = std::vector<BufferPtr>;

//     BufferPtr curBuffer_;
//     BufferPtr nextBuffer_;
//     BufferVec filled_buffers_;
//     std::mutex mutex_;
//     std::condition_variable cond;

// };

#endif