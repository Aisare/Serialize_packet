#include "Any.h"

void Any::serialize(Buffer& buffer) const
{
    HelpersSerialize::serializeSize(buffer, static_cast<uint64_t>(getPayloadTypeId()));
    std::visit([&buffer](const auto& v) { v.serialize(buffer); }, storage);
}

Buffer::const_iterator Any::deserialize(Buffer::const_iterator _begin, Buffer::const_iterator _end)
{
    if (_begin == _end) 
    {
        throw std::runtime_error("Buffer is empty");
    }

    TypeId typeId = static_cast<TypeId>(HelpersSerialize::deserializeUint64(_begin, _end));

    if (typeId == TypeId::Vector)
    {
        VectorType vectorAdd = std::get<VectorType>(HelpersSerialize::deserializeByType(typeId, _begin, _end));
        storage.emplace<VectorType>(std::move(vectorAdd));
    }
    else
    {
        storage = HelpersSerialize::deserializeByType(typeId, _begin, _end);
    }

    return _begin;
}

TypeId Any::getPayloadTypeId() const
{
    return Helpers::getTypeIdFromVariant(storage);
}

bool Any::operator==(const Any& other) const
{
    return HelpersSerialize::compareVariants(storage, other.storage);
}

