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

        return choice;
    }

    string EnterDirectoryPath() const
    {

    }

    void AddMenu(const string& path)
    {
        enum class MenuItems
        {
            addDirectory = '1',
            addFile = '2',
            returnToMainMenu1 = EnterCode,
            returnToMainMenu2 = EscCode
        };

        cout << "Location:" << endl << path << endl << endl;
        cout << "1:         Add directory" << endl;
        cout << "2:         Add file" << endl;
        cout << "Enter\\Esc: Return to the main menu" << endl;

        int choice = SelectingItem('1', '2');

        cout << endl << endl << "Enter the name and press \"Enter\"" << endl;
        cout << "Or press \"Enter\" to return to the main menu" << endl;

        string enteredLine;

        cout << endl << " => ";
        getline(cin, enteredLine);

        if (enteredLine == "")
            return;

        switch ((MenuItems)choice)
        {
        case MenuItems::addDirectory:
        {
            component = dynamic_cast<Directory*>(new Directory(path));
            component->Add(enteredLine);
            break;
        }
        case MenuItems::addFile:
        {
            component = dynamic_cast<File*>(new File(path));
            component->Add(enteredLine);
            break;
        }
        case MenuItems::returnToMainMenu1:
        case MenuItems::returnToMainMenu2:
        {
            return;
        }
        }

        delete component;
    }

public:
    void MainMenu()
    {
        enum class MenuItems
        {
            previousDirectory = '1',
            goToDirectorySelectedFromList = '2',
            goToDirectoryUsingManuallyEnteredPath = '3',
            maskSearch = '4',
            addNewDirectoryOrFile = '5',
            removeDirectoryOrFile = '6',
            copyDirectoryOrFile = '7',
            relocateDirectoryOrFile = '8',
            renameDirectoryOrFile = '9',
            getSizeDirectoryOrFile = '0',
            showDirectoryContent = EnterCode,
            exit = EscCode
        };

        Directory directory;

        do
        {
            cout << "Location:" << endl << directory.GetPath() << endl << endl;
            cout << "1:     Previous directory" << endl;
            cout << "2:     Go to the directory selected from the list" << endl;
            cout << "3:     Go to the directory using the manually entered path" << endl;
            cout << "4:     Mask search in current and nested directories" << endl;
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
            case MenuItems::previousDirectory:
            {
                directory.Previous();
                break;
            }
            case MenuItems::goToDirectorySelectedFromList:
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
            case MenuItems::goToDirectoryUsingManuallyEnteredPath:
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
            case MenuItems::maskSearch:
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
                    cout << endl << "Search result: " << endl << directory.MaskSearch(enteredLine) << endl;
                }
                catch (...)
                {
                    cout << endl << "Unexpected error in the search" << endl << endl;
                }

                system("pause");
                break;
            }
            case MenuItems::addNewDirectoryOrFile:
            {
                try
                {
                    AddMenu(directory.GetPath());
                }
                catch (const string& error)
                {
                    system("cls");
                    cout << endl << "Error: " << error << endl << endl;
                    system("pause");
                }

                break;
            }
            case MenuItems::removeDirectoryOrFile:
            {

                break;
            }
            case MenuItems::copyDirectoryOrFile:
            {

                break;
            }
            case MenuItems::relocateDirectoryOrFile:
            {

                break;
            }
            case MenuItems::renameDirectoryOrFile:
            {

                break;
            }
            case MenuItems::getSizeDirectoryOrFile:
            {
                cout << "The size of the object located along the path:\t" << directory.GetPath() << endl;
                cout << endl << directory.GetSizeInBytes() << " byte" << endl;
                system("pause");
                break;
            }
            case MenuItems::showDirectoryContent:
            {
                cout << "Contents of directory:" << endl << directory.GetPath() << endl << endl;
                directory.ShowContent();
                cout << endl;
                system("pause");
                break;
            }
            case MenuItems::exit:
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