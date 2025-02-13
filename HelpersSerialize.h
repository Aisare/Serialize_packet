#ifndef HELPERSERIALIZEH
#define HELPERSERIALIZEH

#include "Helpers.h"
#include "IntegerType.h"
#include "FloatType.h"
#include "StringType.h"
#include "VectorType.h"

/// <summary>
/// Класс, предоставляющий методы для сериализации и десериализации данных,
/// а также для сравнения различных типов данных
/// </summary>
class HelpersSerialize
{
public:
    /// <summary>
    /// Десериализует данные по типу
    /// </summary>
    /// <param name="typeId">Идентификатор типа данных для десериализации</param>
    /// <param name="it">Итератор на начало данных в буфере, Этот итератор будет обновлен после чтения данных, указывая на новую позицию после извлечения</param>
    /// <param name="end">Итератор на конец данных в буфере</param>
    /// <returns>Возвращает десериализованный объект соответствующего типа</returns>
    static Helpers::ValueType deserializeByType(TypeId typeId, Buffer::const_iterator& it, Buffer::const_iterator end);
    /// <summary>
    /// Десериализует 64-битное целое число uint64_t из буфера
    /// </summary>
    /// <param name="it">Итератор на начало данных в буфере, Этот итератор будет обновлен после чтения данных, указывая на новую позицию после извлечения</param>
    /// <param name="end">Итератор на конец данных в буфере</param>
    /// <returns>Возвращает десериализованное 64-битное целое число</returns>
    static uint64_t deserializeUint64(Buffer::const_iterator& it, Buffer::const_iterator end);
    /// <summary>
    /// Проверяет размер данных в буфере
    /// Если размер данных меньше необходимого, выбрасывает исключение
    /// </summary>
    /// <param name="it">Итератор на начало данных в буфере</param>
    /// <param name="end">Итератор на конец данных в буфере</param>
    /// <param name="size">Необходимый размер данных</param>
    /// <param name="message">Сообщение для исключения в случае ошибки</param>
    static void checkBufferSize(Buffer::const_iterator it, Buffer::const_iterator end, size_t size,std::string message);
    /// <summary>
    /// Сериализует размер данных и записывает его в буфер
    /// </summary>
    /// <param name="buffer">Буфер, в который будет записан размер</param>
    /// <param name="size">Размер данных</param>
    static void serializeSize(Buffer& buffer, uint64_t size);
    /// <summary>
    /// Сравнивает два объекта типа ValueType
    /// </summary>
    /// <param name="lvar">Первый объект для сравнения</param>
    /// <param name="rvar">Второй объект для сравнения</param>
    /// <returns>True, если объекты равны, иначе false</returns>
    static bool compareVariants(const Helpers::ValueType& lvar, const Helpers::ValueType& rvar);
    /// <summary>
    /// Сравнивает два вектора, содержащих объекты типа ValueType
    /// </summary>
    /// <param name="lvec">Первый вектор для сравнения</param>
    /// <param name="rvec">Второй вектор для сравнения</param>
    /// <returns>True, если векторы равны, иначе false</returns>
    static bool compareVector(const std::vector<Helpers::ValueType>& lvec, const std::vector<Helpers::ValueType>& rvec);
    /// <summary>
    /// Сериализует примитивный тип данных и записывает его в буфер
    /// (uint64_t, double, std::string)
    /// </summary>
    /// <typeparam name="T">Тип данных для сериализации</typeparam>
    /// <param name="value">Значение для сериализации</param>
    /// <param name="buffer">Буфер, в который будут записаны данные</param>
    template <typename T>
    static void serializePrimitive(const T& value, Buffer& buffer)
    {
        if constexpr (std::is_same_v<T, std::string>)
        {
            uint64_t size = value.size();
            HelpersSerialize::serializeSize(buffer, size); 
            Helpers::appendToBuffer(buffer, value.data(), size); 
        }
        else
        {
            Helpers::appendToBuffer(buffer, &value, sizeof(T));
        }
    }
    /// <summary>
    /// Сериализует произвольный вариант std::variant в буфер
    /// </summary>
    /// <typeparam name="VariantType">Тип данных в std::variant</typeparam>
    /// <param name="var">Объект, который нужно сериализовать</param>
    /// <param name="buffer">Буфер, в который будут записаны данные</param>
    template <typename VariantType>
    static void serializeVariant(const VariantType& var, Buffer& buffer)
    {
        std::visit([&buffer](const auto& value)
            {
                serializePrimitive(value, buffer);
            }, var);
    }

    /// <summary>
    /// Десериализации значений типов
    /// </summary>
    /// <typeparam name="VariantType">Тип данных в std::variant</typeparam>
    /// <param name="it">Итератор на начало данных в буфере</param>
    /// <param name="end">Итератор на конец буфера</param>
    /// <param name="value">Переменная, в которую будут записаны десериализованные данные</param>
    /// <returns>Итератор, обновленный после чтения данных из буфера</returns>
    template <typename VariantType>
    static Buffer::const_iterator deserializeType(Buffer::const_iterator it, Buffer::const_iterator end, Helpers::GenEntity& value)
    {
        if constexpr (std::is_same_v<VariantType, uint64_t> || std::is_same_v<VariantType, double>)
        {
            HelpersSerialize::checkBufferSize(it, end, sizeof(uint64_t), "Buffer underflow while reading");
            Helpers::readFromBuffer(it, value, sizeof(uint64_t));
        }
        else if constexpr (std::is_same_v<VariantType, std::string>)
        {
            uint64_t size = HelpersSerialize::deserializeUint64(it, end);
            HelpersSerialize::checkBufferSize(it, end, size, "Buffer underflow while reading string data");
            Helpers::readFromBuffer(it, value, size);
        }
        return it;
    }
};
#endif
