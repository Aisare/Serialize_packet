#ifndef INTEGERTYPEH
#define INTEGERTYPEH

#include "Helpers.h"
#include "HelpersSerialize.h"
/// <summary>
/// IntegerType - ����� ��� ������������� ��������
/// </summary>
class IntegerType
{
public:
    /// <summary>
    /// ����������� �� ���������, ��� �� ��������� ��������� � uint64_t
    /// </summary>
    IntegerType() : value(uint64_t(0)) {}
    /// <summary>
    /// ����������� � ����������
    /// </summary>
    /// <param name="val">�������� �������� ��� �������������</param>
    IntegerType(uint64_t val) : value(val) {}
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
    /// �������� ������������� ��������
    /// </summary>
    Helpers::GenEntity value;
    /// <summary>
    /// ���� ����� �������� ������ ��� ������ HelpersSerialize
    /// </summary>
    friend class HelpersSerialize;
};
#endif


