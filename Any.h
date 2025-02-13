#ifndef ANYH
#define ANYH

#include "Helpers.h"
#include "IntegerType.h"
#include "FloatType.h"
#include "StringType.h"
#include "VectorType.h"
/// <summary>
/// Any - �����, ������� ����� ��������� �������� ��������� �����
/// ����� ������� �������� ����� IntegerType, FloatType, StringType � VectorType
/// </summary>
class Any
{
public:
    /// <summary>
    /// ����������� �� ���������
    /// </summary>
    Any() = default;
    /// <summary>
    /// �����������, ������� �������������� ������ ���� Any ��������� ������ �� �������������� �����:
    /// IntegerType, FloatType, StringType, VectorType
    /// </summary>
    /// <typeparam name="Args">��� ������������� ��������</typeparam>
    /// <param name="val">��������, ������� ����� ���������</param>
    template<typename Args, typename = std::enable_if_t<std::is_same_v<std::decay_t<Args>, IntegerType> ||
                                                        std::is_same_v<std::decay_t<Args>, FloatType> ||
                                                        std::is_same_v<std::decay_t<Args>, StringType> ||
                                                        std::is_same_v<std::decay_t<Args>, VectorType>>>
    Any(Args&& val) : storage(std::forward<Args>(val)) {}
    /// <summary>
    /// ����������� ������ � ��������� ��� �������� ������������� � �����
    /// </summary>
    /// <param name="buffer">�����, � ������� ������������ ��������������� ������</param>
    void serialize(Buffer& buffer) const;
    /// <summary>
    /// ������������� ������ �� ������
    /// </summary>
    /// <param name="it">�������� �� ������ ������ � ������</param>
    /// <param name="end">�������� �� ����� ������</param>
    /// <returns>�������� �� ������� ����� ����������� ������</returns>
    Buffer::const_iterator deserialize(Buffer::const_iterator _begin, Buffer::const_iterator _end);
    /// <summary>
    /// ���������� ������������� ���� ������, �������� � �������
    /// </summary>
    /// <returns>���������� TypeId, ������� ������������� ���� ������, �������� � ������� </returns>
    TypeId getPayloadTypeId() const;
    /// <summary>
    /// ��������� �������� ���� Type �� �������
    /// ���� ��� �� ��������� � ���������, ����������� ���������� std::bad_variant_access
    /// </summary>
    /// <typeparam name="Type">���, ������� ���������� ������� �� �������</typeparam>
    /// <returns>������ �� �������� ���� Type, �������� � �������</returns>
    /// <exception cref="std::runtime_error">���������, ���� ��� ������ � ������� �� ������������� ����������</exception>
    template<typename Type>
    auto& getValue() const
    {
        try
        {
            return std::get<Type>(storage);
        }
        catch (const std::bad_variant_access& e)
        {
            throw std::runtime_error("Type mismatch in getValue()");
        }
    }
    /// <summary>
    /// ��������� ��������, ��������������� ����������� TypeId �� �������
    /// ���� ���������� TypeId �� ��������� � ������� ����� ������ � �������, ����������� ����������
    /// </summary>
    /// <typeparam name="kId">������������� ����, ������� ���������� ������� �� �������</typeparam>
    /// <returns>������ �� ��������, ��������������� ����, ��������� kId</returns>
    /// <exception cref="std::runtime_error">���������, ���� kId �� ������������� ���� ������ � �������</exception>
    template<TypeId kId>
    auto& getValue() const
    {
        if (kId == TypeId::Integer)
        {
            return std::get<IntegerType>(storage);
        }
        else if (kId == TypeId::Float)
        {
            return std::get<FloatType>(storage);
        }
        else if (kId == TypeId::String)
        {
            return std::get<StringType>(storage);
        }
        else if (kId == TypeId::Vector)
        {
            return std::get<VectorType>(storage);
        }
        throw std::runtime_error("Invalid TypeId");
    }
    /// <summary>
    /// �������� ��������� ���� �������� Any
    /// </summary>
    /// <param name="other">������ ��� ���������</param>
    /// <returns>True, ���� �������� �����, ����� false</returns>
    bool operator==(const Any& other) const;
private:
    /// <summary>
    /// ������ ������ ��������� �����, ����� ��� IntegerType, FloatType, StringType, ��� VectorType, � ���� ������� � �������������� std::variant
    /// ��� ��������� ������� ������ ���� � ����� �������, ��� ���� ����������, ��� � ����� ������ ������� ����� �������� ������ ���� ���
    /// </summary>
    Helpers::ValueType storage;
};
#endif