#ifndef SERIALIZATORH
#define SERIALIZATORH

#include "Any.h"
/// <summary>
/// ����� Serializator �������� �� ������������ � �������������� ��������� ����� ������, � ����� �������� ���� ������ � ���������� 
/// �� ����� ������������� ������� ����� IntegerType, FloatType, StringType, VectorType � Any, ����������� �� ���������� � ���������
/// </summary>
class Serializator
{
public:
    /// <summary>
    /// ��������� ������� � ���������
    /// �������� ����� ���� ������ �� �����: IntegerType, FloatType, StringType,VectorType ��� Any
    /// </summary>
    /// <typeparam name="Arg">��� ������������� ��������</typeparam>
    /// <param name="_val">�������, ������� ����� �������� � ���������</param>
    /// <returns></returns>
    template<typename Arg>
    typename std::enable_if<
        std::is_same<std::decay_t<Arg>, IntegerType>::value ||
        std::is_same<std::decay_t<Arg>, FloatType>::value ||
        std::is_same<std::decay_t<Arg>, StringType>::value ||
        std::is_same<std::decay_t<Arg>, VectorType>::value ||
        std::is_same<std::decay_t<Arg>, Any>::value,
        void
    >::type push(Arg&& _val)
    {
        Any anyValue(std::forward<Arg>(_val));
        storage.push_back(std::move(anyValue));
    }
    /// <summary>
    /// ����������� ���������� ���������� � �����
    /// </summary>
    /// <returns>�����, ���������� ��������������� ������</returns>
    Buffer serialize() const;
    /// <summary>
    /// ������������� ������ �� ������ � ��������������� ���������
    /// </summary>
    /// <param name="_val">�����, ���������� ��������������� ������</param>
    /// <returns>������ �������� ���� Any, ��������������� �� ������</returns>
    static std::vector<Any> deserialize(const Buffer& _val);
    /// <summary>
    /// ���������� ������� ��������� � �������
    /// </summary>
    /// <returns>����������� ������ �� ������ �������� ���� Any, ���������� ��� ������</returns>
    const std::vector<Any>& getStorage() const;
private:
    /// <summary>
    /// ��������� ��� �������� ������ ��������� �����, �������������� ��� ������� ���� Any
    /// </summary>
    std::vector<Any> storage;
};

#endif
