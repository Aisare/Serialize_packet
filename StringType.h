#ifndef STRINGTYPEH
#define STRINGTYPEH

#include "Helpers.h"
#include "HelpersSerialize.h"

class StringType
{
public:
    /// <summary>
    /// Конструктор из C-строки (const char*)
    /// </summary>
    StringType(const char* val) : value(std::string(val)) {}
    /// <summary>
    /// Конструктор из char (создает строку из одного символа)
    /// </summary>
    StringType(char ch) : value(std::string(1, ch)) {}
    /// <summary>
    /// Конструктор по умолчанию, что бы поведение совпадало с std::string
    /// </summary>
    StringType() : value("") {}
    /// <summary>
    /// Конструктор с параметром
    /// </summary>
    /// <param name="val">Строковое значение для инициализации</param>
    StringType(std::string val) : value(std::move(val)) {}
    /// <summary>
    /// Оператор присваивания из const char*
    /// </summary>
    StringType& operator=(const char* val) 
    {
        value = std::string(val);
        return *this;
    }
    /// <summary>
    /// Оператор присваивания из char
    /// </summary>
    StringType& operator=(char ch) 
    {
        value = std::string(1, ch);
        return *this;
    }
    /// <summary>
    /// Оператор присваивания из std::string
    /// </summary>
    StringType& operator=(const std::string& val) 
    {
        value = val;
        return *this;
    }
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
    /// Хранимое строковое значение
    /// </summary>
    Helpers::GenEntity value;
    /// <summary>
    /// Этот класс является другом для класса HelpersSerialize
    /// </summary>
    friend class HelpersSerialize;
};
#endif

