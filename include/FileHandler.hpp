#pragma once
/*
    Структура json файла

    {
        "tasks": [
            {
                "id": <id>,
                "description": <description>,
                "task_status": <status>,
                "created_at": <time_created>
            },
                ],
        "next_id": <id>
    }

*/
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>

namespace tmtk
{
    class TaskManager;

    class FileHandler
    {
        std::filesystem::path dataDir;
        std::filesystem::path filePath;
        TaskManager &manager;

        std::filesystem::path getDataPath();

    public:
        explicit FileHandler(TaskManager &manager);
        void loadDataFromJSON();
    };

}