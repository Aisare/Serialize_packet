#ifndef VECTORTYPEH
#define VECTORTYPEH

#include "Helpers.h"
#include "IntegerType.h"
#include "FloatType.h"
#include "StringType.h"
#include "HelpersSerialize.h"
/// <summary>
/// VectorType - Класс, представляющий вектор, который может содержать элементы различных типов
/// Вектор может хранить значения типов IntegerType, FloatType, StringType и другие вектора
/// </summary>
class VectorType
{
public:
    /// <summary>
    /// Конструктор по умолчанию
    /// Создаёт пустой вектор
    /// </summary>
    VectorType() = default;
    /// <summary>
    /// Конструктор, который принимает произвольное количество аргументов и добавляет их в вектор
    /// </summary>
    /// <typeparam name="...Args">Типы элементов, которые будут добавлены в вектор</typeparam>
    /// <param name="...args">Элементы, которые будут добавлены в вектор как по значению, так и по ссылке</param>
    template<typename... Args>
    VectorType(Args&& ...args)
    {
        (push_back(std::forward<Args>(args)), ...);
    }
    /// <summary>
    /// Добавляет элемент в вектор
    /// Тип элемента должен быть одним из: IntegerType, FloatType, StringType или VectorType, другие типы добавлены не будут
    /// </summary>
    /// <typeparam name="Args">Тип передаваемого элемента</typeparam>
    /// <param name="_val">Элемент, который будет добавлен в вектор</param>
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
    /// Коллекция элементов, каждый из которых может быть одним из типов: IntegerType, FloatType, StringType или VectorType
    /// Использует std::variant для хранения элементов разных типов, при этом все элементы хранятся в одном контейнере
    /// Этот контейнер поддерживает добавление, удаление и доступ к элементам, при этом гарантируется, что каждый элемент будет одного из заранее определённых типов
    /// </summary>
    std::vector<Helpers::ValueType> value;
    /// <summary>
    /// Этот класс является другом для класса HelpersSerialize
    /// </summary>
    friend class HelpersSerialize;
};

#endif

