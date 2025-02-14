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

## License

This project is licensed under the Business Source License 1.1 (BSL-1.1) - see the [LICENSE](https://github.com/Aisare/Serialize_packet/blob/main/LICENSE) file for details.

You may use, modify, and distribute this software for non-commercial purposes. Commercial use of this software is prohibited without purchasing a commercial license.

Effective from 2035, this software will be released under the open-source license GNU General Public License version 3 (GPL-3.0).
