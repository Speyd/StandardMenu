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

public:

    Menu(std::vector<ItemMenu>&& _itemsMenu) :
        choice{ 0 },
        itemsMenu{ _itemsMenu }                  //move для срабатывания конструктора переноса
    {}


    void inputItemMenu()
    {
        size_t size{ this->itemsMenu.size() };

        for (size_t i{}; i < size; i++)
        {
            std::cout << i + 1 << ". " << this->itemsMenu[i].textSelection << std::endl;
        }
    }

    const short setChoicePlayer()
    {
        while (this->itemsMenu.size() != 0 && this->choice < 1 || this->choice > this->itemsMenu.size())
        {
            inputItemMenu();
            std::cout << "Enter your choice: "; std::cin >> this->choice;
        }

        return --(this->choice);
    }


    pointerEmptyFun operator[](const short _choice)
    {
        if (_choice < 0)
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
    Menu menu{ {{"First text", &d}, {"Second text", &b}} };
    menu[menu.setChoicePlayer()]();


    std::cout << "Hello World!\n";
}
