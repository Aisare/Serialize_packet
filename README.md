# Serialize_packet
1) Стандарт - c++17.
2) Без виртуальных функций.
3) Без наследования.
4) Без обьектов в кучи и умных указателей.
5) Обобщенные типы данных:
- using GenEntity = std::variant<uint64_t, double, std::string>; для классов IntegerType, FloatType, StringType.
- using ValueType = std::variant<IntegerType, FloatType, StringType, VectorType>; для классов VectorType и Any
6) Два хелпер класса:
- class Helpers; Класс предоставляет вспомогательные функции для работы с буферами.
- class HelpersSerialize; Класс, предоставляющий методы для сериализации и десериализации данных, а также для сравнения различных типов данных.
