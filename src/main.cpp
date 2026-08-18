#include "../include/Task.hpp"
#include "../include/TaskManager.hpp"
#include "../include/FileHandler.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
/*
    Список команд:

    Команда add [текст задачи]

        Что делает: Создает новую задачу с переданным текстом.

        Требования: Присваивает задаче уникальный числовой ID (автоинкремент, начинается с 1). Статус задачи по умолчанию — Pending (не выполнена). Устанавливает текущую дату создания.

        Вывод в консоль: Task added successfully with ID: 5

    Команда list

        Что делает: Показывает все задачи в виде таблицы (или списка) с колонками: ID, Description, Status, Created At. Сортировка: по ID или по статусу (сначала Pending, потом Done).

        Вывод в консоль: Читаемая таблица.

    Команда list pending

        Что делает: Показывает только те задачи, у которых статус Pending.

    Команда done [ID]

        Что делает: Отмечает задачу с указанным ID как выполненную (меняет статус на Done).

        Обработка ошибок: Если задача с таким ID не найдена — вывести сообщение об ошибке и не падать.

    Команда delete [ID]

        Что делает: Полностью удаляет задачу с указанным ID из списка.

    Команда exit

        Что делает: Завершает цикл программы, сохраняя данные в файл (если изменения были).

*/

int main(void)
{
    std::string input{};
    std::cout << "Welcome to my TaskManager" << '\n';
    tmtk::TaskManager manager{};
    // загрузка из json в manager

    tmtk::FileHandler filehandler{manager};

    while (true)
    {
        // Приглашение
        std::cout << "TaMa>>> " << std::flush;

        // Чтение ввода
        if (!std::getline(std::cin, input))
        {
            std::cout << "\nВыход...\n";
            break;
        }
        if (input.empty())
            continue;

        std::vector<std::string> parts{tmtk::split_command(input)};

        std::string command{parts[0]};

        if (command == "exit")
            break;

        else if (command == "add")
        {
            if (parts.size() < 2)
            {
                std::cout << "❌ Укажите описание: add <описание>\n";
                continue;
            }

            std::string description;
            for (size_t i = 1; i < parts.size(); ++i)
            {
                if (!description.empty())
                    description += " ";
                description += parts[i];
            }

            manager.addTask(description);
        }
        else if (command == "list")
        {
            if (parts.size() == 2 && parts[1] == "pending")
            {
                manager.list_pending();
            }
            else if (parts.size() == 2 && parts[1] != "pending")
            {
                std::cout << "Unknown command: Please try again" << '\n';
            }
            else if (parts.size() == 1)
            {
                manager.list();
            }
        }
        else if (command == "done")
        {
            if (parts.size() == 1)
            {
                std::cout << "Введите ID задачи\n";
            }
            else
            {
                unsigned long tmp{};
                try
                {
                    tmp = std::stoul(parts[1]);
                }
                catch (const std::invalid_argument &e)
                {
                    std::cout << "Ошибка: строка не является числом" << '\n';
                    continue;
                }
                catch (const std::out_of_range &e)
                {
                    std::cout << "Ошибка: строка не является числом" << '\n';
                    continue;
                }

                unsigned int id{static_cast<unsigned int>(tmp)};

                manager.mark_task_done(id);
            }
        }
        else if (command == "delete")
        {
            if (parts.size() == 1)
            {
                std::cout << "Введите ID задачи\n";
            }
            else
            {
                unsigned long tmp{};
                try
                {
                    tmp = std::stoul(parts[1]);
                }
                catch (const std::invalid_argument &e)
                {
                    std::cout << "Ошибка: строка не является числом" << '\n';
                    continue;
                }
                catch (const std::out_of_range &e)
                {
                    std::cout << "Ошибка: строка не является числом" << '\n';
                    continue;
                }
                unsigned int id{static_cast<unsigned int>(tmp)};
                if (manager.deleteTask(id))
                {
                    std::cout << "Задача с ID: " << id << " успешно удалена.\n";
                }
                else
                {
                    std::cout << "Задача с ID: " << id << " не удалена.\n";
                }
            }
        }
        else
        {
            std::cout << "Unknown command: Please try again" << '\n';
        }
    }

    return 0;
}