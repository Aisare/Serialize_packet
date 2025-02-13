#include "VectorType.h"

void VectorType::serialize(Buffer& buffer) const
{
    HelpersSerialize::serializeSize(buffer, value.size());

    for (const auto& elem : value)
    {
        TypeId type = Helpers::getTypeIdFromVariant(elem);
        std::visit([&buffer,&type](const auto& v) 
        {
            using T = std::decay_t<decltype(v)>;
            Helpers::appendToBuffer(buffer, &type, sizeof(type));
            v.serialize(buffer);
        }, elem);
    }
}

Buffer::const_iterator VectorType::deserialize(Buffer::const_iterator it, Buffer::const_iterator end)
{
    uint64_t size = HelpersSerialize::deserializeUint64(it, end);
    
    value.clear();
    for (uint64_t i = 0; i < size; ++i)
    {
        TypeId typeId = static_cast<TypeId>(HelpersSerialize::deserializeUint64(it, end));
        value.emplace_back(std::move(HelpersSerialize::deserializeByType(typeId,it,end)));
    }

    return it;
}
