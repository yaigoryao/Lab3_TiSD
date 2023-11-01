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
	std::cout << "\n������! ������� ������������ ��������!\n ���������� �����.\n";
	return false;
}

bool Start(int argc, char* argv[])
{
	std::string message = "��������� ������� ���������:\nsource.txt - ������������ ��������, ����� �������� �������\n";
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
		std::cout << "����������� ������� ������������: " << graph.GetDim() << std::endl;

	}
	catch (...) 
	{
		std::cout << "��������� ������!" << std::endl;
	}
}

void Update()
{
	try
	{
		std::cout << "������� ����������� �������: " << std::endl;
		int dim = 0;
		std::cin >> dim;
		graph.Update(dim);
		std::cout << "������� ������������ ���������!" << std::endl;
	}
	catch (...)
	{
		std::cout << "��������� ������ ���������� �������!" << std::endl;
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
		std::cout << "������� �����!" << std::endl;
	}
}

void SetEdge()
{
	try
	{
		std::cout << "������� ��������� � �������� ������ � ��������� ����: " << std::endl;
		int first = 0, second = 0, val = 0;
		std::cin >> first >> second >> val;
		graph.SetEdge(first, second, val);
		std::cout << "����� �����������!" << std::endl;
	}
	catch (...)
	{
		std::cout << "��������� ������ ��������� �����!" << std::endl;
	}
}
void BFS()
{
	try
	{
		std::cout << "������� ��������� �����: " << std::endl;
		int begin = 0;
		std::cin >> begin;
		graph.BFS(begin);
		std::cout << "����� � ������" << std::endl;
	}
	catch (...)
	{
		std::cout << "��������� ������ ��������� ������ � ������!" << std::endl;
	}
}

void AddVertex()
{
	try
	{
		graph.AddVertex();
		std::cout << "������� ���������!" << std::endl;

	}
	catch (...)
	{
		std::cout << "��������� ������ ���������� �������!" << std::endl;
	}
}

void SetMatrix()
{
	try
	{
		graph.SetMatrix();
		std::cout << "������� �����������!" << std::endl;

	}
	catch (...)
	{
		std::cout << "��������� ������ ��������� ������� ������������!" << std::endl;
	}
}

void Deikstra()
{
	try
	{
		std::cout << "������� ��������� �����: " << std::endl;
		int begin = 0;
		std::cin >> begin;
		graph.Deikstra(begin);

	}
	catch (...)
	{
		std::cout << "��������� ������ ��������� ��������!" << std::endl;
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
		std::cout << "��������� ������ ������ � �������!" << std::endl;
	}
}

void FileWrite()
{
	try
	{
		std::cout << "������� ���� �����: " << std::endl;
		std::string path = "";
		std::cin >> path;
		graph.WriteInFile(path.c_str());
	}
	catch (...)
	{
		std::cout << "��������� ������ ������ � ����!" << std::endl;
	}
}

void ReadFromFile()
{
	try
	{
		graph.ReadFromFile(src.c_str());
		std::cout << "���������� ��������� �������!" << std::endl;
	}
	catch (...)
	{
		std::cout << "������ ���������� �����" << std::endl;
	}
}

void DFS()
{
	try
	{
		graph.DoDFS();
		std::cout << "����� ����� � �������" << std::endl;
	}
	catch (...)
	{
		std::cout << "������ ������" << std::endl;
	}
}