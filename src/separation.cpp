#include "separation.h"
#include "Vertex.h"

bool hasMoreThanOneLonelyVertex(std::vector<SuperVertex> supervertices)
{
	int amount = 0;


	for(auto sv : supervertices)
	{
		if(sv.vertices.size() == 1)
		{
			amount+=1;
		}

		if(amount > 1)
			return true;
	}

	return false;
}

bool byGreaterCost(std::pair<int, double> a, std::pair<int, double> b)
{
	return a.second > b.second;
}

std::vector<int> getA(int a, std::vector<SuperVertex> vertices, double ** costs, int n, int & rest)
{
	double cost;
	std::vector<int> visitedVertices = {};
	std::vector<bool> vertexWasVisited = std::vector<bool>(vertices.size(), false);
	std::vector<int> A;
	SuperVertex conjuntoA = vertices[a];
	
	std::cout << "Quantidade de vértices: " << vertices.size() << std::endl;
	int lastOne;
	int choosedOne;

	A.push_back(a);
	visitedVertices.push_back(a);
	vertexWasVisited[a] = true;
	while(visitedVertices.size() < vertices.size())
	{
		// std::cout << "Atualizando conjunto A: ";
		// for(auto element : conjuntoA.vertices)
		// 	std::cout << element << " ";
		// std::cout << std::endl;
		std::vector<std::pair<int, double> > vertexDistToA = {};


		/*Calculando distâncias de cada super vértice até o super vértice A*/
		for(size_t i = 0; i < vertices.size(); i++)
		{
			if(!vertexWasVisited[i])
				vertexDistToA.push_back(std::make_pair(i, calculateDistance(conjuntoA, vertices[i],costs)));
		}

		/*Ordenando os super vértices pela distância até A*/
		std::sort(vertexDistToA.begin(), vertexDistToA.end(), byGreaterCost);
		/*Adicionando a A o super vértice mais fortemenete ligado a ele*/
		choosedOne = vertexDistToA[0].first;
		A.push_back(vertexDistToA[0].first); 

		std::cout << "Inserindo vértice " << vertices[vertexDistToA[0].first] << " em A.\n";
		conjuntoA = mergeSuperVertices(conjuntoA, vertices[choosedOne]);
		visitedVertices.push_back(choosedOne);
		vertexWasVisited[choosedOne] = true;
		lastOne = choosedOne;
	}

	rest = lastOne;
	std::cout << "rest: " << rest << std::endl;
	A.pop_back();

	return A;
}

double minCutPhase(std::vector<int> A, SuperVertex rest, std::vector<SuperVertex> supervertices, double ** costs)
{
	double w = 0, dist;
	for(auto v : A)
	{
		dist = calculateDistance(supervertices[v], rest, costs);
		// std::cout << "Calculando distância entre os vértices " << supervertices[v] << " e " << rest  << " = " << dist << std::endl;
		w += calculateDistance(supervertices[v], rest, costs);
	}
	return w;
}

SuperVertex mergeSuperVertices(SuperVertex sp1, SuperVertex sp2)
{
	std::vector<int> union_vertices = sp1.vertices;

	union_vertices.insert(union_vertices.end(), sp2.vertices.begin(), sp2.vertices.end());

	SuperVertex newsp = SuperVertex(union_vertices);

	return newsp;
}

void mergeSuperVertices(std::vector<SuperVertex> &supervertices, int i, int j)
{
	SuperVertex sp1 = supervertices[i];
	SuperVertex sp2 = supervertices[j];


	std::vector<int> union_vertices = sp1.vertices;

	union_vertices.insert(union_vertices.end(), sp2.vertices.begin(), sp2.vertices.end());

	SuperVertex newsp = SuperVertex(union_vertices);

	int first, last;

	if(i > j)
	{
		first = i;
		last = j;
	}else{
		first = j;
		last = i;
	}
	supervertices.erase(supervertices.begin() + first);
	supervertices.erase(supervertices.begin() + last);

	supervertices.push_back(newsp);
}

double calculateDistance(SuperVertex s1, SuperVertex s2, double ** costs)
{
	double dist = 0;

	for(auto x : s1.vertices)
	{
		for(auto y : s2.vertices)
		{
			if(x > y)
			{
				dist += costs[y][x];
			}else{
				dist += costs[x][y];
			}
		}
	}
	return dist;
}


vector <vector<int> > MinCut(double** x, int n)
{
	// std::cout << "Matriz: \n";
	// for(size_t i = 0; i < n; i++)
	// {
	// 	for(size_t j = 0; j < n; j++)
	// 	{
	// 		std::cout << x[i][j] << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	// std::cout.setstate(std::ios_base::failbit);

	/*Vértices não agrupados*/
	Vectord s = {};
	Vectord isolatedVertices;
	std::vector<SuperVertex> supervertices; 

	/*Inicializando conjunto total de vértices*/
	for(size_t i = 0; i < n; i++)
	{
		s.push_back(i);
		supervertices.push_back(SuperVertex(std::vector<int> ({i})));
	}

	isolatedVertices = s;

	/**
	 * "Super vértice" -> Conjunto de vértices unidos
	 * que funcionam como um único vértice (pode conter apenas um vértice).
	*/


	/*
		0. Selecionar um vértice "a" qualquer para dar início ao procedimento
		Defina um conjunto A que contém o vértice "a".
	*/


	/*
		1. Ordene os vértices restantes de acordo com os custos de suas arestas.
		Adicione o vértice com a ligação mais forte, até que só sobre um único
		vértice (este último não é adicionado em A).
	*/

	/**
	 *	2. Calcule o valor de w, que deve ser a soma total dos custos das arestas
	 	que ligam o vértice que sobrou até o conjunto de vértices A.
	*/

	/**
	 *	3. Se o valor de w for menor do que o menor valor registrado, armazene 
	 	o valor de w como sendo o novo menor valor, e guarde o cutsetpool como
		sendo o melhor.
	*/


	/**
	 * 4. Ligar o vértice que sobrou ao último vértice do conjunto A, este será 
	 * um "super vértice".
	*/

	/**
	 * 5. Selecione um novo vértice qualquer, para ser o vértice "a"
	*/

	/**
	 * 6. Repita o passo 1 até que só haja um único vértice
	 * que não é um "Super vértice".
	*/

	/**
	 * O resultado do algoritmo é o cutsetpool cujo valor de w
	 * foi o menor encontrado.
	*/

	//Passo 0
	int a = 1; /*a será sempre o vértice inicial*/
	double w;
	int rest;
	double wmin = std::numeric_limits<double>::infinity();
	/*A fazer: Preencher os supervertices com super vertices contendo apenas um vértice, para todos os vértices*/
	std::vector<int> A;

	std::vector<SuperVertex> bestCutSetPool = supervertices;
	std::cout << "Organização INICIAL dos vértices:\n";
	for(auto v : supervertices)
	{
		std::cout << v << std::endl;
	}
	while(hasMoreThanOneLonelyVertex(supervertices))
	{
		std::cout << "Vértice inicial: " << supervertices[a] << std::endl;

		A = getA(a, supervertices, x, n, rest);

		std::cout << "minCutPhase - inicio\n";
		std::cout << "Rest: " << supervertices[rest] << std::endl;
		w = minCutPhase(A, supervertices[rest], supervertices, x);
		
		std::cout << "minCutPhase - final\n";
		std::cout << "A: ";
		for(auto element : A)
			std::cout << element << " ";
		std::cout << std::endl;
		std::cout << "Fazendo merge dos super vertices " << rest << " e " << A[A.size()-1] << std::endl;
		mergeSuperVertices(supervertices, rest, A[A.size()-1]);
		std::cout << "w = " << w << std::endl;
		std::cout << "Organização dos vértices:\n";
		for(auto v : supervertices)
		{
			std::cout << v << std::endl;
		}
		if(w < wmin)
		{
			wmin = w;
			bestCutSetPool = supervertices;
		}
	}

	// std::cout.clear();
	std::cout << "w = " << wmin << std::endl;
	std::vector<std::vector<int> > result;
	for(auto v : bestCutSetPool)
	{
		result.push_back(v.vertices);
	}

	std::cout << "cutsetpool:";
	for(size_t i = 0; i < result.size(); i++)
	{
		std::cout << "{";
		for(size_t j = 0; j < result[i].size(); j++)
		{
			std::cout << result[i][j] << " ";
		}
		std::cout << "}\n";
	}

	return result;

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

double calculateCutmin(Vectord s, Vectorb includedVertices, double ** costs, int n)
{
	double cutmin = 0;
	for(auto element : s)
	{
		for(size_t i = 0; i < n; i++)
		{
			if(!includedVertices[i])
			{
				int linha, coluna;
				double value;
				if(element > i)
				{
					linha = i;
					coluna = element;
				}else 
				{
					linha = element;
					coluna = i;
				}	

				cutmin += costs[linha][coluna];

			}

			
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
	
	for(size_t start_vertex = 0; start_vertex < n; start_vertex++)
	{
		includedVertices[start_vertex] = 1;
		smin = s0 = s = {};
		s.push_back(start_vertex);
		maxback_values = getMaxBackValues(x_edge, s, includedVertices, n);
		cutval = cutmin = calculateCutmin(s, includedVertices, x_edge, n);
		// std::cout << "Cutmin: " << cutmin << std::endl;
		while(s.size() < n)
		{
			// std::cout << "maxback_values.size(): " << maxback_values.size() << std::endl;

			if(maxback_values.size() == 0)
				break;
			
			
			Vertex v;
			for(auto value : maxback_values)
			{
				if(!includedVertices[value.idx])
				{
					v = value;
					break;
				}
			}

			cutval = cutval + 2 - (2*v.maxBackValue);
			// std::cout << "v.maxBackValue: " << v.maxBackValue << std::endl;
			s.push_back(v.idx);
			includedVertices[v.idx] = 1;
			/*substituir esta chamada de função por uma chamada de atualização*/
			maxback_values = getMaxBackValues(x_edge, s, includedVertices, n);

			// std::cout << "cutval: " << cutval << ", cutmin: " << cutmin << std::endl;
			if(cutval < cutmin)
			{
				// std::cout << "Encontrou um melhor valor de cutmin. Cutmin = " << cutmin << ", cutval = " << cutval << std::endl;
				cutmin = cutval;
				smin = s;
			}
		}
		includedVertices = Vectorb(n, false);
		if(smin.size() < n)
        {
            solutions.push_back(smin);
        }
	}

	return solutions;
}