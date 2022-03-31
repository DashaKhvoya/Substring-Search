# Поиск Подстроки #
## Условие ##
Необходимо реализовать эффективный алгоритм поиска по строке в очень большом текстовом файле. Файл загружается один раз, потом происходит большое количество запросов на поиск.

## Формат ответа ##
В качестве ответа на запрос печатается позиция первого вхождения строки в текст в виде числа в 0-индексации. Любые символы (включая символ переноса строки) считаются за отдельный символ.

### Пример ###
Данный текст:  

___Elisnore.  
A platform before the castle.  
Francisco at his post. Enter to him Bernardo. 
Who's there?  
Nay, answer me: stand, and unfold yourself.  
Long live the king!___
              
|  запрос  |  ответ   |
|----------|----------|
|A platform|    10    |
|    or    |    5     |

## Решение ##

Для решения данной задачи был использован суффиксный автомат. Наш класс суфиксного автомата будет хранить вектор структур, где каждая структура хранит информацию об очередном состоянии: 
```c
  struct state {
    size_t len;                               //длина строки, соответствующая состоянию
    long long link;                           //суффиксная ссылка
    std::unordered_map<char, long long> next; //список переходов в виде unordered map для достижения O(n) памяти
    long long first_pos;                      //окончание первого вхождения строки в текст
  };
```
Считается, что файл помещается в оперативную память. 

Решение задачи с помощью суффиксного автомата заключается в том, чтобы хранить в каждом состоянии позицию окончания первого вхождения, которую будем подсчитывать при построении автомата. Тогда для ответа на запрос нам просто понадобится найти запрос X в автомате за O(|length X|) и вывести его первое вхождение, вычтя из first_pos длину строки.

Для тестирования используется файл Hamlet.txt размером 163 КБ.
