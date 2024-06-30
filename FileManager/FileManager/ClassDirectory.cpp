#include <iostream>
#include <filesystem>
using namespace std;
using namespace std::filesystem;
#include "ClassComponent.h"
#include "ClassDirectory.h"

int Directory::DirectoryItemsNumber() const
{
    int count = 1;
    for (const directory_entry& dir_entry : directory_iterator(directoryPath))
        count++;

    return --count;
}

unsigned long long Directory::GetSizeInBytesByRecursive(const string& directoryPath) const
{
    unsigned long long size = 0;

    if (!exists(directoryPath))
        return 0;

    if (is_directory(directoryPath))
    {
        directory_iterator dirItr(directoryPath);

        for (dirItr = begin(dirItr); dirItr != end(dirItr); ++dirItr)
        {
            directory_entry dirEntry = *dirItr;
            if (is_regular_file(dirEntry.path()))
            {
                size += file_size(dirEntry.path());
            }
            else if (is_directory(dirEntry.path()))
            {
                size += GetSizeInBytesByRecursive(dirEntry.path().string());
            }
        }

        return size;
    }
    else if (is_regular_file(directoryPath))
    {
        return file_size(directoryPath);
    }
}

string Directory::MaskSearchByRecursive(const string& directoryPath, const string& searchedText) const
{
    string result;

    if (!exists(directoryPath))
        return "";

    if (is_directory(directoryPath))
    {
        directory_iterator dirItr(directoryPath);

        for (dirItr = begin(dirItr); dirItr != end(dirItr); ++dirItr)
        {
            directory_entry dirEntry = *dirItr;
            if (is_regular_file(dirEntry.path()))
            {
                if (dirEntry.path().string().find(searchedText) != string::npos)
                    result += dirEntry.path().string() + "\n\r";
            }
            else if (is_directory(dirEntry.path()))
            {
                result += MaskSearchByRecursive(dirEntry.path().string(), searchedText);
            }
        }
    }

    return result;
}

Directory::Directory()
{
    const string PathToExecutableFile = __FILE__;
    directoryPath = current_path().string();
}

Directory::Directory(const string& directoryPath)
{
    if (!is_directory(path{ directoryPath }))
        throw string("wrong path");

    this->directoryPath = directoryPath;
}

void Directory::SetPath(const string& directoryPath)
{
    if (!is_directory(path{ directoryPath }))
        throw string("wrong path");

    this->directoryPath = directoryPath;
}

string Directory::GetPath() const
{
    return directoryPath;
}

string Directory::SelectDirectoryItem() const
{
    string ReturnSymbol = "";

    ShowContent();

    int itemsNumber = DirectoryItemsNumber();

    string enteredLine;
    int selectedItem;

    cout << endl << "Enter the item number and press \"Enter\"" << endl;
    cout << "Or press \"Enter\" to return to the main menu" << endl;

    do
    {
        cout << " => ";
        getline(cin, enteredLine);

        if (enteredLine == ReturnSymbol)
            return "";

        try
        {
            selectedItem = stoi(enteredLine);
        }
        catch (...)
        {
            continue;
        }

        if (selectedItem < 1 || selectedItem > itemsNumber)
        {
            continue;
        }

        break;

    } while (true);

    int count = 1;
    for (auto& i : directory_iterator(directoryPath))
    {
        if (selectedItem == count)

            return i.path().string();
        count++;
    }
}

string Directory::MaskSearch(const string& searchedText)
{
    if (searchedText.empty())
        return "";
           
    return MaskSearchByRecursive(directoryPath, searchedText);
}

void Directory::ShowContent() const
{
    int count = 1;
    for (const directory_entry& dir_entry : directory_iterator(directoryPath))
        cout << count++ << ": " << dir_entry.path() << endl;
}

void Directory::Previous()
{
    directoryPath = directoryPath.substr(0, directoryPath.rfind("\\"));

    if (directoryPath.find("\\") == directoryPath.npos)
        directoryPath += "\\";
}

void Directory::GoToSelectedDirectory(const string& newPath)
{
    if (!is_directory(newPath))
        throw string("this is not a directory");

    for (auto& i : directory_iterator(directoryPath))
    {
        if (newPath == i.path().string())
        {
            directoryPath = i.path().string();
            break;
        }
    }

    directoryPath = newPath;
}

void Directory::Add(const string& name) const
{
    string namePath = directoryPath + "\\" + name;

    path path(namePath);
    if (!create_directories(path))
        throw string("the directory has not been created");
}

void Directory::Remove() const
{

}

void Directory::Rename(const string& name) const
{

}

void Directory::Copy() const
{

}

void Directory::Relocate() const
{

}

unsigned long long Directory::GetSizeInBytes() const
{
    return GetSizeInBytesByRecursive(directoryPath);
}