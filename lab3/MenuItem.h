#pragma once
#include <iostream>
#include <string>
using namespace std;
class MenuItem {
protected:
	string name;
	void (*func)();
public:
	MenuItem() {};
	MenuItem(string name, void (*func)());
	void RunFunction();
	void PrintItem();
	void Set(string name, void (*func)())
	{
		this->name = name;
		this->func = func;
	}
	std::string& Name()
	{
		return this->name;
	}
};
MenuItem::MenuItem(string name, void(*func)()) {
	this->name = name;
	this->func = func;
}
void MenuItem::RunFunction() {
	this->func();
}
void MenuItem::PrintItem() {
	cout << name;
}
