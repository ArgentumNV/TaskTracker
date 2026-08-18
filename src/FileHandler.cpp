#include "../include/FileHandler.hpp"
#include "../include/TaskManager.hpp"

namespace tmtk
{
    std::filesystem::path FileHandler::getDataPath()
    {
        try
        {
            std::filesystem::path dataDir = std::filesystem::read_symlink("/proc/self/exe")
                                                .parent_path()
                                                .parent_path() /
                                            "data";

            if (!std::filesystem::exists(dataDir))
            {
                std::filesystem::create_directories(dataDir);
            }

            this->dataDir = dataDir;
            this->filePath = dataDir / "tasks.json";

            if (!std::filesystem::exists(this->filePath))
            {
                std::ofstream file(this->filePath);
            }

            return dataDir;
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cout << "Неудалось создать файл\n";
            throw;
        }
    }

    FileHandler::FileHandler(TaskManager &manager)
        : manager(manager)
    {
        getDataPath();
    }
}