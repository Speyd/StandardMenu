#include <iostream>
#include <vector>

typedef void(*pointerEmptyFun)();


struct ItemMenu
{
    std::string textSelection{};
    pointerEmptyFun pointer;

};


class Menu
{
private:

    short choice;
    std::vector<ItemMenu> itemsMenu;
    const std::string nameMenu;

public:

    Menu(const std::string& _nameMenu, std::vector<ItemMenu>&& _itemsMenu) :
        choice{ 1 },
        nameMenu{ _nameMenu },
        itemsMenu{ _itemsMenu }                  //move для срабатывания конструктора переноса
    {}


    void inputItemMenu()
    {
        size_t size{ this->itemsMenu.size() };

        std::cout << "\t\t\t" << nameMenu << std::endl;
        for (size_t i{}; i < size; i++)
        {
            std::cout << i + 1 << ". " << this->itemsMenu[i].textSelection << std::endl;
        }

        if(this->choice < 1 || this->choice > this->itemsMenu.size())
        {
            std::cout << "There is no such choice '" << this->choice << "'!" << std::endl;
        }
    }

    const short setChoicePlayer()
    {

        if (this->itemsMenu.size() == 0) return -1;

        do
        {
            inputItemMenu();
            std::cout << "Enter your choice: "; std::cin >> this->choice;
        }
        while(this->choice < 1 || this->choice > this->itemsMenu.size());

        return --(this->choice);
    }


    pointerEmptyFun operator[](const short _choice)
    {
        if (_choice < 0 || choice > this->itemsMenu.size() - 1)
        {
            return []() { std::cout << "Error choice" << std::endl; };
        }

        std::cout << "Your choice: " << this->itemsMenu[_choice].textSelection << std::endl;
        if (this->itemsMenu[_choice].pointer != nullptr)
        {
            return this->itemsMenu[_choice].pointer;
        }
        else
        {
            return []() { std::cout << "Nullptr pointer" << std::endl; };
        }
    }

};

void d() { std::cout << "First FUN" << std::endl; }
void b() { std::cout << "Second FUN" << std::endl; }


int main()
{
    Menu menu{ "Your menu name ", {{"First text", &d}, {"Second text", &b}}};
    menu[menu.setChoicePlayer()]();

    return 0;
}
