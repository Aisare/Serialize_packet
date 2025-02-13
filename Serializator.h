#ifndef SERIALIZATORH
#define SERIALIZATORH

#include "Any.h"
/// <summary>
/// Класс Serializator отвечает за сериализацию и десериализацию различных типов данных, а также хранение этих данных в контейнере 
/// Он может сериализовать объекты типов IntegerType, FloatType, StringType, VectorType и Any, обеспечивая их добавление в контейнер
/// </summary>
class Serializator
{
public:
    /// <summary>
    /// Добавляет элемент в контейнер
    /// Элементы могут быть одного из типов: IntegerType, FloatType, StringType,VectorType или Any
    /// </summary>
    /// <typeparam name="Arg">Тип передаваемого значения</typeparam>
    /// <param name="_val">Элемент, который будет добавлен в контейнер</param>
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
    /// Сериализует содержимое контейнера в буфер
    /// </summary>
    /// <returns>Буфер, содержащий сериализованные данные</returns>
    Buffer serialize() const;
    /// <summary>
    /// Десериализует данные из буфера и восстанавливает контейнер
    /// </summary>
    /// <param name="_val">Буфер, содержащий сериализованные данные</param>
    /// <returns>Вектор объектов типа Any, восстановленных из буфера</returns>
    static std::vector<Any> deserialize(const Buffer& _val);
    /// <summary>
    /// Возвращает текущий контейнер с данными
    /// </summary>
    /// <returns>Константная ссылка на вектор объектов типа Any, содержащих все данные</returns>
    const std::vector<Any>& getStorage() const;
private:
    /// <summary>
    /// Контейнер для хранения данных различных типов, представленных как объекты типа Any
    /// </summary>
    std::vector<Any> storage;
};

#endif
