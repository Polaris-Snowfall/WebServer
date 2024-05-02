#ifndef __NONCOPYABLE_H
#define __NONCOPYABLE_H
class NonCopyable{
public:
    NonCopyable() = default;

    NonCopyable(const NonCopyable& other) = delete;
    NonCopyable& operator=(const NonCopyable& other) = delete;
    NonCopyable(NonCopyable&& other) = delete;
    NonCopyable& operator=(NonCopyable&& other) = delete;
};
#endif