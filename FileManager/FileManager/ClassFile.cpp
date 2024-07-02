#include <iostream>
#include <filesystem>
#include <fstream>
using namespace std;
using namespace std::filesystem;
#include "ClassComponent.h"
#include "ClassFile.h"


File::File(const string& fileDirectoryPath)
{
    if (!is_directory(path{ fileDirectoryPath }))
        throw string("wrong path");

    this->fileDirectoryPath = fileDirectoryPath;
}

void File::SetPath(const string& fileDirectoryPath)
{
    if (!is_directory(path{ fileDirectoryPath }))
        throw string("wrong path");

    this->fileDirectoryPath = fileDirectoryPath;
}

string File::GetPath() const
{
    return fileDirectoryPath;
}

void File::Add(const string& name) const
{
    string filePath = fileDirectoryPath + "\\" + name;
    if (is_regular_file(filePath))
        throw string("the file has not been created");

    ofstream file;
    file.open(filePath, ios_base::app);

    if (!file.is_open())
        throw string("the file has not been created");

    file.close();
}

void File::Remove(const string& name) const
{
    string namePath = fileDirectoryPath + "\\" + name;

    if (!is_regular_file(namePath))
        throw string("this is not a file");

    remove(namePath);
}

void File::Rename(const string& oldName, const string& newName) const
{
    string oldNameDirectoryPath = fileDirectoryPath + "\\" + oldName;

    if (!is_regular_file(oldNameDirectoryPath))
        throw string("this is not a file");

    rename(oldNameDirectoryPath, fileDirectoryPath + "\\" + newName);
}

void File::Copy() const
{

}

void File::Relocate() const
{

}

unsigned long long File::GetSizeInBytes() const
{
    if (!is_regular_file(fileDirectoryPath))
        return 0;

    return file_size(fileDirectoryPath);
}