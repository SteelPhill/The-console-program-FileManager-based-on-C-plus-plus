#include <iostream>
#include <filesystem>
#include <conio.h>
#include <Windows.h>
using namespace std;
using namespace std::filesystem;
#include "ClassComponent.h"
#include "ClassDirectory.h"
#include "ClassFile.h"

class FileManagerMenus
{
    Component* component;

    static const int EnterCode = 13;
    static const int EscCode = 27;

    int SelectingItem(const char beginRange, const char endRange)
    {
        int choice;

        cout << endl << "Select an item from list => ";

        do
        {
            choice = _getch();

        } while (choice != EnterCode && choice != EscCode && choice < beginRange || choice > endRange);

        cout << endl;
        return choice;
    }

    void AddMenu(const Directory& directory)
    {
        enum class MenuItems
        {
            AddDirectory = '1',
            AddFile = '2',
            Return1 = EnterCode,
            Return2 = EscCode
        };

        cout << "Location:" << endl << directory.GetPath() << endl << endl;
        cout << "1:         Add directory" << endl;
        cout << "2:         Add file" << endl;
        cout << "Enter\\Esc: Return to the main menu" << endl;

        int choice = SelectingItem('1', '2');

        switch ((MenuItems)choice)
        {
        case MenuItems::Return1:
        case MenuItems::Return2:
        {
            return;
        }
        }

        cout << endl << endl << "Enter the name and press \"Enter\"" << endl;
        cout << "Or press \"Enter\" to return to the main menu" << endl;

        string enteredLine;

        cout << endl << " => ";
        getline(cin, enteredLine);

        if (enteredLine == "")
            return;

        switch ((MenuItems)choice)
        {
        case MenuItems::AddDirectory:
        {
            component = dynamic_cast<Directory*>(new Directory(directory.GetPath()));
            component->Add(enteredLine);
            break;
        }
        case MenuItems::AddFile:
        {
            component = dynamic_cast<File*>(new File(directory.GetPath()));
            component->Add(enteredLine);
            break;
        }
        }

        delete component;
    }

    void RenameMenu(const Directory& directory)
    {
        enum class MenuItems
        {
            RenameDirectory = '1',
            RenameFile = '2',
            Return1 = EnterCode,
            Return2 = EscCode
        };

        cout << "Location:" << endl << directory.GetPath() << endl << endl;
        cout << "1:         Rename directory" << endl;
        cout << "2:         Rename file" << endl;
        cout << "Enter\\Esc: Return to the main menu" << endl;

        int choice = SelectingItem('1', '2');

        switch ((MenuItems)choice)
        {
        case MenuItems::Return1:
        case MenuItems::Return2:
        {
            return;
        }
        }

        string oldNamePath = directory.SelectDirectoryItem();
        if (oldNamePath == "")
            return;
        string oldName = oldNamePath.substr(oldNamePath.rfind("\\") + 1, oldNamePath.size() - oldNamePath.rfind("\\"));

        cout << endl << endl << "Enter the new name and press \"Enter\"" << endl;
        cout << "Or press \"Enter\" to return to the main menu" << endl;
        string newName;
        cout << " => ";
        getline(cin, newName);
        if (newName == "")
            return;

        switch ((MenuItems)choice)
        {
        case MenuItems::RenameDirectory:
        {
            component = dynamic_cast<Directory*>(new Directory(directory.GetPath()));
            component->Rename(oldName, newName);
            break;
        }
        case MenuItems::RenameFile:
        {
            string extension = oldNamePath.substr(oldNamePath.rfind("."), oldNamePath.size() - oldNamePath.rfind("."));
            component = dynamic_cast<File*>(new File(directory.GetPath()));
            component->Rename(oldName, newName + extension);
            break;
        }
        }

        delete component;
    }

    void RemoveMenu(const Directory& directory)
    {
        enum class MenuItems
        {
            RemovingDirectory = '1',
            RemovingFile = '2',
            Return1 = EnterCode,
            Return2 = EscCode
        };

        cout << "Location:" << endl << directory.GetPath() << endl << endl;
        cout << "1:         Remove directory" << endl;
        cout << "2:         Remove file" << endl;
        cout << "Enter\\Esc: Return to the main menu" << endl;

        int choice = SelectingItem('1', '2');

        switch ((MenuItems)choice)
        {
        case MenuItems::Return1:
        case MenuItems::Return2:
        {
            return;
        }
        }

        string removeNamePath = directory.SelectDirectoryItem();
        if (removeNamePath == "")
            return;
        string removeName = removeNamePath.substr(removeNamePath.rfind("\\") + 1, removeNamePath.size() - removeNamePath.rfind("\\"));


        switch ((MenuItems)choice)
        {
        case MenuItems::RemovingDirectory:
        {
            component = dynamic_cast<Directory*>(new Directory(directory.GetPath()));
            component->Remove(removeName);
            break;
        }
        case MenuItems::RemovingFile:
        {
            component = dynamic_cast<File*>(new File(directory.GetPath()));
            component->Remove(removeName);
            break;
        }
        }

        delete component;
    }

public:
    void MainMenu()
    {
        enum class MenuItems
        {
            PreviousDirectory = '1',
            GoToDirectorySelectedFromList = '2',
            GoToDirectoryUsingManuallyEnteredPath = '3',
            SubstringSearch = '4',
            AddNewDirectoryOrFile = '5',
            RemoveDirectoryOrFile = '6',
            CopyDirectoryOrFile = '7',
            RelocateDirectoryOrFile = '8',
            RenameDirectoryOrFile = '9',
            GetByteSizeDirectoryOrFile = '0',
            ShowDirectoryContent = EnterCode,
            Exit = EscCode
        };

        Directory directory;

        do
        {
            cout << "Location:" << endl << directory.GetPath() << endl << endl;
            cout << "1:     Previous directory" << endl;
            cout << "2:     Go to the directory selected from the list" << endl;
            cout << "3:     Go to the directory using the manually entered path" << endl;
            cout << "4:     Substring search in current and nested directories" << endl;
            cout << "5:     Add new directory\\file to this directory" << endl;
            cout << "6:     Remove directory\\file from this directory" << endl;
            cout << "7:     Copy directory\\file" << endl;
            cout << "8:     Relocate directory\\file" << endl;
            cout << "9:     Rename directory\\file" << endl;
            cout << "0:     Get size directory\\file" << endl;
            cout << "Enter: Show contents of directory" << endl;
            cout << "Esc:   Exit the program" << endl;

            int choice = SelectingItem('0', '9');

            system("cls");

            switch ((MenuItems)choice)
            {
            case MenuItems::PreviousDirectory:
            {
                directory.Previous();
                break;
            }
            case MenuItems::GoToDirectorySelectedFromList:
            {
                cout << "Contents of directory:" << endl << directory.GetPath() << endl << endl;
                string chosenDirectory = directory.SelectDirectoryItem();
                if (chosenDirectory.empty())
                    break;

                try
                {
                    directory.GoToSelectedDirectory(chosenDirectory);
                }
                catch (const string& error)
                {
                    cout << endl << "Error: " << error << endl << endl;
                    system("pause");
                }

                break;
            }
            case MenuItems::GoToDirectoryUsingManuallyEnteredPath:
            {
                cout << "Enter the path and press \"Enter\"" << endl;
                cout << "Or press \"Enter\" to return to the main menu" << endl;

                string enteredLine;

                cout << " => ";
                getline(cin, enteredLine);

                if (enteredLine == "")
                    break;

                try
                {
                    directory.GoToSelectedDirectory(enteredLine);
                }
                catch (const string& error)
                {
                    cout << endl << "Error: " << error << endl << endl;
                    system("pause");
                }

                break;
            }
            case MenuItems::SubstringSearch:
            {
                cout << "Enter the searched text and press \"Enter\"" << endl;
                cout << "Or press \"Enter\" to return to the main menu" << endl;

                string enteredLine;

                cout << " => ";
                getline(cin, enteredLine);

                if (enteredLine == "")
                    break;

                try
                {
                    cout << endl << "Search result: " << endl << directory.substringSearch(enteredLine) << endl;
                }
                catch (...)
                {
                    cout << endl << "Unexpected error in the search" << endl << endl;
                }

                system("pause");
                break;
            }
            case MenuItems::AddNewDirectoryOrFile:
            {
                try
                {
                    AddMenu(directory);
                }
                catch (const string& error)
                {
                    system("cls");
                    cout << endl << "Error: " << error << endl << endl;
                    system("pause");
                }

                break;
            }
            case MenuItems::RemoveDirectoryOrFile:
            {
                try
                {
                    RemoveMenu(directory);
                }
                catch (const string& error)
                {
                    system("cls");
                    cout << endl << "Error: " << error << endl << endl;
                    system("pause");
                }

                break;
            }
            case MenuItems::CopyDirectoryOrFile:
            {

                break;
            }
            case MenuItems::RelocateDirectoryOrFile:
            {

                break;
            }
            case MenuItems::RenameDirectoryOrFile:
            {
                try
                {
                    RenameMenu(directory);
                }
                catch (const string& error)
                {
                    system("cls");
                    cout << endl << "Error: " << error << endl << endl;
                    system("pause");
                }
               
                break;
            }
            case MenuItems::GetByteSizeDirectoryOrFile:
            {
                cout << "The size of the object located along the path:\t" << directory.GetPath() << endl;
                cout << endl << directory.GetSizeInBytes() << " byte" << endl;
                system("pause");
                break;
            }
            case MenuItems::ShowDirectoryContent:
            {
                cout << "Contents of directory:" << endl << directory.GetPath() << endl << endl;
                directory.ShowContent();
                cout << endl;
                system("pause");
                break;
            }
            case MenuItems::Exit:
            {
                cout << "Exiting the program . . ." << endl;
                return;
            }
            }

            system("cls");

        } while (true);
    }
};

void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    FileManagerMenus fileManagerMenus;
    fileManagerMenus.MainMenu();
   
    cout << endl;
    system("pause");
}