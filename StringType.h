#ifndef STRINGTYPEH
#define STRINGTYPEH

#include "Helpers.h"
#include "HelpersSerialize.h"

class StringType
{
public:
    /// <summary>
    /// ����������� �� ���������, ��� �� ��������� ��������� � std::string
    /// </summary>
    StringType() : value("") {}
    /// <summary>
    /// ����������� � ����������
    /// </summary>
    /// <param name="val">��������� �������� ��� �������������</param>
    StringType(std::string val) : value(std::move(val)) {}
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
    /// �������� ��������� ��������
    /// </summary>
    Helpers::GenEntity value;
    /// <summary>
    /// ���� ����� �������� ������ ��� ������ HelpersSerialize
    /// </summary>
    friend class HelpersSerialize;
};
#endif

