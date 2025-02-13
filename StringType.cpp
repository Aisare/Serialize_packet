#include "StringType.h"

void StringType::serialize(Buffer& buffer) const
{
    HelpersSerialize::serializeVariant(value, buffer);
}

Buffer::const_iterator StringType::deserialize(Buffer::const_iterator it, Buffer::const_iterator end)
{
    return HelpersSerialize::deserializeType<std::string>(it, end, value);
}