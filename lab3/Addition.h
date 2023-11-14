#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <string>
std::string exc = "exception.txt";
//std::string src = "alph.txt";
std::string dst = "destination.txt";
std::string src = "source.txt";
#include <Windows.h>
#include "Graph.h"

Graph graph = Graph();

bool InputError()
{
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	std::cout << "\nОшибка! Введено некорректное значение!\n Попробуйте снова.\n";
	return false;
}

bool Start(int argc, char* argv[])
{
	std::string message = "Параметры запуска программы:\nsource.txt - обязательный параметр, место хранения словаря\n";
	if (argc <= 1)
	{
		//std::cout << argc << std::endl;
		std::cout << message;
		return false;
	}
	else
	{
		if (argc == 2)
		{
			//std::cout << argc << std::endl;
			dst = argv[1];
			return true;
		}
		else if (argc > 2)
		{
			//std::cout << argc << std::endl;
			std::cout << message << std::endl;
			return false;
		}
	}
}

void GetGraphDim()
{
	try
	{
		std::cout << "Размерность матрицы соответствий: " << graph.GetDim() << std::endl;

	}
	catch (...) 
	{
		std::cout << "Произошла ошибка!" << std::endl;
	}
}

void Update()
{
	try
	{
		std::cout << "Введите размерность матрицы: " << std::endl;
		int dim = 0;
		std::cin >> dim;
		graph.Update(dim);
		std::cout << "Таблица соответствий обновлена!" << std::endl;
	}
	catch (...)
	{
		std::cout << "Произошла ошибка обновления матрицы!" << std::endl;
	}
}
void Print()
{
	try
	{
		graph.Print();
	}
	catch (...)
	{
		std::cout << "Матрица пуста!" << std::endl;
	}
}

void SetEdge()
{
	try
	{
		std::cout << "Введите начальный и конечный города и стоимость пути: " << std::endl;
		int first = 0, second = 0, val = 0;
		std::cin >> first >> second >> val;
		graph.SetEdge(first, second, val);
		std::cout << "Ребро установлено!" << std::endl;
	}
	catch (...)
	{
		std::cout << "Произошла ошибка установки ребра!" << std::endl;
	}
}
void BFS()
{
	try
	{
		std::cout << "Введите начальный город: " << std::endl;
		int begin = 0;
		std::cin >> begin;
		graph.BFS(begin);
		std::cout << "Обход в ширину" << std::endl;
	}
	catch (...)
	{
		std::cout << "Произошла ошибка алгоритма поиска в ширину!" << std::endl;
	}
}

void AddVertex()
{
	try
	{
		graph.AddVertex();
		std::cout << "Вершина добавлена!" << std::endl;

	}
	catch (...)
	{
		std::cout << "Произошла ошибка добавления вершины!" << std::endl;
	}
}

void SetMatrix()
{
	try
	{
		graph.SetMatrix();
		std::cout << "Матрица установлена!" << std::endl;

	}
	catch (...)
	{
		std::cout << "Произошла ошибка установки матрицы соответствий!" << std::endl;
	}
}

void Deikstra()
{
	try
	{
		std::cout << "Введите начальный город: " << std::endl;
		int begin = 0;
		std::cin >> begin;
		graph.Deikstra(begin);

	}
	catch (...)
	{
		std::cout << "Произошла ошибка алгоритмы Деикстры!" << std::endl;
	}
}

void DS()
{
	try
	{
		graph.NewDS();

	}
	catch (...)
	{
		std::cout << "Произошла ошибка поиска в глубину!" << std::endl;
	}
}

void FileWrite()
{
	try
	{
		std::cout << "Введите путь файла: " << std::endl;
		std::string path = "";
		std::cin >> path;
		graph.WriteInFile(path.c_str());
	}
	catch (...)
	{
		std::cout << "Произошла ошибка записи в файл!" << std::endl;
	}
}

void ReadFromFile()
{
	try
	{
		graph.ReadFromFile(src.c_str());
		std::cout << "Считывание произошло успешно!" << std::endl;
	}
	catch (...)
	{
		std::cout << "Ошибка считывания файла" << std::endl;
	}
}

void DFS()
{
	try
	{
		graph.DoDFS();
		std::cout << "Обход графа в глубину" << std::endl;
	}
	catch (...)
	{
		std::cout << "Ошибка обхода" << std::endl;
	}
}

void FloydWarshell()
{
	//graph.ReadFromFile(src.c_str());
	try
	{
		if (graph.Empty()) throw new BaseE("Graph is empty");
		//graph.ReadFromFile(src.c_str());
		int source = 1, drainCtr = 1;
		int* drains = nullptr;

		std::cout << "Введите номер истока: " << std::endl;
		std::cin >> source;
		while (source <= 0 || source >= graph.GetDim())
		{
			std::cout << "Ошибка ввода, введите номер истока " << std::endl;
			std::cin >> source;
		}

		std::cout << "Введите количество стоков: " << std::endl;
		std::cin >> drainCtr;
		while (drainCtr <= 0 || drainCtr >= graph.GetDim() - 1)
		{
			std::cout << "Ошибка ввода, введите количество стоков " << std::endl;
			std::cin >> drainCtr;
		}

		/*std::cout << "Введите номер стока: " << std::endl;
		std::cin >> drain;
		while (drain <= 0 || drain >= graph.GetDim())
		{
			std::cout << "Ошибка ввода, введите номер истока " << std::endl;
			std::cin >> drain;
		}*/

		drains = new int[drainCtr];
		for (int i = 0; i < drainCtr; i++)
		{
			std::cout << "Введите номер стока " << i << ": " << std::endl;
			std::cin >> drains[i];
			bool equal = false;
			for (int j = 0; j < i - 1; j++)
			{
				if (drains[i] == drains[j])
				{
					equal = true;
					break;
				}
			}
			while (drains[i] <= 0 || drains[i] >= graph.GetDim() + 1 || drains[i] == source || equal)
			{
				equal = false;
				std::cout << "Ошибка ввода, введите номер стока " << i << ": " << std::endl;
				std::cin >> drains[i];
				equal = false;
				for (int j = 0; j < i - 1; j++)
				{
					if (drains[i] == drains[j])
					{
						equal = true;
						break;
					}
				}
			}
			drains[i] -= 1;
		}
		drains[0] = 6;
		for (int i = 0; i < drainCtr; i++)
		{
			drains[i] -= 1;
		}
		graph.BFSFloydWarshell(source - 1, drainCtr, drains);
		delete[] drains;
		std::cout << "Поиск максимального потока" << std::endl;
	}
	catch (...)
	{
		std::cout << "Ошибка нахождения максимального потока" << std::endl;
	}
}