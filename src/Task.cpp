#include "../include/Task.hpp"

namespace tmtk
{
    std::vector<std::string> split_command(const std::string &input)
    {
        std::vector<std::string> parts;

        // Создаем поток из строки
        std::istringstream iss{input};
        std::string part;

        while (iss >> part)
        {
            parts.push_back(part);
        }

        return parts;
    }

    unsigned int Task::next_id = 1;

    unsigned int Task::generate_id()
    {
        int new_id = next_id++;
        return new_id;
    }

    Task::Task(std::string desc,
               std::chrono::system_clock::time_point time_created)
        : id{generate_id()}, description{desc},
          status{task_status::Pending}, created_at{time_created}
    {
    }

    unsigned int Task::get_id() const { return id; }
    const std::string &Task::get_description() const { return description; }
    const Task::task_status Task::get_status() const { return status; }

    std::string Task::get_created_at_str() const
    {
        const auto time = std::chrono::system_clock::to_time_t(created_at);
        std::tm *local = std::localtime(&time);
        std::ostringstream oss;
        oss << std::put_time(local, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    void Task::mark_done() { status = task_status::Done; }
    bool Task::is_done() const { return status == task_status::Done; }
}