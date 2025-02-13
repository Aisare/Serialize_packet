#ifndef FLOATTYPEH
#define FLOATTYPEH

#include "Helpers.h"
#include "HelpersSerialize.h"
/// <summary>
/// FloatType - ����� ��� ������� ��������
/// </summary>
class FloatType
{
public:
    /// <summary>
    /// ����������� �� ���������, ��� �� ��������� ��������� � double
    /// </summary>
    FloatType() : value(0.0) {}
    /// <summary>
    /// ����������� � ����������
    /// </summary>
    /// <param name="val">�������� �������� ��� �������������</param>
    FloatType(double val) : value(val) {}
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


