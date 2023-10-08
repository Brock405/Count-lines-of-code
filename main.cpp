#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <filesystem>
namespace fs = std::__1::__fs::filesystem;

static std::string projectsDirectory;
static std::vector<std::string> filesInProjectsDirectory = {};

void getAllFilesInADirectoryTree(std::string directory)
{
    for (const auto &entry : fs::directory_iterator(directory))
    {
        if (fs::is_regular_file(entry.path()))
        {
            filesInProjectsDirectory.insert(filesInProjectsDirectory.begin(), entry.path());
        }
        else if (fs::is_directory(entry.path()))
            getAllFilesInADirectoryTree(entry.path());
        else
            return;
    }
}

int main()
{
    int totalNumOfLines = 0;
    std::cout << "Enter the projects folder path: ";
    std::getline(std::cin, projectsDirectory);
    std::cout << "\n";

    getAllFilesInADirectoryTree(projectsDirectory);
    for (int file = 0; file < filesInProjectsDirectory.size(); file++)
    {
        std::ifstream currentFile(filesInProjectsDirectory[file].c_str());

        int numLines = std::count(std::istreambuf_iterator<char>(currentFile),
                                  std::istreambuf_iterator<char>(), '\n');
        std::string fileD = filesInProjectsDirectory[file].substr(projectsDirectory.length() + 1);
        std::cout << numLines << " lines - " << fileD << std::endl;
        totalNumOfLines += numLines;
    }

    std::cout << "\n" << "---------------------------------------------------------------------" << std::endl;
    std::cout << "\n" << "Total Number of lines in project: " << totalNumOfLines << "\n" << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
}
