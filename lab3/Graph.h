#pragma once
#include <iostream>
#include <iomanip>
#include <C:\Users\Игорь\Desktop\учеба\LabRab\ЛР ВП 2 Сем\1 ЛР\LR1\LR1\myException.h>
#include "C:\Users\Игорь\Desktop\учеба\LabRab\ЛР ВП 2 Сем\1 ЛР\LR1\LR1\myVector.h"
#include "Exceptions.h"
#include <fstream>
#include <queue>
#include <algorithm>

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

bool vectorBool(PIA::myVector<bool> v)
{
	for (int i = 0; i < v.getSize(); i++)
	{
		if (v[i] == false) return false;
	}
	return true;
}
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

using namespace PIA;
class Graph
{
private:
	static const int infinity = 900000;
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

	int** AdjaencyCopy() const
	{
		int** copy = new int* [this->dim];
		for (int i = 0; i < dim; i++)
		{
			this->adjacency[i] = new int[this->dim];
		}
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				copy[i][j] = this->adjacency[i][j];
			}
		}
		return copy;
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

	//PIA::myVector<int> BFS__(const Graph& gr, int beg, int end)
	//{
	//	myVector<int> q = myVector<int>();
	//	myVector<bool> used = myVector<bool>(gr.dim, false);
	//	//for (int i = 0; i < used.getSize(); i++)
	//	//{
	//	//	used.pushBack(false);
	//	//}
	//	myVector<int> d = myVector<int>(gr.dim, 0);
	//	//for (int i = 0; i < d.getSize(); i++)
	//	//{
	//	//	d.pushBack(0);
	//	//}
	//	myVector<int> p = myVector<int>(gr.dim, 0);
	//	//for (int i = 0; i < p.getSize(); i++)
	//	//{
	//	//	p.pushBack(0);
	//	//}
	//	q.pushFront(beg);
	//	used[beg] = true;
	//	p[beg] = -1;
	//	while (!q.empty())
	//	{
	//		int v = 0;
	//		if (!q.empty()) v = q.popFront();
	//		for (size_t i = 0; i < gr.dim; i++)
	//		{
	//			int to = gr.adjacency[v][i];
	//			if (!used[i] && to != 0)
	//			{
	//				used[i] = true;
	//				q.pushBack(i);
	//				d[i] = d[v] + 1;
	//				p[i] = v;
	//			}
	//		}
	//	}
	//	
	//	if (!used[end]) return myVector<int>();
	//	else
	//	{
	//		myVector<int> path;
	//		for (int v = end; v != -1; v = p[v])
	//		{
	//			path.pushBack(p[v]);
	//		}
	//		path.reverse();
	//		return path;
	//	}
	//}
	//std::vector<int> BFS__(const Graph& gr, int beg, int end)
	//{
	//	std::queue<int> q = std::queue<int>();
	//	std::vector<bool> used = std::vector<bool>(gr.dim, false);
	//	//for (int i = 0; i < used.getSize(); i++)
	//	//{
	//	//	used.pushBack(false);
	//	//}
	//	std::vector<int> d = std::vector<int>(gr.dim, 0);
	//	//for (int i = 0; i < d.getSize(); i++)
	//	//{
	//	//	d.pushBack(0);
	//	//}
	//	std::vector<int> p = std::vector<int>(gr.dim, 0);
	//	//for (int i = 0; i < p.getSize(); i++)
	//	//{
	//	//	p.pushBack(0);
	//	//}
	//	q.push(beg);
	//	used[beg] = true;
	//	p[beg] = -1;
	//	while (!q.empty())
	//	{
	//		int v = q.front();
	//		q.pop();
	//		for (size_t i = 0; i < gr.dim; i++)
	//		{
	//			int to = gr.adjacency[v][i];
	//			if (to != 0 && !used[i])
	//			{
	//				used[i] = true;
	//				q.push(i);
	//				d[i] = d[v] + 1;
	//				p[i] = v;
	//			}
	//		}
	//	}

	//	if (!used[end]) return std::vector<int>();
	//	else
	//	{
	//		std::vector<int> path;
	//		for (int v = end; v != -1; v = p[v])
	//		{
	//			path.push_back(p[v]);
	//		}
	//		std::reverse(path.begin(), path.end());
	//		return path;
	//	}
	//}

	/*std::vector<int> BFS__(const Graph& gr, int beg, int end)
	{
		if (beg == end) return std::vector<int>();
		std::vector<bool> visited = std::vector<bool>(gr.dim, false);
		std::queue<int> q = std::queue<int>();
		visited[beg] = true;
		q.push(beg);
		std::vector<int> path = std::vector<int>();
		path.push_back(beg);
		while (!q.empty())
		{
			int s = q.front();
			q.pop();
			for (auto i = 0; i < gr.dim; i++)
			{
				if (!visited[i] && gr.adjacency[s][i] != 0)
				{
					if (i == end)
					{
						path.push_back(i);
						return path;
					}
					else
					{
						visited[i] = true;
						path.push_back(i);
						q.push(i);
					}
				}
			}
			auto t = std::find(path.begin(), path.end(), );
		}
		if (path.empty()) return std::vector<int>();
	}*/
	//std::vector<int> BFS__(const Graph& gr, int beg, int end)
	//{
	//	if (beg == end) return std::vector<int>();
	//	std::vector<bool> visited = std::vector<bool>(gr.dim, false);
	//	std::queue<int> q = std::queue<int>();
	//	visited[beg] = true;
	//	q.push(beg);
	//	std::vector<int> path = std::vector<int>();
	//	path.push_back(beg);
	//	while (!q.empty())
	//	{
	//		int p = q.front();
	//		q.pop();
	//		path.push_back(p);
	//		//path.pop_back();
	//		//path.push_back(p);
	//		if (p == end)
	//		{
	//			return path;
	//		}
	//		for (int i = 0; i < gr.dim; i++)
	//		{
	//			if (!visited[i] && gr.adjacency[p][i] != 0)
	//			{
	//				visited[i] = true;
	//				q.push(i);
	//			}
	//		}
	//	}
	//}
	myVector<int> __BFS__(const Graph& gr, int beg, int end)
	{
		myVector<int> q;
		myVector<bool> visited = myVector<bool>(gr.dim, false);
		myVector<int> d = myVector<int>(gr.dim, 0);
		myVector<int> p = myVector<int>(gr.dim, 0);
		q.pushFront(beg);
		visited[beg] = true;
		p[beg] = -1;
		while (!q.empty())
		{
			int v = q.popBack();
			// q.pop();
			for (int i = 0; i < gr.dim; i++)
			{
				if (gr.adjacency[v][i] != 0 && !visited[i])
				{
					visited[i] = true;
					q.pushFront(i);
					d[i] = d[v] + 1;
					p[i] = v;
				}
			}
		}
		myVector<int>path = myVector<int>();
		if (p[end] == 0) return path;
		for (int v = end; v != -1; v = p[v])
		{
			path.pushBack(v);
		}
		
		//std::reverse(path.begin(), path.end());
		//std::reverse(p.begin(), p.end());
		path.reverse();
		return myVector<int>(path);
	}

	std::vector<int> BFS__(const Graph& gr, int beg, int end)
	{
		std::queue<int> q;
		std::vector<bool> visited = std::vector<bool>(gr.dim, false);
		std::vector<int> d = std::vector<int>(gr.dim, 0);
		std::vector<int> p = std::vector<int>(gr.dim, 0);
		q.push(beg);
		visited[beg] = true;
		p[beg] = -1;
		while (!q.empty())
		{
			int v = q.front();
			q.pop();
			for (int i = 0; i < gr.dim; i++)
			{
				if (gr.adjacency[v][i] != 0 && !visited[i])
				{
					visited[i] = true;
					q.push(i);
					d[i] = d[v] + 1;
					p[i] = v;
				}
			}
		}
		std::vector<int>path = std::vector<int>();
		if (p[end] == 0) return path;
		for (int v = end; v != -1; v = p[v])
		{
			path.push_back(v);
		}
		std::reverse(path.begin(), path.end());
		//std::reverse(p.begin(), p.end());
		return path;
	}

	void AddVertexAuto(int prevCtr, int* prev)
	{
		int** temp = new int* [this->dim + 1];
		for (int i = 0; i < this->dim + 1; i++)
		{
			temp[i] = new int[this->dim + 1];
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
		for (int i = 0; i < this->dim; i++)
		{
			temp[i][this->dim-1] = 0;
		}
		for (int i = 0; i < this->dim; i++)
		{
			temp[this->dim-1][i] = 0;
		}
		for (int i = 0; i<prevCtr; i++)
		{
			temp[prev[i]][this->dim - 1] = 999999;
		}
		//for (int i = 0; i < dim - 1; i++)
		//{
		//	std::cout << "Введите вес между городами " << (char)(dim - 1 + 'A') << " и " << (char)(i + 'A') << ": ";
		//	int val = 0;
		//	while (!(std::cin >> val))
		//	{
		//		std::cin.clear();
		//		std::cin.ignore(INT_MAX, '\n');
		//		std::cout << "\nОшибка! Введено некорректное значение!\n Попробуйте снова.\n";
		//	}
		//	temp[dim - 1][i] = val;
		//	temp[i][dim - 1] = val;
		//	//temp[dim][i] = val;
		//	//temp[i][dim] = val;
		//}
		temp[dim - 1][dim - 1] = 0;

		if (this->adjacency)
		{
			for (int i = 0; i < this->dim - 1; i++)
			{
				if (this->adjacency[i]) delete[] this->adjacency[i];
			}
		}
		this->adjacency = temp;
	}


					//Graph BFSFloydWarshell(int source, int drainCtr, int* drains)
					//{
					//	try
					//	{
					//		Graph temp = *this;
					//		temp.AddVertexAuto(drainCtr, drains);
					//		std::cout << "Исходная сеть: " << std::endl;
					//		temp.Print();
					//		int dest = temp.GetDim() - 1;
					//		std::vector<int> path = std::vector<int>(1, 0);
					//		//path.push_back(0);
					//		int maxStream = 0;
					//		int ctr = 1;
					//		while (!path.empty())
					//		{
					//			path.clear();
					//			path = BFS__(temp, source, dest);
					//			if (path.size() <= 1) break;
					//			//path.erase(path.cbegin(), path.cbegin()+1);
					//			path.erase(path.end() - 1, path.end());
					//			path.push_back(dest);
					//			int minStr = 99999;
					//			for (int i = 0; i < path.size() - 1; i++)
					//			{
					//				int pathcost = temp.adjacency[path[i]][path[i + 1]];
					//				if (minStr > temp.adjacency[path[i]][path[i + 1]] && temp.adjacency[path[i]][path[i + 1]] != 0)
					//					//minStr < temp.adjacency[path[i]][path[i + 1]] ? minStr : temp.adjacency[path[i]][path[i + 1]];
					//					minStr = temp.adjacency[path[i]][path[i + 1]];
					//			}
					//			maxStream += minStr;
					//			std::cout << std::endl << "Шаг " << ctr << std::endl;
					//			for (int i = 0; i < path.size() - 1; i++)
					//			{
					//				temp.adjacency[path[i]][path[i + 1]] -= minStr;
					//				temp.adjacency[path[i + 1]][path[i]] += minStr;
					//			}
					//			std::cout << "Путь из истока в сток: ";
					//			for (auto& e : path) std::cout << e;
					//			std::cout << std::endl << "Макс. поток через путь: ";
					//			std::cout << minStr << std::endl;
					//			std::cout << "Остаточная сеть: " << std::endl;
					//			temp.Print();
					//			ctr++;
					//		}
					//		std::cout << "Максимальный поток = " << maxStream << std::endl;
					//		//Graph min = *this;
					//		//int maxStream = 0;
					//		//PIA::myVector<bool> visited = PIA::myVector<bool>();

					//		//for (int k = 0; k < min.dim; k++)
					//		//{
					//		//	for (int i = 0; i < min.dim; i++)
					//		//	{
					//		//		for (int j = 0; j < min.dim; j++)
					//		//		{
					//		//			min.adjacency[i][j] = std::min(min.adjacency[i][j], min.adjacency[i][k] + min.adjacency[k][j]);
					//		//			/*if (min.adjacency[i][j] > min.adjacency[i][k] + min.adjacency[k][j])
					//		//				min.adjacency[i][j] = min.adjacency[i][k] + min.adjacency[k][j];*/
					//		//		}
					//		//	}
					//		//}
					//		//min.Print();
					//		/*int maxStream = 0;
					//		for (int i = 0; i < drainCtr; i++)
					//		{
					//			maxStream += min.adjacency[source][drains[i]];
					//		}*/
					//		//std::cout << "Максимальный поток из " << source + 1 << " в стоки равен: " << maxStream << std::endl;
					//	}
					//	catch (...)
					//	{
					//		throw new BaseE("Error occured during FloydWarshell algorithm process");
					//		return Graph();
					//	}
					//}
	Graph BFSFloydWarshell(int source, int drainCtr, int* drains)
	{
		try
		{
			Graph temp = *this;
			temp.AddVertexAuto(drainCtr, drains);
			std::cout << "Исходная сеть: " << std::endl;
			temp.Print();
			int dest = temp.GetDim() - 1;
			myVector<int> path = myVector<int>(1, 0);
			//path.push_back(0);
			int maxStream = 0;
			int ctr = 1;
			while (!path.empty())
			{
				path.clear();
				path = __BFS__(temp, source, dest);
				if (path.getSize() <= 1) break;
				//path.erase(path.cbegin(), path.cbegin()+1);
				//path.erase(path.end()-1, path.end());
				path.popBack();
				path.pushBack(dest);
				int minStr = 99999;
				for (int i = 0; i < path.getSize() - 1; i++)
				{
					int pathcost = temp.adjacency[path[i]][path[i + 1]];
					if (minStr > temp.adjacency[path[i]][path[i + 1]] && temp.adjacency[path[i]][path[i + 1]] != 0)
						//minStr < temp.adjacency[path[i]][path[i + 1]] ? minStr : temp.adjacency[path[i]][path[i + 1]];
						minStr = temp.adjacency[path[i]][path[i + 1]];
				}
				maxStream += minStr;
				std::cout << std::endl << "Шаг " << ctr << std::endl;
				for (int i = 0; i < path.getSize() - 1; i++)
				{
					temp.adjacency[path[i]][path[i + 1]] -= minStr;
					temp.adjacency[path[i + 1]][path[i]] += minStr;
				}
				std::cout << "Путь из истока в сток: ";
				for (auto& e : path) std::cout << e;
				std::cout << std::endl << "Макс. поток через путь: ";
				std::cout <<  minStr << std::endl;
				std::cout << "Остаточная сеть: " << std::endl;
				temp.Print();
				ctr++;
			}
			std::cout << "Максимальный поток = " << maxStream << std::endl;
			//Graph min = *this;
			//int maxStream = 0;
			//PIA::myVector<bool> visited = PIA::myVector<bool>();

			//for (int k = 0; k < min.dim; k++)
			//{
			//	for (int i = 0; i < min.dim; i++)
			//	{
			//		for (int j = 0; j < min.dim; j++)
			//		{
			//			min.adjacency[i][j] = std::min(min.adjacency[i][j], min.adjacency[i][k] + min.adjacency[k][j]);
			//			/*if (min.adjacency[i][j] > min.adjacency[i][k] + min.adjacency[k][j])
			//				min.adjacency[i][j] = min.adjacency[i][k] + min.adjacency[k][j];*/
			//		}
			//	}
			//}
			//min.Print();
			/*int maxStream = 0;
			for (int i = 0; i < drainCtr; i++)
			{
				maxStream += min.adjacency[source][drains[i]];
			}*/
			//std::cout << "Максимальный поток из " << source + 1 << " в стоки равен: " << maxStream << std::endl;
		}
		catch (...)
		{
			throw new BaseE("Error occured during FloydWarshell algorithm process");
			return Graph();
		}
	}
	//Graph BFSFloydWarshell(int source, int drainCtr, int* drains) 
	//{
	//	try
	//	{
	//		Graph temp = *this;
	//		temp.AddVertexAuto(drainCtr, drains);
	//		temp.Print();
	//		int dest = temp.GetDim() - 1;
	//		myVector<int> path = myVector<int>();
	//		path.pushBack(0);
	//		int maxStream = 0;
	//		while (!path.empty())
	//		{
	//			path.clear();
	//			path = BFS__(temp, source, dest).empty();
	//			int minStr = 99999;
	//			for (int i = 0; i < path.getSize() - 1; i++)
	//			{
	//				if(minStr < temp.adjacency[path[i]][path[i + 1]] && temp.adjacency[path[i]][path[i + 1]]!=0)
	//				//minStr < temp.adjacency[path[i]][path[i + 1]] ? minStr : temp.adjacency[path[i]][path[i + 1]];
	//					minStr = temp.adjacency[path[i]][path[i + 1]];
	//			}
	//			maxStream += minStr;
	//			for (int i = 0; i < path.getSize() - 1; i++)
	//			{
	//				temp.adjacency[path[i]][path[i + 1]] -= minStr;
	//				temp.adjacency[path[i + 1]][path[i]] += minStr;
	//			}
	//			temp.Print();
	//		}
	//		std::cout << "Максимальный поток = " << maxStream << std::endl;
	//		//Graph min = *this;
	//		//int maxStream = 0;
	//		//PIA::myVector<bool> visited = PIA::myVector<bool>();
	//		
	//		//for (int k = 0; k < min.dim; k++)
	//		//{
	//		//	for (int i = 0; i < min.dim; i++)
	//		//	{
	//		//		for (int j = 0; j < min.dim; j++)
	//		//		{
	//		//			min.adjacency[i][j] = std::min(min.adjacency[i][j], min.adjacency[i][k] + min.adjacency[k][j]);
	//		//			/*if (min.adjacency[i][j] > min.adjacency[i][k] + min.adjacency[k][j])
	//		//				min.adjacency[i][j] = min.adjacency[i][k] + min.adjacency[k][j];*/
	//		//		}
	//		//	}
	//		//}
	//		//min.Print();
	//		/*int maxStream = 0;
	//		for (int i = 0; i < drainCtr; i++)
	//		{
	//			maxStream += min.adjacency[source][drains[i]];
	//		}*/
	//		//std::cout << "Максимальный поток из " << source + 1 << " в стоки равен: " << maxStream << std::endl;
	//	}
	//	catch (...)
	//	{
	//		throw new BaseE("Error occured during FloydWarshell algorithm process");
	//		return Graph();
	//	}
	//}
	bool Empty()
	{
		if (this->dim == 0) return true;
		else return false;
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
					std::cout << std::setw(7) << std::resetiosflags(std::ios::left) << 'г';
				}
				else if (i == 0 || j == 0)
				{
					std::cout << std::setw(7) << std::resetiosflags(std::ios::left) << (- 1 + i + j);//(char)('A' - 1 + i + j);
				}
				else
				{
					if(adjacency[i-1][j-1] < infinity)
						std::cout << std::setw(7) << std::resetiosflags(std::ios::left) << adjacency[i-1][j-1];
					else 
						std::cout << std::setw(7) << std::resetiosflags(std::ios::left) << "inf";
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
	Graph(const Graph& other)
	{
		this->dim = other.dim;
		if (this->adjacency)
		{
			for (int i = 0; i < dim; i++)
			{
				if (adjacency[i]) delete[] adjacency[i];
			}
		}
		if (other.adjacency)
		{
			this->adjacency = new int* [dim];
			for (int i = 0; i < this->dim; i++)
			{
				this->adjacency[i] = new int[dim];
			}
			for (int i = 0; i < dim; i++)
			{
				for (int j = 0; j < dim; j++)
				{
					this->adjacency[i][j] = other.adjacency[i][j];
				}
			}
		}
		else this->adjacency = nullptr;
	}

	Graph(Graph&& other)
	{
		this->dim = other.dim;
		if (this->adjacency)
		{
			for (int i = 0; i < dim; i++)
			{
				if (adjacency[i]) delete[] adjacency[i];
			}
		}
		if (other.adjacency)
		{
			this->adjacency = new int* [dim];
			for (int i = 0; i < this->dim; i++)
			{
				this->adjacency[i] = new int[dim];
			}
			for (int i = 0; i < dim; i++)
			{
				for (int j = 0; j < dim; j++)
				{
					this->adjacency[i][j] = other.adjacency[i][j];
				}
			}
		}
		else this->adjacency = nullptr;
		other.dim = 0;
		for (int i = 0; i < other.dim; i++)
		{
			delete[] other.adjacency[i];
		}
		other.adjacency = nullptr;
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

