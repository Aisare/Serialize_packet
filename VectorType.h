#ifndef VECTORTYPEH
#define VECTORTYPEH

#include "Helpers.h"
#include "IntegerType.h"
#include "FloatType.h"
#include "StringType.h"
#include "HelpersSerialize.h"
/// <summary>
/// VectorType - �����, �������������� ������, ������� ����� ��������� �������� ��������� �����
/// ������ ����� ������� �������� ����� IntegerType, FloatType, StringType � ������ �������
/// </summary>
class VectorType
{
public:
    /// <summary>
    /// ����������� �� ���������
    /// ������ ������ ������
    /// </summary>
    VectorType() = default;
    /// <summary>
    /// �����������, ������� ��������� ������������ ���������� ���������� � ��������� �� � ������
    /// </summary>
    /// <typeparam name="...Args">���� ���������, ������� ����� ��������� � ������</typeparam>
    /// <param name="...args">��������, ������� ����� ��������� � ������ ��� �� ��������, ��� � �� ������</param>
    template<typename... Args>
    VectorType(Args&& ...args)
    {
        (push_back(std::forward<Args>(args)), ...);
    }
    /// <summary>
    /// ��������� ������� � ������
    /// ��� �������� ������ ���� ����� ��: IntegerType, FloatType, StringType ��� VectorType, ������ ���� ��������� �� �����
    /// </summary>
    /// <typeparam name="Args">��� ������������� ��������</typeparam>
    /// <param name="_val">�������, ������� ����� �������� � ������</param>
    template<typename Args>
    void push_back(Args&& _val)
    {
        if constexpr (std::is_same_v<std::decay_t<Args>, IntegerType> ||
            std::is_same_v<std::decay_t<Args>, FloatType> ||
            std::is_same_v<std::decay_t<Args>, StringType> ||
            std::is_same_v<std::decay_t<Args>, VectorType>)
        {
            value.emplace_back(std::forward<Args>(_val));
        }
    }
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
    Buffer::const_iterator deserialize(Buffer::const_iterator it, Buffer::const_iterator end);
private:
    /// <summary>
    /// ��������� ���������, ������ �� ������� ����� ���� ����� �� �����: IntegerType, FloatType, StringType ��� VectorType
    /// ���������� std::variant ��� �������� ��������� ������ �����, ��� ���� ��� �������� �������� � ����� ����������
    /// ���� ��������� ������������ ����������, �������� � ������ � ���������, ��� ���� �������������, ��� ������ ������� ����� ������ �� ������� ����������� �����
    /// </summary>
    std::vector<Helpers::ValueType> value;
    /// <summary>
    /// ���� ����� �������� ������ ��� ������ HelpersSerialize
    /// </summary>
    friend class HelpersSerialize;
};

#endif

