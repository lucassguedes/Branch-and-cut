#include "separation.h"
#include "Vertex.h"

bool byGreaterCost(std::pair<int, double> a, std::pair<int, double> b)
{
	return a.second > b.second;
}


void updateMaxBackValues(double ** costs, std::vector<double> &maxBackValues, int newVertex, std::vector<bool> &includedVertices, int n)
{
	for(int t = 0; t < n; t++)
	{
		if(newVertex > t)
		{
			maxBackValues[t] += costs[t][newVertex];
		}else{
			maxBackValues[t] += costs[newVertex][t];
		}
	}
}


std::pair<int , double> getGreaterMaxBack(double ** costs, std::vector<int> &s, std::vector<bool> includedVertices, int n)
{
	double greaterMaxBack = -std::numeric_limits<double>::infinity();
	double vertex = -1;
	const size_t s_size = s.size();

	for(size_t i = 0; i < n; i++) /*i percorrerá todos os possíveis vértices*/
	{
		double maxBack = 0;	

		for(size_t j = 0; j < s_size; j++)/*j percorrerá as posições de s, que contém os vértices da solução*/
		{
			/*Aqui é feita a atualização dos valores de max-back, dos vértices que estão
			  fora da solução relacionados com os vértices que estão dentro.*/
			if(!includedVertices[i])
			{
				if(s[j] > i)
				{
					maxBack += costs[i][s[j]];
				}
				else if(i > s[j])
				{
					maxBack += costs[s[j]][i];
				}
			}
		}

		if(maxBack > greaterMaxBack)
		{
			greaterMaxBack = maxBack;
			vertex = i;
		}
	}

	return std::make_pair(vertex, greaterMaxBack);
}

VertexVector getMaxBackValues(double ** costs, std::vector<int> &s, std::vector<bool> includedVertices, int n){
	VertexVector maxback_values;
	const size_t s_size = s.size();
	Vertex v;
	for(size_t i = 0; i < n; i++) /*i percorrerá todos os possíveis vértices*/
	{
		v = Vertex(i, 0);
		for(size_t j = 0; j < s_size; j++)/*j percorrerá as posições de s, que contém os vértices da solução*/
		{
			
			/*Aqui é feita a atualização dos valores de max-back, dos vértices que estão
			  fora da solução relacionados com os vértices que estão dentro.*/
			if(!includedVertices[i])
			{
				if(s[j] > i)
				{
					v.maxBackValue += costs[i][s[j]];
				}
				else if(i > s[j])
				{
					v.maxBackValue += costs[s[j]][i];
				}
			}
		}
		// if(v.maxBackValue >= 1)
		maxback_values.push_back(v);
	}

	std::sort(maxback_values.begin(), maxback_values.end(), byGreaterMaxBack);

	return maxback_values;
}

double calculateCutmin(int vertex, Vectorb includedVertices, double ** costs, int n)
{
	double cutmin = 0;
	for(size_t i = 0; i < n; i++)
	{
		if(i < vertex)
		{
			cutmin += costs[i][vertex];
		}else if(vertex == i)
		{

		}else{
			cutmin += costs[vertex][i];
		}
	}
	return cutmin;
}



vector <vector<int> >  MaxBack(double **x_edge, int n)
{
	/*Max-back heuristic*/
	Vectord smin, s, s0;
	VertexVector maxback_values;
	Vectorb includedVertices = Vectorb(n, false); /*Para cada s, iremos registrar os vértices inclusos aqui*/
	Matrixd solutions;

	double cutmin, cutval;
	cutmin = 0; /*O valor inicial de cutmin não é igual a zero, consulte o pdf*/
	Vectord visited_vertices = {};

	std::pair<int, double> bestMaxBack;

	Vectorb verticesInSol = Vectorb(n, false);
	
	for(size_t start_vertex = 0; start_vertex < n; start_vertex++)
	{

		if(verticesInSol[start_vertex])
			continue;

		includedVertices[start_vertex] = 1;
		verticesInSol[start_vertex] = 1;
		smin = s0 = s = {};
		s.push_back(start_vertex);
		// maxback_values = getMaxBackValues(x_edge, s, includedVertices, n);
		bestMaxBack = getGreaterMaxBack(x_edge, s, includedVertices, n);
		cutval = cutmin = calculateCutmin(start_vertex, includedVertices, x_edge, n);
		// std::cout << "Cutmin: " << cutmin << std::endl;
		while(s.size() < n)
		{
			// std::cout << "maxback_values.size(): " << maxback_values.size() << std::endl;

			if(bestMaxBack.first == -1)
				continue;
			
			
			int vertex = bestMaxBack.first;
			double mbVal = bestMaxBack.second;
			

			cutval = cutval + 2 - (2*mbVal);
			// std::cout << "v.maxBackValue: " << v.maxBackValue << std::endl;
			s.push_back(vertex);
			includedVertices[vertex] = 1;
			/*substituir esta chamada de função por uma chamada de atualização*/
			bestMaxBack = getGreaterMaxBack(x_edge, s, includedVertices, n);

			// std::cout << "cutval: " << cutval << ", cutmin: " << cutmin << std::endl;
			if(cutval < cutmin)
			{
				// std::cout << "Encontrou um melhor valor de cutmin. Cutmin = " << cutmin << ", cutval = " << cutval << std::endl;
				cutmin = cutval;
				smin = s;
			}
		}
		verticesInSol = Vectorb(n, false);
		includedVertices = Vectorb(n, false);

		/*Determinando quais vértices estão na solução (o que conta é Smin)*/
		for(auto v : smin)
		{
			verticesInSol[v] = 1;
		}

		if(smin.size() < n)
        {
            solutions.push_back(smin);
        }
	}

	return solutions;
}