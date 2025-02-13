#ifndef ANYH
#define ANYH

#include "Helpers.h"
#include "IntegerType.h"
#include "FloatType.h"
#include "StringType.h"
#include "VectorType.h"
/// <summary>
/// Any - Класс, который может содержать элементы различных типов
/// Может хранить значение типов IntegerType, FloatType, StringType и VectorType
/// </summary>
class Any
{
public:
    /// <summary>
    /// Конструктор по умолчанию
    /// </summary>
    Any() = default;
    /// <summary>
    /// Конструктор, который инициализирует объект типа Any значением одного из поддерживаемых типов:
    /// IntegerType, FloatType, StringType, VectorType
    /// </summary>
    /// <typeparam name="Args">Тип передаваемого значения</typeparam>
    /// <param name="val">Значение, которое будет сохранено</param>
    template<typename Args, typename = std::enable_if_t<std::is_same_v<std::decay_t<Args>, IntegerType> ||
                                                        std::is_same_v<std::decay_t<Args>, FloatType> ||
                                                        std::is_same_v<std::decay_t<Args>, StringType> ||
                                                        std::is_same_v<std::decay_t<Args>, VectorType>>>
    Any(Args&& val) : storage(std::forward<Args>(val)) {}
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
    Buffer::const_iterator deserialize(Buffer::const_iterator _begin, Buffer::const_iterator _end);
    /// <summary>
    /// Возвращает идентификатор типа данных, хранимых в объекте
    /// </summary>
    /// <returns>Возвращает TypeId, который соответствует типу данных, хранимым в объекте </returns>
    TypeId getPayloadTypeId() const;
    /// <summary>
    /// Извлекает значение типа Type из объекта
    /// Если тип не совпадает с ожидаемым, выбрасывает исключение std::bad_variant_access
    /// </summary>
    /// <typeparam name="Type">Тип, который необходимо извлечь из объекта</typeparam>
    /// <returns>Ссылка на значение типа Type, хранимое в объекте</returns>
    /// <exception cref="std::runtime_error">Бросается, если тип данных в объекте не соответствует ожидаемому</exception>
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
    /// Извлекает значение, соответствующее конкретному TypeId из объекта
    /// Если переданный TypeId не совпадает с текущим типом данных в объекте, выбрасывает исключение
    /// </summary>
    /// <typeparam name="kId">Идентификатор типа, который необходимо извлечь из объекта</typeparam>
    /// <returns>Ссылка на значение, соответствующее типу, заданному kId</returns>
    /// <exception cref="std::runtime_error">Бросается, если kId не соответствует типу данных в объекте</exception>
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
    /// Оператор сравнения двух объектов Any
    /// </summary>
    /// <param name="other">Объект для сравнения</param>
    /// <returns>True, если значения равны, иначе false</returns>
    bool operator==(const Any& other) const;
private:
    /// <summary>
    /// Хранит данные различных типов, таких как IntegerType, FloatType, StringType, или VectorType, в виде обертки с использованием std::variant
    /// Это позволяет хранить разные типы в одном объекте, при этом гарантируя, что в любой момент времени будет доступен только один тип
    /// </summary>
    Helpers::ValueType storage;
};
#endif