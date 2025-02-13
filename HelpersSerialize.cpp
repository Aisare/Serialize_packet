#include "HelpersSerialize.h"

Helpers::ValueType HelpersSerialize::deserializeByType(TypeId typeId, Buffer::const_iterator& it, Buffer::const_iterator end)
{
    switch (typeId)
    {
        case TypeId::Uint:
        {
            IntegerType intValue;
            it = intValue.deserialize(it, end);
            return intValue;
        }
        case TypeId::Float:
        {
            FloatType floatValue;
            it = floatValue.deserialize(it, end);
            return floatValue;
        }
        case TypeId::String:
        {
            StringType stringValue;
            it = stringValue.deserialize(it, end);
            return stringValue;
        }
        case TypeId::Vector:
        {
            VectorType vectorValue;
            it = vectorValue.deserialize(it, end);
            return std::move(vectorValue);
        }
        default:
            throw std::runtime_error("Unknown TypeId during deserialization");
    }
}

uint64_t HelpersSerialize::deserializeUint64(Buffer::const_iterator& it, Buffer::const_iterator end)
{
    uint64_t size;
    if (std::distance(it, end) < static_cast<std::ptrdiff_t>(sizeof(size)))
    {
        throw std::runtime_error("Buffer underflow while reading size");
    }
    Helpers::readFromBuffer(it, &size, sizeof(size));

    return size;
}

void HelpersSerialize::checkBufferSize(Buffer::const_iterator it, Buffer::const_iterator end, size_t size, std::string message)
{
    if (std::distance(it, end) < static_cast<std::ptrdiff_t>(size))
    {
        throw std::runtime_error(message);
    }
}

void HelpersSerialize::serializeSize(Buffer& buffer, uint64_t size)
{
    Helpers::appendToBuffer(buffer, &size, sizeof(size));
}

bool HelpersSerialize::compareVariants(const Helpers::ValueType& lvar, const Helpers::ValueType& rvar)
{
    return std::visit([](const auto& lhs, const auto& rhs) -> bool
        {
            using LType = std::decay_t<decltype(lhs)>;
            using RType = std::decay_t<decltype(rhs)>;

            if constexpr (std::is_same_v<LType, RType>)
            {
                if constexpr (std::is_same_v<LType, IntegerType>)
                {
                    return lhs.value == rhs.value;
                }
                else if constexpr (std::is_same_v<LType, FloatType>)
                {
                    return lhs.value == rhs.value;
                }
                else if constexpr (std::is_same_v<LType, StringType>)
                {
                    return lhs.value == rhs.value;
                }
                else if constexpr (std::is_same_v<LType, VectorType>)
                {
                    return compareVector(lhs.value, rhs.value);
                }
            }
            return false;
        }, lvar, rvar);
}

bool HelpersSerialize::compareVector(const std::vector<Helpers::ValueType>& lvec, const std::vector<Helpers::ValueType>& rvec)
{
    if (lvec.size() != rvec.size())
    {
        return false;
    }

    for (size_t i = 0; i < lvec.size(); ++i)
    {
        if (!compareVariants(lvec[i], rvec[i]))
        {
            return false;
        }
    }

    return true;
}