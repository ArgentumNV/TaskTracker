#pragma once

#include <vector>
#include <string>

#include "Task.hpp"

namespace tmtk
{
    class TaskManager
    {
        std::vector<Task> tasks;

    public:
        TaskManager();

        void addTask(const std::string &desc);

        void list() const;
        void list_pending() const;

        void mark_task_done(unsigned int id);
        bool deleteTask(unsigned int id);
    };
}