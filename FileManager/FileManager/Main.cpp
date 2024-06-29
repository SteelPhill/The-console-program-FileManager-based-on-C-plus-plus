#include <iostream>
#include <filesystem>
#include <conio.h>
#include <Windows.h>
using namespace std;
using namespace std::filesystem;

class Component
{
public:
    virtual void Add(const string& name) = 0;
    virtual void Remove() = 0;
    virtual void Rename(const string& newName) = 0;
    virtual void Copy() = 0;
    virtual void Relocate() = 0;
    virtual unsigned long long GetSizeInBytes() const = 0;
};

class Directory : public Component
{
    string directoryPath;

    int DirectoryItemsNumber() const
    {
        int count = 1;
        for (const directory_entry& dir_entry : directory_iterator(directoryPath))
            count++;

        return --count;
    }

    unsigned long long GetSizeInBytesByRecursive(const string& directoryPath) const
    {
        unsigned long long size = 0;

        if (!exists(directoryPath))
            return 0;

        if (is_directory(directoryPath))
        {
            directory_iterator m_dir_itr(directoryPath);

            for (m_dir_itr = begin(m_dir_itr); m_dir_itr != end(m_dir_itr); ++m_dir_itr)
            {
                directory_entry m_dir_entry = *m_dir_itr;
                if (is_regular_file(m_dir_entry.path()))
                {
                    size += file_size(m_dir_entry.path());
                }
                else if (is_directory(m_dir_entry.path()))
                {
                    size += GetSizeInBytesByRecursive(m_dir_entry.path().string());
                }
            }

            return size;
        }
        else if (is_regular_file(directoryPath))
        {
            return file_size(directoryPath);
        }
    }

public:
    Directory()
    {
        const string PathToExecutableFile = __FILE__;
        directoryPath = current_path().string();
    }

    string GetDirectoryPath() const
    {
        return directoryPath;
    }

    string SelectDirectoryItem() const
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

    void ShowContent() const
    {
        int count = 1;
        for (const directory_entry& dir_entry : directory_iterator(directoryPath))
            cout << count++ << ": " << dir_entry.path() << endl;
    }

    void Previous()
    {
        directoryPath = directoryPath.substr(0, directoryPath.rfind("\\"));

        if (directoryPath.find("\\") == directoryPath.npos)
            directoryPath += "\\";
    }

    void GoToSelectedDirectory(const string& newPath)
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
    }

    void Add(const string& name) override
    {

    }

    void Remove() override
    {

    }

    void Rename(const string& name) override
    {

    }

    void Copy() override
    {

    }

    void Relocate() override
    {

    }

    unsigned long long GetSizeInBytes() const override
    {
        return GetSizeInBytesByRecursive(directoryPath);
    }
};

class File : public Component
{
    string name;

public:
    File(const string& name)
    {
        this->name = name;
    }

    string GetName() const
    {
        return name;
    }

    void Add(const string& name) override
    {

    }

    void Remove() override
    {

    }

    void Rename(const string& name) override
    {

    }

    void Copy() override
    {

    }

    void Relocate() override
    {

    }

    unsigned long long GetSizeInBytes() const override
    {
        return 0;
    }
};

class FileManagerMenus
{
    static const int EscCode = 27;
    static const int SpaceCode = 32;

    enum class MenusItems
    {
        firstItem = '1',
        secondItem = '2',
        thirdItem = '3',
        fourthItem = '4',
        fifthItem = '5',
        sixthItem = '6',
        seventhItem = '7',
        eighthItem = '8',
        ninthItem = '9',
        show = SpaceCode,
        exit = EscCode
    };

    MenusItems SelectingItem(const char beginRange, const char endRange)
    {
        int choice;

        cout << endl << "Select an item from list => ";

        do
        {
            choice = _getch();

        } while (choice != SpaceCode && choice != EscCode && choice < beginRange || choice > endRange);

        return (MenusItems)choice;
    }

    /* void AddMenu(const Directory& directory)
     {
         cout << "Location:\t" << directory.GetDirectoryPath() << endl << endl;
         cout << "1:\tAdd directory" << endl;
         cout << "2:\tAdd file" << endl;
         cout << "Esc:\tReturn to the main menu" << endl;

         MenusItems choice = SelectingItem('1', '2');

         switch (choice)
         {
         case FileManagerMenus::MenusItems::firstItem:
         {

             break;
         }
         case FileManagerMenus::MenusItems::secondItem:
         {

             break;
         }
         case FileManagerMenus::MenusItems::exit:
         {
             return;
         }
         }
     }*/

public:
    void MainMenu()
    {
        Directory directory;

        do
        {

            cout << "Location:" << endl << directory.GetDirectoryPath() << endl << endl;
            cout << "1: Previous directory" << endl;
            cout << "2: Select next one directory" << endl;
            cout << "3: Go to the directory using the entered path" << endl;
            cout << "4: Add new directory//file" << endl;
            cout << "5: Remove directory//file" << endl;
            cout << "6: Copy directory//file" << endl;
            cout << "7: Relocate directory//file" << endl;
            cout << "8: Rename directory//file" << endl;
            cout << "9: Get size directory//file" << endl;
            cout << "Space: Show contents of directory" << endl;
            cout << "Esc: Exit the program" << endl;

            MenusItems choice = SelectingItem('1', '9');

            system("cls");

            switch (choice)
            {
            case MenusItems::firstItem:
            {
                directory.Previous();
                break;
            }
            case MenusItems::secondItem:
            {
                cout << "Contents of directory:" << endl << directory.GetDirectoryPath() << endl << endl;
                string choice = directory.SelectDirectoryItem();
                if (choice.empty())
                    break;

                try
                {
                    directory.GoToSelectedDirectory(choice);
                }
                catch (const string& error)
                {
                    cout << endl << "Error: " << error << endl << endl;
                    system("pause");
                }

                break;
            }
            case MenusItems::thirdItem:
            {
                //AddMenu(directory);
                break;
            }
            case MenusItems::fourthItem:
            {
                break;
            }
            case MenusItems::fifthItem:
            {

                break;
            }
            case MenusItems::sixthItem:
            {

                break;
            }
            case MenusItems::seventhItem:
            {

                break;
            }
            case MenusItems::eighthItem:
            {

                break;
            }
            case MenusItems::ninthItem:
            {
                cout << "The size of the object located along the path:\t" << directory.GetDirectoryPath() << endl;
                cout << endl << directory.GetSizeInBytes() << " byte" << endl;
                break;
            }
            case MenusItems::show:
            {
                cout << "Contents of directory:" << endl << directory.GetDirectoryPath() << endl << endl;
                directory.ShowContent();
                cout << endl;
                system("pause");
                break;
            }
            case MenusItems::exit:
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