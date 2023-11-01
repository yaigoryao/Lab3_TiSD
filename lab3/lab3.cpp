#include <iostream>
#include "Graph.h"
#include <cstdio>
//#include <windows.h>
#include "Addition.h"
#include "Menu.h"
using namespace std;
int main(int argc, char** argv)
{
	setlocale(0, "");
	if (Start(argc, argv))
	{
		Menu menu = Menu("Петроченков И. А. ИУК4-32Б");
		menu.AddItem("Получить размерность матрицы соответствий", GetGraphDim);
		menu.AddItem("Обновить размерность матрицы соответствий", Update);
		menu.AddItem("Напечатать матрицу соответствий", Print);
		menu.AddItem("Установить ребро", SetEdge);
		menu.AddItem("Обход методом поиска в ширину", BFS);
		menu.AddItem("Добавить вершину", AddVertex);
		menu.AddItem("Установить матрицу соответствий", SetMatrix);
		menu.AddItem("Поиск наименьшего пути алгоритмом Деикстры", Deikstra);
		menu.AddItem("Поиск наименьшего пути методом поиска в глубину", DS);
		menu.AddItem("Запись в файл матрицы соответствий", FileWrite);
		menu.AddItem("Чтение из файла матрицы соответствий", ReadFromFile);
		menu.AddItem("Обход графа в глубину", DFS);
		menu.RunMenu();
	}
}
