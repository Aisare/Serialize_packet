#include "Helpers.h"

void Helpers::appendToBuffer(Buffer& buffer, const void* data, size_t size)
{
    const auto* bytes = static_cast<const std::byte*>(data);
    buffer.insert(buffer.end(), bytes, bytes + size);
}

void Helpers::readFromBuffer(Buffer::const_iterator& it, Helpers::GenEntity& value, size_t size) {
    std::visit([&](auto&& val) 
    {
        using T = std::decay_t<decltype(val)>;

        if constexpr (std::is_same_v<T, uint64_t> || std::is_same_v<T, double>)
        {
            if (std::distance(it, it + size) < size) 
            {
                throw std::runtime_error("Not enough data in buffer to read value");
            }
            std::memcpy(&val, &(*it), size);
            it += size;
            return;
        }
        else if constexpr (std::is_same_v<T, std::string>) 
        {
            if (std::distance(it, it + size) < size)
            {
                throw std::runtime_error("Not enough data in buffer to read string");
            }
            val.resize(size);
            std::memcpy(&val[0], &(*it), size);
            it += size;
        }
    }, value);
}

void Helpers::readFromBuffer(Buffer::const_iterator& it, void* value, size_t size)
{
    std::memcpy(value, &(*it), size);
    it += size;
}


