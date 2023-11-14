#pragma once
//#include "Addition.h"
#pragma once
#include "MenuItem.h"
#include <Windows.h>
#include <conio.h>

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void SetCursor(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}
class Menu {
protected:
	string name;
	MenuItem* items = nullptr;
	int countOfItem = 0;
public:
	Menu(string name, int countOfItems, MenuItem* items[]);
	void PrintMenu();
	void RunMenu();
	void AddItem(string name, void (*func)())
	{
		countOfItem++;
		MenuItem* temp = new MenuItem[countOfItem];
		for (int i = 0; i < countOfItem - 1; i++)
		{
			temp[i] = items[i];
		}
		temp[countOfItem - 1].Set(name, func);
		items = temp;
	}
	Menu()
	{
		items = nullptr;
		countOfItem = 0;
	}
	Menu(std::string name)
	{
		this->name = name;
		items = nullptr;
		countOfItem = 0;
	}
	
};

Menu::Menu(string name, int countOfItems, MenuItem* items[]) {
	this->name = name;
	this->countOfItem = countOfItems;
	for (int i = 0; i < countOfItem; i++) {
		this->items[i] = *items[i];
	}
}

void Menu::PrintMenu() {
	system("cls");
	cout << name << "\n";
	for (int i = 0; i < countOfItem; i++) {
		cout << "  [" << i + 1 << "] " << items[i].Name();
		//items[i].PrintItem();
		cout << "\n";
	}
	cout << "  [0] Выход\n";
}
void Menu::RunMenu() {
	int choice = 1;
	bool input = false;
	bool call = false;
	this->PrintMenu();
	SetCursor(0, 1);
	std::cout << ">";
	do 
	{
		char ch = _getch();
		switch (ch)
		{
		case 13:
			call = true;
			input = true;
			break;
		/*case 27:
			choice = 0;
			break;*/
		case 80:
			if (choice <= this->countOfItem)
			{
				input = true;
				choice++;
			}
			else
			{
				choice = 1;
				input = true;
			}
			break;
		case 72:
			if (choice - 1 >= 1)
			{
				input = true;
				choice--;
			}
			else
			{
				choice = this->countOfItem + 1;
				input = true;
			}
			break;
		case -32:
		default:
			input = false;
			break;
		}	
		if (input)
		{
			if (call)
			{
				if (choice <= countOfItem && choice >= 0)
				{
					if (choice != 0)
					{
						system("cls");
						items[choice - 1].RunFunction();
						system("pause");
						system("cls");
						this->PrintMenu();
						SetCursor(0, choice);
						std::cout << '>';
					}
				}
				else if (choice == countOfItem + 1)
				{
					break;
				}
			}
			else
			{
				for (int i = 0; i < this->countOfItem + 1; i++)
				{
					SetCursor(0, 1 + i);
					std::cout << ' ';
				}
				SetCursor(0, choice);
				std::cout << '>';
			}
			call = false;
		}
		input = false;
	} while (choice != 0);
}
