/*
       ДОМАШНЕЕ ЗАДАНИЕ
       Проект телефонная книга
       Поиск по имени: добавить итоговую инф (найдено Х записей)
       ** Реализовать частичный поиск по подстроке petr? находит Petrovich Petrenko
       Реализовать поиск по номеру телефона
   */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "colors.h"
using namespace std;

size_t N = 10;     // максимальное кол-во ячеек-записей
char*** phonebook; // указатель на ресурс тел книги

void print_phonebook()
{
    cout << " No\tFIO\t\tTel\n";   // шапка таблицы
    for (size_t i = 0; i < N; i++)
    {
        cout << (i + 1) << '\t';  // номер порядковый
        if (phonebook[i][0] == NULL)  // нет данных ФИО
        {
            cout << "--\t\t";
        }
        else  // есть данные ФИО
        {
            cout << phonebook[i][0] << '\t';
        }
        if (phonebook[i][1] == NULL)  // нет данных тел
        {
            cout << "--";
        }
        else  // есть данные тел
        {
            cout << phonebook[i][1];
        }
        cout << "\n";
    }
}

bool add_phone(const char* name, const char* phone)
{
    if (name == NULL || phone == NULL)
    {
        cout << colors::RED_BRIGHT << "NULL-argument in add_phone()"
            << colors::RESET << "\n";
        return false;
    }
    size_t i = 0;
    while (i < N && phonebook[i][0] != NULL)
    {
        ++i;
    }

    if (i == N)  // i == N - книга заполнена (нет пустых), иначе работаем дальше
    {
        return false;
    }
    // phonebook[0][0] = name; // так нельзя
    // phonebook[0][0] = (char*) name; // так нельзя псевдоним - второй указатель на те же данные
    // правильно копировать, выделить новую память и перенести данные

    phonebook[i][0] = new char[strlen(name) + 1];  // размер ФИО + 1
    strcpy(phonebook[i][0], name);  // копируем ФИО

    phonebook[i][1] = new char[strlen(phone) + 1];  // размер телефона + 1
    strcpy(phonebook[i][1], phone);  // копируем телефон

    return true;
}

void fill_demo()  // демонстрационная версия
{
    add_phone("Petrovich", "223322");
    add_phone("Pavlovna", "322223");
}

bool input_phone()
{
    const size_t BUF_SIZE = 100;
    char* name = new char[BUF_SIZE];  // константный указатель
    char* phone = new char[BUF_SIZE];
    cout << "Name: ";
    cin.getline(name, BUF_SIZE);
    cout << "Phone: ";
    cin >> phone;

    bool res = add_phone(name, phone);

    delete[] name;
    delete[] phone;

    return res;
}

void search_by_name()
{
    const size_t BUF_SIZE = 100;
    char* name = new char[BUF_SIZE];  // константный указатель
    cout << "Name: ";
    cin.getline(name, BUF_SIZE);

    for (size_t i = 0; i < N; i++)
    {
        if (phonebook[i][0] != NULL)
        {
            if (_stricmp(phonebook[i][0], name) == 0) // если совпадение найдено
            {
                cout << (i + 1) << " " << phonebook[i][0] << " "
                    << phonebook[i][1] << "\n";
            }
        }
    }
    delete[] name;
}
int main()
{
    phonebook = new char** [N];  // первый уровень вложенности ячейки [ФИО][тлф]
    for (size_t i = 0; i < N; i++)
    {
        phonebook[i] = new char* [2];  // второй уровень сами ячейки [ФИО][тлф]
        phonebook[i][0] = NULL;   // признак свободной ячейки
        phonebook[i][1] = NULL;   // признак свободной ячейки
    }
    cout << colors::BLUE_BOLD_BRIGHT
        << "Phonebook!"
        << colors::PURPLE_BOLD_BRIGHT
        << " v0.3 \n"
        << colors::RESET; // RESET возвращает в исходное состояние

    fill_demo();

    cout << "1. Show all phones\n"
         << "2. Add phone\n"
         << "0. Exit\n";

    char user_choice[10]; // исп для того, чтобы исключить системные ошибки
    //int userChoice;    // приводит к ошибкам
    //cin >> userChoice; // если вводится не число
    do
    {
        cout << "1. Show all phones\n"
             << "2. Add phone\n"
             << "3. Search by name\n"
             << "0. Exit\n";

        cout << "Make a choice: ";

        if (cin.peek() == '\n') cin.get();  // если от предыдущих итераций остался символ \n, то стираем его

        cin.getline(user_choice, 10); // чтобы исключить системные ошибки
        if (strlen(user_choice) != 1)
        {
            cout << colors::PURPLE << "Incorrect choice (only 1 digit)\n" << colors::RESET;
            continue;
        }
        switch (user_choice[0])
        {
            case '1': print_phonebook(); break;
            case '2':
                if (input_phone())
                {
                    cout << colors::GREEN << "Phone added\n" << colors::RESET;
                }
                else
                {
                    cout << colors::YELLOW << "Phone adding error" << colors::RESET;
                }
                break;
            case '3': search_by_name(); break;
            case '0': break;
            default:
            cout << colors::PURPLE << "Incorrect choice (choose from menu)\n" << colors::RESET;
            continue;
        }
    } while (user_choice[0] != '0');

    return 0;
}
/*
    Многомерные массивы - массивы строк

    Проект: телефонный справочник
    Описание: программа должна хранить данные об имени
    и номере телефона. Предоставляется интерфейс для
    поиска и добавления записей.
    Задача: сопоставить информацию о телефоне и имени,
    собирая массив записей.
    [   [ФИО][тлф]
        [ФИО][тлф]
        [ФИО][тлф]
        .....(10)
        [ФИО][тлф]
     ]
    phonebook[10] {  [Petrovich] [223322]}
    phonebook[10][0] - ФИО (char[] "Petrovich") phonebook[10][0][2] - 't'
    phonebook[10][1] - тлф (char[] "223322")

*/