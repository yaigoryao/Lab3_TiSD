#pragma once
#include <iostream>
#include <iomanip>
#include <C:\Users\Игорь\Desktop\учеба\LabRab\ЛР ВП 2 Сем\1 ЛР\LR1\LR1\myException.h>
#include "C:\Users\Игорь\Desktop\учеба\LabRab\ЛР ВП 2 Сем\1 ЛР\LR1\LR1\myVector.h"
#include "Exceptions.h"
#include <fstream>

struct RouteParams
{
public:
	int cost = 0;
	int len = 0;
	//char* pathName = nullptr;
	PIA::myVector<char> name = PIA::myVector<char>();
	RouteParams()
	{
		cost = 0;
		len = 0;
		name.clear();
	}

	RouteParams(int cost, int len, PIA::myVector<char> name)
	{
		this->cost = cost;
		this->len = len;
		this->name = name;
	}

	RouteParams(const RouteParams& other)
	{
		this->cost = other.cost;
		this->len = other.len;
		this->name = other.name;
	}
	RouteParams& operator=(const RouteParams& other)
	{
		this->cost = other.cost;
		this->len = other.len;
		this->name = other.name;
		return *this;
	}

	RouteParams Copy()
	{
		RouteParams result = RouteParams();
		result.cost = this->cost;
		result.len = this->len;
		result.name = this->name;
		return result;
	}
	/*~RouteParams()
	{
		delete[] pathName;
	}*/
};

struct Routes
{
public:
	RouteParams* routes = nullptr;
	int len = 0;
	Routes()
	{
		len = 0;
		routes = nullptr;
	}
	Routes& operator=(const Routes& other)
	{
		this->len = other.len;
		if (this->routes) delete[] this->routes;
		this->routes = new RouteParams[this->len];
		for (int i = 0; i < other.len; i++)
		{
			this->routes[i] = other.routes[i];
		}
		return *this;
	}
	~Routes()
	{
		if(this->routes) delete[] routes;
	}
};

class Graph
{
private:
	int** adjacency = nullptr;
	int dim = 0;
public:
	Graph()
	{
		this->adjacency = 0;
		this->dim = 0;
	}
	Graph(int dim)
	{
		this->dim = dim;
		if (this->adjacency)
		{
			for (int i = 0; i < dim; i++)
			{
				if (adjacency[i]) delete[] adjacency[i];
			}
		}
		this->adjacency = new int* [dim];
		for (int i = 0; i < dim; i++)
		{
			this->adjacency[i] = new int[dim];
		}
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				this->adjacency[i][j] = 0;
			}
		}
	}

	int GetDim() const 
	{
		return this->dim;
	}

	void Update(int dim)
	{
		if (dim <= 0) throw new OutOfRangeE("Matrix dimension can't be lower than one");
		if (this->adjacency)
		{
			for (int i = 0; i < this->dim; i++)
			{
				if (adjacency[i]) delete[] adjacency[i];
			}
		}
		this->dim = dim;
		this->adjacency = new int* [this->dim];
		for (int i = 0; i < this->dim; i++)
		{
			this->adjacency[i] = new int[this->dim];
		}
		for (int i = 0; i < this->dim; i++)
		{
			for (int j = 0; j < this->dim; j++)
			{
				this->adjacency[i][j] = 0;
			}
		}
	}

	int& operator()(int i, int j)
	{
		if (i < 0 || j < 0) throw new OutOfRangeE("Index can't be lower than zero");
		if (i > this->dim - 1 || j > this->dim - 1) throw new OutOfRangeE("Index can't be greater than matrix dimension");
		return this->adjacency[i][j];
	}

	void Print() const
	{
		if (!this->adjacency) throw new BaseE("The graph is empty");
		for (int i = 0; i < dim + 1; i++)
		{
			for (int j = 0; j < dim + 1; j++)
			{
				if (i == 0 && j == 0)
				{
					std::cout << std::setw(3) << 'г';
				}
				else if (i == 0 || j == 0)
				{
					std::cout << std::setw(3) << (char)('A' - 1 + i + j);
				}
				else
				{
					std::cout << std::setw(3) << adjacency[i-1][j-1];
				}
			}
			std::cout << std::endl;
		}
	}

	void SetEdge(int first, int second, int value)
	{
		if(first < 0 || second < 0) throw new OutOfRangeE("Index can't be lower than zero");
		if(first > this->dim-1 || second > this->dim - 1) throw new OutOfRangeE("Index can't be greater than matrix dimension");
		if (first == second) throw new BaseE("Can't change distance");
		if(first < this->dim && second < this->dim)
		this->adjacency[first - 1][second - 1] = value;
		this->adjacency[second - 1][first - 1] = value;
	}
	
	void BFS(int begin) const
	{
		if(begin < 1) throw new OutOfRangeE("Index can't be lower than one");
		if (begin > this->dim) throw new OutOfRangeE("Index can't be greater than matrix dimension");
		int unit = begin - 1;
		bool* visited = new bool[this->dim];
		for (int i = 0; i < this->dim; i++)
		{
			visited[i] = false;
		}
		int* queue = new int[this->dim];
		int count = 0;
		int head = 0;
		for (int i = 0; i < this->dim; i++)
		{
			queue[i] = 0;
		}
		queue[count++] = unit;
		visited[unit] = true;
		while (head < count)
		{
			unit = queue[head++];
			std::cout << (char)(unit + 'A') << ' ';
			for (int i = 0; i < this->dim; i++)
			{
				if (adjacency[unit][i] && !visited[i])
				{
					queue[count++] = i;
					visited[i] = true;
				}
			}
		}
		std::cout << std::endl;
		delete[] queue;
	}

	void AddVertex()
	{
		int** temp = new int* [this->dim+1];
		for (int i = 0; i< this->dim +1; i++)
		{
			temp[i] = new int[this->dim +1];
		}
		for (int i = 0; i < this->dim; i++)
		{
			for (int j = 0; j < this->dim; j++)
			{
				temp[i][j] = adjacency[i][j];
			}
		}
		//Update(this->dim + 1);
		this->dim += 1;
		for (int i = 0; i < dim - 1; i++)
		{
			std::cout << "Введите вес между городами " << (char)(dim - 1 + 'A') << " и " << (char)(i + 'A') << ": ";
			int val = 0;
			while (!(std::cin >> val))
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cout << "\nОшибка! Введено некорректное значение!\n Попробуйте снова.\n";
			}
			temp[dim - 1][i] = val;
			temp[i][dim - 1] = val;
			//temp[dim][i] = val;
			//temp[i][dim] = val;
		}
		temp[dim - 1][dim-1] = 0;

		if (this->adjacency)
		{
			for (int i = 0; i < this->dim - 1; i++)
			{
				if (this->adjacency[i]) delete[] this->adjacency[i];
			}
		}
		this->adjacency = temp;
	}

	void SetMatrix()
	{
		int bias = 0;
		for (int i = 0; i < dim; i++)
		{
			adjacency[i][i] = 0;
		}
		for (int i = 0; i < dim - 1; i++)
		{
			for (int j = i + 1; j < dim; j++)
			{
				std::cout << "Введите вес между городами " << (char)(i + 'A') << " и " << (char)(j + 'A') << ": ";
				int val = 0;
				while (!(std::cin >> val))
				{
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
					std::cout << "\nОшибка! Введено некорректное значение!\n Попробуйте снова.\n";
				}
				adjacency[i][j] = val;
				adjacency[j][i] = val;
			}
		}
	}
	
	void Deikstra(int start) const
	{
		if(start < 0) throw new OutOfRangeE("Index can't be lower than zero");
		if(start > this->dim) throw new OutOfRangeE("Index can't be greater than matrix dimension");
		int begin = start - 1;
		PIA::myVector<int> distance = PIA::myVector<int>();
		int count = 0, index = 0, u = 0;// , m = begin + 1;
		bool* visited = new bool[this->dim];
		for (int i = 0; i < this->dim; i++)
		{
			distance.pushBack(INT_MAX);
			visited[i] = false;
		}
		distance[begin] = 0;
		for (count = 0; count < this->dim - 1; count++)
		{
			int min = INT_MAX;
			for (int i = 0; i < this->dim; i++)
			{
				if (!visited[i] && distance[i] <= min)
				{
					min = distance[i];
					index = i;
				}
			}
			u = index;
			visited[u] = true;
			for (int i = 0; i < this->dim; i++)
			{
				if (!visited[i] && this->adjacency[u][i] && distance[u] != INT_MAX &&
					distance[u] + adjacency[u][i] < distance[i])
					distance[i] = distance[u] + adjacency[u][i];
			}
		}
		for (int i = 0; i < this->dim; i++)
		{
			if (distance[i] != INT_MAX)
				std::cout << "Маршрут из " << (char)(begin + 'A') << " в " << (char)('A' + (i) % (this->dim)) << " = " << distance[i] << std::endl;
			else std::cout << "Маршрут из " << (char)(begin + 'A') << " в " << (char)('A' + (i ) % (this->dim)) << " = " << "маршрут недоступен" << std::endl;
		}
		delete[] visited;
	}
	void NewDS() const
	{
		int begin = 0;
		std::cout << "Введите начальный город: ";
		while (!(std::cin >> begin) || begin < 0 || begin > this->dim)
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "\nОшибка! Введено некорректное значение!\n Попробуйте снова.\n";
		}
		int end = 0;
		std::cout << "Введите конечный город: ";
		while (!(std::cin >> end) || end < 0 || end > this->dim)
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "\nОшибка! Введено некорректное значение!\n Попробуйте снова.\n";
		}
		PIA::myVector<bool> visited = PIA::myVector<bool>();
		for (int i = 0; i < this->dim; i++)
		{
			visited.pushBack(false);
		}
		PIA::myVector<RouteParams> params = PIA::myVector<RouteParams>();
		RouteParams base = RouteParams(0, 0, PIA::myVector<char>());
		NewDepthSearch(begin - 1, end - 1, visited, params, base);
		auto shortest = RouteParams(INT_MAX, INT_MAX, PIA::myVector<char>());
		for (auto el : params)
		{
			/*std::cout << "cost: " << el.cost << " len: " << el.len << " name: ";
			for (auto& e : el.name)
			{
				std::cout << e;
			}
			std::cout << std::endl;*/
			if (el.name[el.len - 1] == (char)('A' + end - 1))
			{
				if (el.cost < shortest.cost)
				{
					shortest = el;
				}
			}
		}
		if (shortest.cost != INT_MAX && shortest.len != INT_MAX)
		{
			std::cout << "Кратчайший путь из " << (char)('A' + begin - 1) << " в " << (char)('A' + end - 1) << ": " << std::endl;
			std::cout << "Стоимость: " << shortest.cost << " Длина пути: " << shortest.len << " Название: ";
			for (auto& e : shortest.name)
			{
				std::cout << e;
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Из города " << (char)('A' + begin - 1) << " в " << (char)('A' + end - 1) << " добраться нельзя" << std::endl;
		}
	}

	void NewDepthSearch(int start, int end, PIA::myVector<bool> visited, PIA::myVector<RouteParams>& params, RouteParams base) const
	{
		try
		{
			visited[start] = true;
			if (start == end)
			{
				auto name = PIA::myVector<char>(base.name);
				name.pushBack((char)('A' + start));
				RouteParams nbase = RouteParams(base.cost + adjacency[start][start], base.len + 1, name);
				params.pushBack(nbase);
				return;
			}
			else
			{
				for (int i = 0; i < this->dim; i++)
				{
					if (adjacency[start][i] != 0 && !visited[i])
					{
						auto name = PIA::myVector<char>(base.name);
						name.pushBack((char)('A' + start));
						RouteParams nbase = RouteParams(base.cost + adjacency[start][i], base.len + 1, name);//base.name + (char)('A' + start));
						params.pushBack(nbase);
						NewDepthSearch(i, end, visited, params, nbase);
					}
				}
			}
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	void WriteInFile(const char* path) const
	{
		try
		{
			std::ofstream fout;
			fout.open(path);
			if (!this->adjacency) throw new BaseE("The graph is empty");
			for (int i = 0; i < dim + 1; i++)
			{
				for (int j = 0; j < dim + 1; j++)
				{
					if (i == 0 && j == 0)
					{
						fout << std::setw(3) << 'г';
					}
					else if (i == 0 || j == 0)
					{
						fout << std::setw(3) << (char)('A' - 1 + i + j);
					}
					else
					{
						fout << std::setw(3) << adjacency[i - 1][j - 1];
					}
				}
				fout << std::endl;
			}
			fout.close();
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			std::cout << "Произошла ошибка записи в файл!" << std::endl;
		}
	}
	void Clear()
	{
		if (this->adjacency)
		{
			for (int i = 0; i < this->dim; i++)
			{
				if (this->adjacency[i]) delete adjacency[i];
			}
		}
		this->dim = 0;
	}

	void ReadFromFile(const char* path)
	{
		try
		{
			this->Clear();
			std::ifstream fin;
			fin.open(path);
			fin >> this->dim;
			this->Update(this->dim);
			for (int i = 0; i < this->dim; i++)
			{
				for (int j = 0; j < this->dim; j++)
				{
					fin >> this->adjacency[i][j];
				}
			}
			fin.close();
		}
		catch (...)
		{
			std::cout << "Произошла ошибка считывания файла" << std::endl;
		}
	}

	void DoDFS() const
	{
		std::cout << "Введите начальный город" << std::endl;
		int begin = 0;
		while (!(std::cin >> begin) || begin < 0 || begin > this->dim)
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "\nОшибка! Введено некорректное значение!\n Попробуйте снова.\n";
		}
		bool* visited = new bool[this->dim];
		for (int i = 0; i < this->dim; i++)
		{
			visited[i] = false;
		}
		DFS(visited, begin - 1);
		delete[] visited;
		std::cout << std::endl;
	}

	void DFS(bool* visited, int begin) const
	{
		std::cout << (char)('A' + begin);
		visited[begin] = true;
		for (int i = 0; i < this->dim; i++)
		{
			if (this->adjacency[begin][i] != 0 && !visited[i])
			{
				DFS(visited, i);
			}
		}
	}
	/*void PrintList(bool* visited)
	{
		for (int i = 0; i < dim; i++)
		{
			std::cout << visited[i] << ' ';
		}
		std::cout << std::endl;
	}*/
	/*void DoDS()
	{
		bool* visited = new bool[dim] {};
		int begin = 0;
		std::cout << "Введите начальный город: ";
		std::cin >> begin;
		int end = 0;
		std::cout << "Введите конечный город: ";
		std::cin >> end;
		bool flag = false;
		int* summ = new int[dim];
		DepthSearch(begin - 1, end - 1, visited, flag, summ);
		int len = 0;
		for (int i = 0; i < dim; i++)
		{
			if (visited[i] == true) len++;
		}
		if (len == 1)
		{
			std::cout << "Нет способа добраться из вершины " << begin << " до вершины " << end << std::endl;
		}
		else
		{
			std::cout << std::endl << "Стоимость: " << summ << std::endl << "Длина: " << len << std::endl;
		}
		delete[] visited;
	}*/
	/*void DepthSearch(int begin, int end, bool* visited, bool& flag, int* summ)
	{
		if (!flag)
		{
			std::cout << begin + 1 << ' ';
			visited[begin] = true;
			if (begin == end)
			{
				flag = true;
				return;
			};
			for (int i = 0; i < this->dim; i++)
			{
				if (!flag && adjacency[begin][i] != 0 && !visited[i])
				{
					DepthSearch(i, end, visited, flag, summ);
					summ[begin] += adjacency[begin][i];
				}
			}
			
		}
	}*/

	//void DoDS_()
	//{
	//	bool** visited = new bool*[dim];
	//	for (int i = 0; i < dim; i++)
	//	{
	//		visited[i] = new bool[dim];
	//	}
	//	for (int i = 0; i < dim; i++)
	//	{
	//		for (int j = 0; j < dim; j++)
	//		{
	//			visited[i][j] = false;
	//		}
	//	}
	//	int begin = 0;
	//	std::cout << "Введите начальный город: ";
	//	std::cin >> begin;
	//	int end = 0;
	//	std::cout << "Введите конечный город: ";
	//	std::cin >> end;
	//	Routes* params = new Routes();
	//	//DepthSearch_(begin-1, end-1, visited, params, 0);
	//	bool* visited_ = new bool[dim];
	//	for (int i = 0; i < dim; i++)
	//	{
	//		visited_[i] = false;
	//	}
	//	RouteParams temp = RouteParams();
	//	DepthSearch__(begin - 1, end - 1, visited_, params, temp);
	//	for (int i = 0; i < params->len; i++)
	//	{
	//		std::cout << i << ": " << std::endl;
	//		//std::cout << "cost: " << params->routes[i].cost << " len: " << params->routes[i].len << " name: " << params->routes[i].name << std::endl;
	//	}
	//	for (int i = 0; i < dim; i++)
	//	{
	//		delete[] visited[i];
	//	}
	//}

	
	

	//void DepthSearch_(int start, int end, bool**& visited, Routes*& params, int counter = 0)
	//{
	//	if (start == end)
	//	{
	//		return;
	//	}
	//	for (int i = 0; i < this->dim; i++)
	//	{
	//		if (adjacency[start][i] != 0 && !visited[start][i])
	//		{
	//			//Routes* temp = new Routes[params->len+1];
	//			////temp->routes = new RouteParams[params->len + 1];
	//			//for (int i = 0; i < params->len; i++)
	//			//{
	//			//	temp->routes[i] = params->routes[i];
	//			//}
	//			//temp->len = params->len;
	//			///*if (temp->len - 1 >= 0)
	//			//	temp->routes[temp->len] = temp->routes[temp->len - 1];*/
	//			//
	//			//temp->routes[temp->len].cost += adjacency[start][i];
	//			//temp->routes[temp->len].len += 1;
	//			//temp->routes[temp->len].name+=(char)('A' - 1 + i);
	//			//temp->len++;
	//			//delete[] params;
	//			//params = temp;
	//			//visited[start][i] = true;
	//			Routes* temp = new Routes;
	//			temp->routes = new RouteParams[params->len + 1];
	//			for (int i = 0; i < params->len; i++)
	//			{
	//				temp->routes[i] = params->routes[i];
	//			}
	//			temp->len = params->len;
	//			if (temp->len - 1 >= 0)
	//				//temp->routes[temp->len] = temp->routes[temp->len - 1];
	//				temp->routes[temp->len] = temp->routes[counter];
	//			else
	//				temp->routes[temp->len] = RouteParams();
	//			temp->routes[temp->len].cost += adjacency[start][i];
	//			temp->routes[temp->len].len++;
	//			//temp->routes[temp->len].name += (char)('A' + i);
	//			temp->len++;
	//			if(params) delete params;
	//			params = temp;
	//			visited[start][i] = true;
	//			visited[i][start] = true;
	//			counter++;
	//			DepthSearch_(i, end, visited, params, counter);
	//		}
	//	}
	//}

	//Routes* GetNewRoute(int start, int i, Routes*& params, RouteParams& previous)
	//{
	//	Routes* temp = new Routes;
	//	temp->routes = new RouteParams[params->len + 1];
	//	for (int i = 0; i < params->len; i++)
	//	{
	//		temp->routes[i] = params->routes[i];
	//	}
	//	temp->len = params->len;
	//	temp->routes[temp->len] = previous.Copy();
	//	temp->routes[temp->len].cost += adjacency[start][i];
	//	temp->routes[temp->len].len++;
	//	//temp->routes[temp->len].name += (char)('A' + i);
	//	temp->len++;
	//	return temp;
	//}

	/*bool* SaveVisitedPoint(bool*& visited)
	{
		bool* visited_copy = new bool[dim];
		for (int i = 0; i < dim; i++)
		{
			visited_copy[i] = visited[i];
		}
		return visited_copy;
	}*/


	//void DepthSearch__(int start, int end, bool*& visited, Routes*& params, RouteParams previous)
	//{
	//	std::cout << start << std::endl<<std::endl;
	//	PrintList(visited);
	//	Print();
	//	if (start != end)
	//	{

	//		for (int i = 0; i < this->dim; i++)
	//		{
	//			if (adjacency[start][i] != 0 && !visited[start])
	//			{
	//				
	//				/*this->Print();
	//				for (int i = 0; i < dim; i++)
	//				{
	//					std::cout << visited[i] << ' ';
	//				}
	//				
	//				std::cout << std::endl;
	//				std::cout << previous.name << std::endl;*/
	//				//if (temp->len - 1 >= 0)
	//				//	//temp->routes[temp->len] = temp->routes[temp->len - 1];
	//				//	temp->routes[temp->len] = temp->routes[i];
	//				//else
	//				//	temp->routes[temp->len] = RouteParams();
	//				// 
	//				// 
	//				Routes* temp = new Routes;
	//				temp->routes = new RouteParams[params->len + 1];
	//				for (int i = 0; i < params->len; i++)
	//				{
	//					temp->routes[i] = params->routes[i];
	//				}
	//				temp->len = params->len;
	//				temp->routes[temp->len] = previous.Copy();
	//				temp->routes[temp->len].cost += adjacency[start][i];
	//				temp->routes[temp->len].len++;
	//				//temp->routes[temp->len].name += (char)('A' + i);
	//				temp->len++;
	//				//auto temp = GetNewRoute(start, i, params, previous);
	//				if (params) delete params;
	//				params = temp;
	//				visited[start] = true;
	//				adjacency[start][i] = 0;
	//				//auto visited_copy = SaveVisitedPoint(visited);
	//				bool* visited_copy = new bool[dim];
	//				for (int i = 0; i < dim; i++)
	//				{
	//					visited_copy[i] = visited[i];
	//				}
	//				DepthSearch__(i, end, visited, params, temp->routes[temp->len-1]);
	//				delete[] visited;
	//				visited = visited_copy;
	//			}
	//		}
	//	}
	//}

	/*void MinDistance(int fSity, int sSity)
	{
		
	}*/
};

