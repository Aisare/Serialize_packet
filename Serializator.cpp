#include "Serializator.h"

Buffer Serializator::serialize() const
{
    Buffer buffer;

    HelpersSerialize::serializeSize(buffer, storage.size());

    for (const auto& anyValue : storage)
    {
        anyValue.serialize(buffer);
    }

    return buffer;
}

std::vector<Any> Serializator::deserialize(const Buffer& _val)
{
    Buffer::const_iterator it = _val.cbegin();
    Buffer::const_iterator end = _val.cend();
    
    std::vector<Any> result;

    uint64_t size = HelpersSerialize::deserializeUint64(it, end);
   
    for (int i = 0; i < size; i++)
    {
        Any any;
        it = any.deserialize(it, end);
        result.push_back(std::move(any));
    }

    return result;
}

const std::vector<Any>& Serializator::getStorage() const
{
    return storage;
}
