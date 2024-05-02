#include <FixedBuffer.h>
#include <algorithm>

template <int SIZE>
void FixedBuffer<SIZE>::append(const std::string &data)
{
    size_t appendSize = std::min(avail(),data.size());
    std::copy_n(data.begin(),appendSize,data_.begin()+cursize_);
    return;
}
