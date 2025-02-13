#include "FloatType.h"

void FloatType::serialize(Buffer& buffer) const
{
    HelpersSerialize::serializeVariant(value, buffer);
}

Buffer::const_iterator FloatType::deserialize(Buffer::const_iterator it, Buffer::const_iterator end)
{
    return HelpersSerialize::deserializeType<double>(it, end, value);
}
