#ifndef HELPERSH
#define HELPERSH
#include <iostream>
#include <vector>
#include <fstream>
#include <type_traits>
#include <variant>
#include <string>

/// <summary>
/// Тип Id представляет собой алиас для типа uint64_t
/// </summary>
using Id = uint64_t;
/// <summary>
/// Тип Buffer представляет собой контейнер std::vector<std::byte>, который используется для хранения бинарных данных
/// </summary>
using Buffer = std::vector<std::byte>;
/// <summary>
/// Перечисление TypeId определяет типы данных, которые могут быть сериализованы/десериализованы
/// Каждый элемент перечисления соответствует конкретному типу данных:
/// Uint - целочисленный тип
/// Float - тип с плавающей точкой
/// String - строковый тип
/// Vector - тип, представляющий вектор
/// </summary>
enum class TypeId : Id 
{
    Uint,
    Float,
    String,
    Vector
};

/// <summary>
/// Предварительное объявление классов
/// </summary>
class IntegerType;
class FloatType;
class StringType;
class VectorType;

/// <summary>
/// Helpers - Класс предоставляет вспомогательные функции для работы с буферами
/// </summary>
class Helpers
{
public:
    /// <summary>
    /// Обобщённый тип данных, для переменных которые могут быть
    /// IntegerType, FloatType, StringType или VectorType
    /// </summary>
    using ValueType = std::variant<IntegerType, FloatType, StringType, VectorType>;
    /// <summary>
    /// Обобщённый тип данных, для переменных которые могут быть
    /// uint64_t, double или std::string
    /// </summary>
    using GenEntity = std::variant<uint64_t, double, std::string>;
    /// <summary>
    /// Добавляет данные в буфер
    /// </summary>
    /// <param name="buffer">Буфер, в который добавляются данные</param>
    /// <param name="data">Данные, которые нужно добавить в буфер</param>
    /// <param name="size">Размер данных, которые будут добавлены в буфер</param>
    static void appendToBuffer(Buffer& buffer, const void* data, size_t size);
    /// <summary>
    /// Извлекает данные из буфера, начиная с текущей позиции итератора
    /// </summary>
    /// <param name="it">Итератор на текущую позицию в буфере, который будет обновлен после чтения данных</param>
    /// <param name="data">Место назначения для данных, которые будут прочитаны из буфера</param>
    /// <param name="size">Размер данных, которые будут прочитаны</param>
    static void readFromBuffer(Buffer::const_iterator& it, Helpers::GenEntity& value, size_t size);
    /// <summary>
    /// Извлекает данные из буфера, начиная с текущей позиции итератора
    /// </summary>
    /// <param name="it">Итератор на текущую позицию в буфере, который будет обновлен после чтения данных</param>
    /// <param name="value">Место назначения для данных, которые будут прочитаны из буфера</param>
    /// <param name="size">Размер данных, которые будут прочитаны</param>
    static void readFromBuffer(Buffer::const_iterator& it, void* value, size_t size);
    /// <summary>
    /// Функция для получения типа TypeId из переданного variant типа
    /// </summary>
    /// <typeparam name="VariantType">Тип variant, из которого нужно извлечь TypeId</typeparam>
    /// <param name="var">Variant значение, тип которого необходимо определить</param>
    /// <returns>Тип данных TypeId</returns>
    template <typename VariantType>
    static TypeId getTypeIdFromVariant(const VariantType& var)
    {
        return std::visit([](const auto& v) -> TypeId
            {
                using T = std::decay_t<decltype(v)>;
                if constexpr (std::is_same_v<T, IntegerType>)
                {
                    return TypeId::Uint;
                }
                else if constexpr (std::is_same_v<T, FloatType>)
                {
                    return TypeId::Float;
                }
                else if constexpr (std::is_same_v<T, StringType>)
                {
                    return TypeId::String;
                }
                else if constexpr (std::is_same_v<T, VectorType>)
                {
                    return TypeId::Vector;
                }
            }, var);
    }
};


#endif // HELPERS



