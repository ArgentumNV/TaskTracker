#include "../include/TaskManager.hpp"
#include "../include/Task.hpp"
namespace tmtk
{
    TaskManager::TaskManager() : tasks{}
    {
    }

    void TaskManager::addTask(const std::string &desc)
    {
        tasks.emplace_back(desc, std::chrono::system_clock::now());
        std::cout << "✅ Задача добавлена (ID: " << tasks.back().get_id() << ")\n";
    }

    void TaskManager::list() const
    {
        if (tasks.empty())
        {
            std::cout << "\n📭 Нет задач\n";
            return;
        }

        std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        std::cout << "  📋 ЗАДАЧИ (" << tasks.size() << ")\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";

        for (const auto &task : tasks)
        {
            std::string icon = (task.is_done()) ? "✅" : "⬜";
            std::cout << "  " << icon << " #" << std::setw(3) << task.get_id() << " ";

            std::string desc = task.get_description();
            if (desc.length() > 50)
            {
                desc = desc.substr(0, 47) + "...";
            }
            std::cout << std::left << std::setw(50) << desc;

            // std::string time = task.get_created_at_str().substr(11, 8);
            std::string time = task.get_created_at_str();
            std::cout << " 🕐 " << time;

            if (task.is_done())
            {
                std::cout << " ✅";
            }
            std::cout << "\n";
        }
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    }

    void TaskManager::list_pending() const
    {
        if (tasks.empty())
        {
            std::cout << "\n📭 Нет задач\n";
            return;
        }

        // Проверяем наличие ожидающих задач
        bool has_pending = false;
        for (const auto &task : tasks)
        {
            if (!task.is_done())
            {
                has_pending = true;
                break;
            }
        }

        if (!has_pending)
        {
            std::cout << "\n╔═══════════════════════════════════════════════════════════════╗\n";
            std::cout << "║                    🎉 ВСЕ ЗАДАЧИ ВЫПОЛНЕНЫ!                   ║\n";
            std::cout << "╚═══════════════════════════════════════════════════════════════╝\n";
            return;
        }

        // Подсчет статистики
        size_t total = tasks.size();
        size_t pending = 0;
        size_t done = 0;
        for (const auto &task : tasks)
        {
            if (task.is_done())
                done++;
            else
                pending++;
        }

        // Заголовок
        std::cout << "\n╔════════════════════════════════════════════════════════════════════════════╗\n";
        std::cout << "║                      ⬜ ОЖИДАЮЩИЕ ЗАДАЧИ (" << pending << ")                               ║\n";
        std::cout << "╠════════════════════════════════════════════════════════════════════════════╣\n";
        std::cout << "║  Всего: " << std::setw(3) << total
                  << "  |  ⬜ Ожидают: " << std::setw(3) << pending
                  << "  |  ✅ Выполнены: " << std::setw(3) << done << "                      ║\n";
        std::cout << "╚════════════════════════════════════════════════════════════════════════════╝\n";

        // Таблица задач
        if (pending > 0)
        {
            std::cout << "\n┌──────┬──────────────────────────────────────────────────┬─────────────────────┐\n";
            std::cout << "│  ID  │               Описание задачи                    │     Создана         │\n";
            std::cout << "├──────┼──────────────────────────────────────────────────┼─────────────────────┤\n";

            for (const auto &task : tasks)
            {
                if (!task.is_done())
                { // Только Pending
                    // Обрезаем описание если слишком длинное
                    std::string desc = task.get_description();
                    if (desc.length() > 48)
                    {
                        desc = desc.substr(0, 45) + "...";
                    }

                    std::cout << "│ " << std::setw(4) << task.get_id() << " │ "
                              << std::left << std::setw(48) << desc << " │ "
                              << std::setw(19) << task.get_created_at_str() << " │\n";
                }
            }

            std::cout << "└──────┴──────────────────────────────────────────────────┴─────────────────────┘\n";
        }

        std::cout << "\n💡 Чтобы выполнить задачу: done <ID>\n";
    }

    void TaskManager::mark_task_done(unsigned int id)
    {
        // ищем задачу с id
        for (auto &task : tasks)
        {
            if (task.get_id() == id)
            {
                task.mark_done();
                std::cout << "Задача с ID: " << task.get_id() << " " << task.get_description() << " сделана\n";
                return;
            }
        }
        // задача с таким id не найдена
        std::cout << "Задача с ID: " << id << " не найдена.\n";
    }

    bool TaskManager::deleteTask(unsigned int id)
    {
        for (auto it = tasks.begin(); it != tasks.end(); ++it)
        {
            if (it->get_id() == id)
            {
                tasks.erase(it);
                return true;
            }
        }
        return false; // Задача с таким ID не найдена
    }

}