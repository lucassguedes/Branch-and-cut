#include "separation.h"
#include "Vertex.h"


int selectVertex(vector<bool>& chosed, int n){ //Select

    auto it = find(chosed.begin(), chosed.end(), 0);

    if (it != chosed.end())
    {
        int index = it - chosed.begin();
        chosed[index] = 1;
        return index;
    }
    return -1;
}

void updateBool(vector<bool>&chosed, vector<int> Smin){

    int n = Smin.size();

    for(int i = 0; i < n; i++){
        chosed[Smin[i]] = 1;
    }
}

bool checkChosed(vector<bool> chosed){

    int n = chosed.size();
    int sum = 0;
    for(int i = 0; i < n; i++){
        if(chosed[i]){
            sum++;
        }
    }
    return sum == n;
}



double sumWeights(int v, vector<bool> chosed, double** x, bool inout){ //Sum the weights of v with respect to the vertices are in/out chosed
    //inout == 1 if belongs to s, 0 if not
    double sum = 0;
    int n = chosed.size();
    for(int i = 0; i < n; i++){
        if(chosed[i] == inout){
            if(i < v){
                if(x[i][v] > EPSILON){
                    sum += x[i][v];
                }
                
            }
            else{
                if(x[v][i] > EPSILON){
                    sum += x[v][i];
                }
                
            }
        }
    }

    return sum;
}

int maximumMaxBack(vector<bool>&chosed, double ** x, double& maximumMaxBackValue){

    int n = chosed.size();
    int maxV = -1;
    double maxValue = -numeric_limits<double>::infinity();
    double value;

    for(int i = 0; i < n; i++){
        if(chosed[i] == 0){

            value = sumWeights(i, chosed, x, 1);
            if(value > maxValue){
                maxValue = value;
                maxV = i;
            }
        }
    }
    maximumMaxBackValue = maxValue;
    return maxV;

}


int index2D(vector<vector<int>> V, int element){

    int n = V.size();

    for(int i = 0; i < n; i++){
        for(int j = 0; j < V[i].size(); j++){
            if(V[i][j] == element){
                return i;
            }
        }
    }

    return -1;
}

int index(vector<int> V, int element){

    auto it = find(V.begin(), V.end(), element);

    if (it != V.end())
    {
        int index = it - V.begin();
        return index;
    }
    return -1;
}


int tightVertex(vector<vector<int>>& V, vector<bool> inA, double ** x, int n){

    double sum;
    double maxSum = -numeric_limits<double>::infinity();
    int maxI;
    int Vsize = V.size();
    for(int i = 0; i < Vsize;i++){

        if(!inA[V[i][0]]){

            sum = sumWeights(V[i][0], inA, x, 1);

            if(sum > maxSum){
                maxSum = sum;
                maxI = V[i][0];
            }
        }
    }
    return maxI;
}

vector<vector<int>> identifyEdges(double **x, int n, int a, int b){


    vector<vector<int>> EdgesAB(2, vector<int>(n)); //EDGES[0][i] == edges connected with a, EDGES[1][i] edges connected witb b
    EdgesAB[1].clear();
    for(int i = 0; i < n; i++){
        if(i < b){
            if(x[i][b] > EPSILON){
                EdgesAB[1].push_back(i);
            }
        }
        else if(i > b){
            if(x[b][i] > EPSILON){
                EdgesAB[1].push_back(i);
            }
        }
        
    }

    return EdgesAB;
}

vector<int> getComplement(vector<int> A, int n){

    vector<int> complement;
    for(int i = 0; i < n; i++){
        if(index(A, i) == -1){
            complement.push_back(i);
        }
    }
    return complement;


}

void shrinkGraph(vector<vector<int>>& V, double ** x, int n, int a, int b){

    if(a > b){
        swap(a, b);
    }
    //smaller vertex represents the "supervertex"

    vector<vector<int>> edgesToMerge;

    int indA = index2D(V, a);
    int indB = index2D(V, b);

    int bSize = V[indB].size();
    for(int i = 0; i < bSize; i++){ //updating the V subsets to represents a "supervertex"
        V[indA].push_back(V[indB][0]);
        V[indB].erase(V[indB].begin());
    }
    V.erase(V.begin() + indB);
    
    x[a][b] = 0;

    edgesToMerge = identifyEdges(x, n, a, b); //getting the vertices connected with b

    for(int i = 0; i < edgesToMerge[1].size(); i++){ //updating the x costs
        if(a < edgesToMerge[1][i]){
            if(b < edgesToMerge[1][i]){
                x[a][edgesToMerge[1][i]] += x[b][edgesToMerge[1][i]];
                x[b][edgesToMerge[1][i]] = 0;
            }
            else{
                x[a][edgesToMerge[1][i]] += x[edgesToMerge[1][i]][b];
                x[edgesToMerge[1][i]][b] = 0;
            }
        }
        else{

            if(b < edgesToMerge[1][i]){
                x[edgesToMerge[1][i]][a] += x[b][edgesToMerge[1][i]];
                x[b][edgesToMerge[1][i]] = 0;
            }
            else{
                x[edgesToMerge[1][i]][a] += x[edgesToMerge[1][i]][b];
                x[edgesToMerge[1][i]][b] = 0;
            }

        }
    }

    return;
}

double MinCutPhase(vector<vector<int>>& V, double **x, int n, int a, int& last1, int& last2, vector<int>& set){

    vector<int> A;
    vector<bool> inA(n, 0);
    A.push_back(a);
    inA[a] = 1;
    double value = 0;


    while(A.size() < V.size()){

        int tV = tightVertex(V, inA, x, n); //find the vertex that is not in A with the maximum weight attached to vertex that are in A
        A.push_back(tV);
        inA[tV] = 1;

    }

    int lastVertex = A[A.size() - 1]; //cut of the phase value = sum of weights of last added vertex

    for(int i = 0; i < n; i++){
        if(lastVertex < i){
            if(x[lastVertex][i] > EPSILON){
                value += x[lastVertex][i];
            }
            
        }
        else{
            if(x[i][lastVertex] > EPSILON){
                value += x[i][lastVertex];
            }
            
        }
    }

    last1 = A[A.size() - 1];
    last2 = A[A.size() - 2];
    
    int indSet1 = index2D(V, last1);
    // std::cout << "Last One (A1): ";
    // for(int i = 0; i < V[indSet1].size(); i++) std::cout << V[indSet1][i] << " ";
    // std::cout << std::endl;
    std::cout << "Value (A1): " << value << std::endl;
    if(value < 2 - EPSILON){ //getting the smaller subtour(less constraints) set
        if(V[indSet1].size() <= n/2){
            set = V[indSet1];
            
        }
        else{
            set = getComplement(V[indSet1], n);
        }
    }

    return value;
}

vector<vector<int>> MinCut(double**x, int n){

    srand(time(NULL));
    vector<int> set;
    vector<vector<int>> cutSet;
    vector<vector<int>> V;
    int last1, last2;
    double cutOfThePhase;

    // int a = rand() % n;
    int a = 0;

    // std::cout << "Matrix (A1): \n";
    // for(int i = 0; i < n; i++)
    // {
    //     for(int j = 0; j < n; j++)
    //     {
    //         double value = (j >= i+1) ? x[i][j] : 0;
    //         printf("%2.0f ", value);
    //     }
    //     printf("\n");
    // }

    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(x[i][j] < EPSILON){
                x[i][j] = 0;
            }
        }
    }

    for(int i = 0; i < n; i++){
        V.push_back({i});
    }

    while(1){
        
        cutOfThePhase = MinCutPhase(V, x, n, a, last1, last2, set);
        if(!set.empty()){
            cutSet.push_back(set);
            set.clear();
        }
        if(V.size() == 2){
            break;
        }
        shrinkGraph(V, x, n, last1, last2);

    }

    return cutSet;
}



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
		}else if(i != vertex){
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