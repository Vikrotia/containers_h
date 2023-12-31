# containers_h

## Введение

Проект `containers_h` представляет собой библиотеку, реализующую стандартные контейнерные классы языка C++ с добавлением нескольких дополнительных функций. В данной библиотеке реализованы контейнеры: `map` (словарь), `queue` (очередь) и `set` (множество), а также реализован дополнительный метод `insert_many`, который вставляет несколько элементов в контейнеры `map` и `set` одновременно.

## Реализация AVL-дерева

Для контейнеров `set` и `map` в данной библиотеке используется реализация AVL-дерева. AVL-дерево является сбалансированным двоичным деревом поиска, что обеспечивает эффективное выполнение операций вставки, удаления и поиска элементов. Это позволяет достичь высокой производительности и предсказуемости времени выполнения операций на этих контейнерах.


## Использование библиотеки

### Включение библиотеки в проект

Для использования библиотеки `containers_h` в вашем проекте выполните следующие шаги:

1. Скопируйте файлы в директорию вашего проекта.

2. Включите любую библиотеку в вашем исходном коде:

   ```cpp
   #include "s21_map.h"
   ```

### Создание объектов контейнеров

Для создания объектов контейнеров воспользуйтесь следующим конструктором:

- Конструктор по умолчанию:

   ```cpp
   s21::map<Key, Value> myMap;
   s21::queue<int> myQueue;
   s21::set<double> mySet;
   ```

### Доступ к элементам контейнера

Вы можете получить доступ к элементам контейнера с помощью итераторов. Пример:

```cpp
s21::map<Key, Value> myMap;
// Заполнение myMap элементами

for (auto it = myMap.begin(); it != myMap.end(); ++it) {
    // Доступ к элементу через итератор it
    auto key = it->first;
    auto value = it->second;
    // Делайте что-то с key и value
}
```

### Методы проверки контейнера

Методы, позволяющие проверить состояние контейнера:

- `empty()`: Проверка на пустоту контейнера.
- `size()`: Получение количества элементов в контейнере.

Пример:

```cpp
s21::queue<int> myQueue;
bool isEmpty = myQueue.empty();
size_t size = myQueue.size();
```

### Методы изменения контейнера

Методы для добавления, удаления и изменения элементов в контейнере:

- `insert(key, value)`: Добавление элемента в контейнер `map`.
- `erase(key)`: Удаление элемента по ключу из контейнера `map` или `set`.
- `push(value)`: Добавление элемента в конец контейнера `queue`.
- `pop()`: Удаление элемента из начала контейнера `queue`.
- `insert_many(args...)`: Добавление нескольких элементов в контейнеры `map` и `set` одновременно.

Примеры:

```cpp
s21::map<int, std::string> myMap;
myMap.insert(1, "One");
myMap.erase(2);

s21::queue<int> myQueue;
myQueue.push(42);
myQueue.pop();

s21::set<double> mySet;
mySet.insert(3.14);
mySet.erase(2.71);

// Добавление нескольких элементов
auto result = myMap.insert_many({{1, "One"}, {2, "Two"}, {3, "Three"}});
```

## Сборка проекта

Для сборки проекта, включая тесты, используйте прилагаемый Makefile. Выполните следующие команды:

1. Сборка проекта:

   ```bash
   make
   ```

2. Запуск тестов:

   ```bash
   make test
   ```

## Автор

- Виктория (s21_utheryde)

## Благодарность

Благодарю себя и моих друзей
