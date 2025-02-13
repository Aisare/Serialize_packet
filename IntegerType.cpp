#include "IntegerType.h"

void IntegerType::serialize(Buffer& buffer) const
{
    HelpersSerialize::serializeVariant(value,buffer);
}

Buffer::const_iterator IntegerType::deserialize(Buffer::const_iterator it, Buffer::const_iterator end)
{
    return HelpersSerialize::deserializeType<uint64_t>(it, end, value);
}
