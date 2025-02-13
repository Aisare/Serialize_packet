#ifndef INTEGERTYPEH
#define INTEGERTYPEH

#include "Helpers.h"
#include "HelpersSerialize.h"
/// <summary>
/// IntegerType - класс для целочисленных значений
/// </summary>
class IntegerType
{
public:
    /// <summary>
    /// Конструктор по умолчанию, что бы поведение совпадало с uint64_t
    /// </summary>
    IntegerType() : value(uint64_t(0)) {}
    /// <summary>
    /// Конструктор с параметром
    /// </summary>
    /// <param name="val">Числовое значение для инициализации</param>
    IntegerType(uint64_t val) : value(val) {}
    /// <summary>
    /// Сериализует объект и добавляет его бинарное представление в буфер
    /// </summary>
    /// <param name="buffer">Буфер, в который записываются сериализованные данные</param>
    void serialize(Buffer& buffer) const;
    /// <summary>
    /// Десериализует объект из буфера
    /// </summary>
    /// <param name="it">Итератор на начало данных в буфере</param>
    /// <param name="end">Итератор на конец буфера</param>
    /// <returns>Итератор на позицию после прочитанных данных</returns>
    Buffer::const_iterator deserialize(Buffer::const_iterator it, Buffer::const_iterator end);
private:
    /// <summary>
    /// Хранимое целочисленное значение
    /// </summary>
    Helpers::GenEntity value;
    /// <summary>
    /// Этот класс является другом для класса HelpersSerialize
    /// </summary>
    friend class HelpersSerialize;
};
#endif


