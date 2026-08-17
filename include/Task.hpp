#pragma once
/*
    Структура-класс для описания одной задачи

*/

#include "FileHadler.hpp"

#include <string>
#include <chrono>
#include <vector>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>

namespace tmtk
{
    std::vector<std::string> split_command(const std::string &input);

    class Task
    {
        enum class task_status
        {
            Pending = 0, // Задача еще не сделана
            Done = 1     // Задача сделана
        };

        unsigned int id;
        std::string description;
        task_status status;
        std::chrono::system_clock::time_point created_at;

        static unsigned int next_id;
        static unsigned int generate_id();

    public:
        Task(std::string desc,
             std::chrono::system_clock::time_point time_created);

        unsigned int get_id() const;
        const std::string &get_description() const;
        const task_status get_status() const;

        std::string get_created_at_str() const;
        void mark_done();
        bool is_done() const;
    };
}