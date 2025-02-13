#ifndef HELPERSERIALIZEH
#define HELPERSERIALIZEH

#include "Helpers.h"
#include "IntegerType.h"
#include "FloatType.h"
#include "StringType.h"
#include "VectorType.h"

/// <summary>
/// �����, ��������������� ������ ��� ������������ � �������������� ������,
/// � ����� ��� ��������� ��������� ����� ������
/// </summary>
class HelpersSerialize
{
public:
    /// <summary>
    /// ������������� ������ �� ����
    /// </summary>
    /// <param name="typeId">������������� ���� ������ ��� ��������������</param>
    /// <param name="it">�������� �� ������ ������ � ������, ���� �������� ����� �������� ����� ������ ������, �������� �� ����� ������� ����� ����������</param>
    /// <param name="end">�������� �� ����� ������ � ������</param>
    /// <returns>���������� ����������������� ������ ���������������� ����</returns>
    static Helpers::ValueType deserializeByType(TypeId typeId, Buffer::const_iterator& it, Buffer::const_iterator end);
    /// <summary>
    /// ������������� 64-������ ����� ����� uint64_t �� ������
    /// </summary>
    /// <param name="it">�������� �� ������ ������ � ������, ���� �������� ����� �������� ����� ������ ������, �������� �� ����� ������� ����� ����������</param>
    /// <param name="end">�������� �� ����� ������ � ������</param>
    /// <returns>���������� ����������������� 64-������ ����� �����</returns>
    static uint64_t deserializeUint64(Buffer::const_iterator& it, Buffer::const_iterator end);
    /// <summary>
    /// ��������� ������ ������ � ������
    /// ���� ������ ������ ������ ������������, ����������� ����������
    /// </summary>
    /// <param name="it">�������� �� ������ ������ � ������</param>
    /// <param name="end">�������� �� ����� ������ � ������</param>
    /// <param name="size">����������� ������ ������</param>
    /// <param name="message">��������� ��� ���������� � ������ ������</param>
    static void checkBufferSize(Buffer::const_iterator it, Buffer::const_iterator end, size_t size,std::string message);
    /// <summary>
    /// ����������� ������ ������ � ���������� ��� � �����
    /// </summary>
    /// <param name="buffer">�����, � ������� ����� ������� ������</param>
    /// <param name="size">������ ������</param>
    static void serializeSize(Buffer& buffer, uint64_t size);
    /// <summary>
    /// ���������� ��� ������� ���� ValueType
    /// </summary>
    /// <param name="lvar">������ ������ ��� ���������</param>
    /// <param name="rvar">������ ������ ��� ���������</param>
    /// <returns>True, ���� ������� �����, ����� false</returns>
    static bool compareVariants(const Helpers::ValueType& lvar, const Helpers::ValueType& rvar);
    /// <summary>
    /// ���������� ��� �������, ���������� ������� ���� ValueType
    /// </summary>
    /// <param name="lvec">������ ������ ��� ���������</param>
    /// <param name="rvec">������ ������ ��� ���������</param>
    /// <returns>True, ���� ������� �����, ����� false</returns>
    static bool compareVector(const std::vector<Helpers::ValueType>& lvec, const std::vector<Helpers::ValueType>& rvec);
    /// <summary>
    /// ����������� ����������� ��� ������ � ���������� ��� � �����
    /// (uint64_t, double, std::string)
    /// </summary>
    /// <typeparam name="T">��� ������ ��� ������������</typeparam>
    /// <param name="value">�������� ��� ������������</param>
    /// <param name="buffer">�����, � ������� ����� �������� ������</param>
    template <typename T>
    static void serializePrimitive(const T& value, Buffer& buffer)
    {
        if constexpr (std::is_same_v<T, std::string>)
        {
            uint64_t size = value.size();
            HelpersSerialize::serializeSize(buffer, size); 
            Helpers::appendToBuffer(buffer, value.data(), size); 
        }
        else
        {
            Helpers::appendToBuffer(buffer, &value, sizeof(T));
        }
    }
    /// <summary>
    /// ����������� ������������ ������� std::variant � �����
    /// </summary>
    /// <typeparam name="VariantType">��� ������ � std::variant</typeparam>
    /// <param name="var">������, ������� ����� �������������</param>
    /// <param name="buffer">�����, � ������� ����� �������� ������</param>
    template <typename VariantType>
    static void serializeVariant(const VariantType& var, Buffer& buffer)
    {
        std::visit([&buffer](const auto& value)
            {
                serializePrimitive(value, buffer);
            }, var);
    }

    /// <summary>
    /// �������������� �������� �����
    /// </summary>
    /// <typeparam name="VariantType">��� ������ � std::variant</typeparam>
    /// <param name="it">�������� �� ������ ������ � ������</param>
    /// <param name="end">�������� �� ����� ������</param>
    /// <param name="value">����������, � ������� ����� �������� ����������������� ������</param>
    /// <returns>��������, ����������� ����� ������ ������ �� ������</returns>
    template <typename VariantType>
    static Buffer::const_iterator deserializeType(Buffer::const_iterator it, Buffer::const_iterator end, Helpers::GenEntity& value)
    {
        if constexpr (std::is_same_v<VariantType, uint64_t> || std::is_same_v<VariantType, double>)
        {
            HelpersSerialize::checkBufferSize(it, end, sizeof(uint64_t), "Buffer underflow while reading");
            Helpers::readFromBuffer(it, value, sizeof(uint64_t));
        }
        else if constexpr (std::is_same_v<VariantType, std::string>)
        {
            uint64_t size = HelpersSerialize::deserializeUint64(it, end);
            HelpersSerialize::checkBufferSize(it, end, size, "Buffer underflow while reading string data");
            Helpers::readFromBuffer(it, value, size);
        }
        return it;
    }
};
#endif
