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

            std::string time = task.get_created_at_str().substr(11, 8);
            std::cout << " 🕐 " << time;

            if (task.is_done())
            {
                std::cout << " ✅";
            }
            std::cout << "\n";
        }
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    }
}