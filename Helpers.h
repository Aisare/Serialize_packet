#ifndef HELPERSH
#define HELPERSH
#include <iostream>
#include <vector>
#include <fstream>
#include <type_traits>
#include <variant>
#include <string>

/// <summary>
/// ��� Id ������������ ����� ����� ��� ���� uint64_t
/// </summary>
using Id = uint64_t;
/// <summary>
/// ��� Buffer ������������ ����� ��������� std::vector<std::byte>, ������� ������������ ��� �������� �������� ������
/// </summary>
using Buffer = std::vector<std::byte>;
/// <summary>
/// ������������ TypeId ���������� ���� ������, ������� ����� ���� �������������/���������������
/// ������ ������� ������������ ������������� ����������� ���� ������:
/// Uint - ������������� ���
/// Float - ��� � ��������� ������
/// String - ��������� ���
/// Vector - ���, �������������� ������
/// </summary>
enum class TypeId : Id 
{
    Uint,
    Float,
    String,
    Vector
};

/// <summary>
/// ��������������� ���������� �������
/// </summary>
class IntegerType;
class FloatType;
class StringType;
class VectorType;

/// <summary>
/// Helpers - ����� ������������� ��������������� ������� ��� ������ � ��������
/// </summary>
class Helpers
{
public:
    /// <summary>
    /// ���������� ��� ������, ��� ���������� ������� ����� ����
    /// IntegerType, FloatType, StringType ��� VectorType
    /// </summary>
    using ValueType = std::variant<IntegerType, FloatType, StringType, VectorType>;
    /// <summary>
    /// ���������� ��� ������, ��� ���������� ������� ����� ����
    /// uint64_t, double ��� std::string
    /// </summary>
    using GenEntity = std::variant<uint64_t, double, std::string>;
    /// <summary>
    /// ��������� ������ � �����
    /// </summary>
    /// <param name="buffer">�����, � ������� ����������� ������</param>
    /// <param name="data">������, ������� ����� �������� � �����</param>
    /// <param name="size">������ ������, ������� ����� ��������� � �����</param>
    static void appendToBuffer(Buffer& buffer, const void* data, size_t size);
    /// <summary>
    /// ��������� ������ �� ������, ������� � ������� ������� ���������
    /// </summary>
    /// <param name="it">�������� �� ������� ������� � ������, ������� ����� �������� ����� ������ ������</param>
    /// <param name="data">����� ���������� ��� ������, ������� ����� ��������� �� ������</param>
    /// <param name="size">������ ������, ������� ����� ���������</param>
    static void readFromBuffer(Buffer::const_iterator& it, Helpers::GenEntity& value, size_t size);
    /// <summary>
    /// ��������� ������ �� ������, ������� � ������� ������� ���������
    /// </summary>
    /// <param name="it">�������� �� ������� ������� � ������, ������� ����� �������� ����� ������ ������</param>
    /// <param name="value">����� ���������� ��� ������, ������� ����� ��������� �� ������</param>
    /// <param name="size">������ ������, ������� ����� ���������</param>
    static void readFromBuffer(Buffer::const_iterator& it, void* value, size_t size);
    /// <summary>
    /// ������� ��� ��������� ���� TypeId �� ����������� variant ����
    /// </summary>
    /// <typeparam name="VariantType">��� variant, �� �������� ����� ������� TypeId</typeparam>
    /// <param name="var">Variant ��������, ��� �������� ���������� ����������</param>
    /// <returns>��� ������ TypeId</returns>
    template <typename VariantType>
    static TypeId getTypeIdFromVariant(const VariantType& var)
    {
        return std::visit([](const auto& v) -> TypeId
            {
                using T = std::decay_t<decltype(v)>;
                if constexpr (std::is_same_v<T, IntegerType>)
                {
                    return TypeId::Uint;
                }
                else if constexpr (std::is_same_v<T, FloatType>)
                {
                    return TypeId::Float;
                }
                else if constexpr (std::is_same_v<T, StringType>)
                {
                    return TypeId::String;
                }
                else if constexpr (std::is_same_v<T, VectorType>)
                {
                    return TypeId::Vector;
                }
            }, var);
    }
};


#endif // HELPERS



