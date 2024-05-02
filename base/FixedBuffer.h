#ifndef __FIXEDBUFFER_H
#define __FIXEDBUFFER_H
#include <array>
#include <string>
#include <span>

template <int SIZE>
class FixedBuffer{
public:
    void append(const std::string& data);
    size_t avail() { return SIZE-cursize_;}
    std::span<char,SIZE> data() { return std::span<char,SIZE>(data_);}
private:
    size_t cursize_;
    std::array<char,SIZE> data_;
};

#endif

