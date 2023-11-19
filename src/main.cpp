#include "dataFunction.h"
#include "auxFunctions.h"
#include "separation.h"
#include "MyLazyCallback.h"
#include "MyCutCallback.h"
#include "MyBranchCallback.h"
#include <stdio.h>
#include <iostream>
#include <ilcplex/ilocplex.h>
#include "mincut.hpp"

void STSP_Solve(Data *data, string instanceName, double ub)
{   
    IloEnv env;
    IloModel model(env);
    IloCplex cplex(model);

    env.setName("Branch and Cut");
    model.setName("Symmetrical Traveling Salesman Problem");

    int dimension = data->getDimension();

    /********** Creating variable x for each edge **********/
    IloArray <IloBoolVarArray> x(env, dimension);

    for (int i = 0; i < dimension; i++) {
		IloBoolVarArray array(env, dimension);
		x[i] = array;
	}
    /*******************************************************/

    /*********** Adding x variables to the model ***********/
    char var[100];
    for (int i = 0; i < dimension; i++){
        for (int j = i + 1; j < dimension; j++){
            sprintf(var, "X(%d,%d)", i, j);
			x[i][j].setName(var);
			model.add(x[i][j]);
        }
    }
    /******************************************************/
    
    /**************** Objective Function ******************/
    IloExpr obj(env);
    for (int i = 0; i < dimension; i++) {	
		for (int j = i + 1; j < dimension; j++) {
			obj += data->getDistance(i, j)*x[i][j];
		}
	}
    model.add(IloMinimize(env, obj));
    /******************************************************/
    
    /******************** Constraints *********************/
    IloRange r;
    char name[100];

    for (int i = 0; i < dimension; i++){
        IloExpr sumX(env);
        for (int j = 0; j < dimension; j++){
            if (j < i) {
				sumX += x[j][i];
			}
            if (i < j){
                sumX += x[i][j];
            }
        }
        r = (sumX == 2);
        sprintf(name, "c_%d", i);
		r.setName(name);
		model.add(r);
    }


    
    /******************************************************/

    /****************** Solve the model *******************/
    IloCplex STSP(model);
    STSP.setParam(IloCplex::TiLim, 2*60*60);
    STSP.setParam(IloCplex::Threads, 1);
    STSP.setParam(IloCplex::Param::MIP::Tolerances::MIPGap, 1e-08);
    STSP.setParam(IloCplex::CutUp, ub);
    //STSP.exportModel("stsp.lp");

    double timeBefore, timeAfter;

    const IloArray<IloBoolVarArray>& x_ref = x;

    /********** Creating Branch Callback Object ***********/
    MyBranchCallback* branchCbk = new (env) MyBranchCallback(env);
    STSP.use(branchCbk);
    /******************************************************/

    /************ Creating Cut Callback Object ************/
    MyCutCallback* cutCbk = new (env) MyCutCallback(env, x_ref, dimension); 
	STSP.use(cutCbk);
    /******************************************************/

    /************ Creating Lazy Callback Object ***********/
    MyLazyCallback* lazyCbk = new (env) MyLazyCallback(env, x_ref, dimension);
    STSP.use(lazyCbk);
    /******************************************************/

    try{ 
	    timeBefore = STSP.getTime();
	    STSP.solve();
	    timeAfter = STSP.getTime();
    }
    catch(IloException& e){
        std::cout << e;
    }

    
    // cplex.exportModel("model.lp");

    printResults(STSP, instanceName, timeAfter-timeBefore);
	printSolution(STSP, x, dimension);
	//printResultsToFile(STSP, instanceName, timeAfter-timeBefore);
    /******************************************************/

    /**************** Cleaning the memory *****************/

    delete branchCbk;
    delete cutCbk;
    delete lazyCbk;
    env.end();
    /******************************************************/
}


// double calculateCutmin(Vectord s, Vectorb includedVertices, Matrixd costs, int n)
// {
// 	double cutmin = 0;
// 	for(auto element : s)
// 	{
// 		for(size_t i = 0; i < n; i++)
// 		{
// 			if(!includedVertices[i])
// 			{
// 				int linha, coluna;
// 				double value;
// 				if(element > i)
// 				{
// 					linha = i;
// 					coluna = element;
// 				}else 
// 				{
// 					linha = element;
// 					coluna = i;
// 				}	

				

// 				if(isnan(costs[linha][coluna]))
// 				{
// 					// std::cout << "linha: " << linha << ", coluna: " << coluna << std::endl;
// 					// std::cout << "Inserindo isto daqui: " << value << std::endl;	
// 				}else
// 				{
// 					cutmin += costs[linha][coluna];
// 				}
// 			}

			
// 		}
// 	}
// 	return cutmin;
// }

// VertexVector getMaxBackValues(Matrixd costs, std::vector<int> &s, std::vector<bool> includedVertices, int n)
// {
// 	VertexVector maxback_values;
// 	const size_t s_size = s.size();
// 	Vertex v;
// 	for(size_t i = 0; i < n; i++) /*i percorrerá todos os possíveis vértices*/
// 	{
//         v = Vertex(i, 0);
// 		for(size_t j = 0; j < s_size; j++)/*j percorrerá as posições de s, que contém os vértices da solução*/
// 		{
			
// 			/*Aqui é feita a atualização dos valores de max-back, dos vértices que estão
// 			  fora da solução relacionados com os vértices que estão dentro.*/
// 			if(!includedVertices[i])
// 			{
// 				if(s[j] > i)
// 				{
// 					v.maxBackValue += costs[i][s[j]];
// 				}
// 				else if(i > s[j])
// 				{
// 					v.maxBackValue += costs[s[j]][i];
// 				}
// 			}
// 		}
//         if(v.maxBackValue >= 1)
//             maxback_values.push_back(v);
// 	}

// 	std::sort(maxback_values.begin(), maxback_values.end(), byGreaterMaxBack);

// 	return maxback_values;
// }

// Matrixd maxBack(Matrixd x_edge, int n)
// {
// 	/*Max-back heuristic*/
// 	Vectord smin, s, s0;
// 	VertexVector maxback_values;
// 	Vectorb includedVertices = Vectorb(n, false); /*Para cada s, iremos registrar os vértices inclusos aqui*/
// 	Matrixd solutions;

// 	double cutmin, cutval;
// 	int v;
// 	cutmin = 0; /*O valor inicial de cutmin não é igual a zero, consulte o pdf*/
// 	Vectord visited_vertices = {};
	
// 	for(size_t start_vertex = 0; start_vertex < n; start_vertex++)
// 	{
// 		includedVertices[start_vertex] = 1;
// 		smin = s0 = s = {};
// 		s.push_back(start_vertex);
// 		maxback_values = getMaxBackValues(x_edge, s, includedVertices, n);
// 		cutval = cutmin = calculateCutmin(s, includedVertices, x_edge, n);
// 		std::cout << "Cutmin: " << cutmin << std::endl;
// 		while(s.size() < n)
// 		{
// 			std::cout << "maxback_values.size(): " << maxback_values.size() << std::endl;

// 			if(maxback_values.size() == 0)
// 				break;
			
			
// 			Vertex v;
// 			for(auto value : maxback_values)
// 			{
// 				if(!includedVertices[value.idx])
// 				{
// 					v = value;
// 					break;
// 				}
// 			}

// 			cutval = cutval + 2 - (2*v.maxBackValue);
// 			std::cout << "v.maxBackValue: " << v.maxBackValue << std::endl;
// 			s.push_back(v.idx);
// 			includedVertices[v.idx] = 1;
// 			/*substituir esta chamada de função por uma chamada de atualização*/
// 			maxback_values = getMaxBackValues(x_edge, s, includedVertices, n);

// 			std::cout << "cutval: " << cutval << ", cutmin: " << cutmin << std::endl;
// 			if(cutval < cutmin)
// 			{
// 				std::cout << "Encontrou um melhor valor de cutmin. Cutmin = " << cutmin << ", cutval = " << cutval << std::endl;
// 				cutmin = cutval;
// 				smin = s;
// 			}
// 		}
// 		includedVertices = Vectorb(n, false);
// 		solutions.push_back(smin);
// 	}

// 	return solutions;
// }

int main(int argc, char** argv)
{
    double ub = numeric_limits<double>::max();

    if(argc < 2){
        printf("Correct command: ./bc data/instance\n");
        return 0;
    }
    else if(argc > 2){
        ub = stod(argv[2]);
    }

    Data * data = new Data(argc, argv[1]);

    // Matrixd x_edge =      {{0, 1, 1, 0, 0, 0},
    //                        {1, 0, 1, 0, 0, 0},
    //                        {1, 1, 0, 0, 0, 0},
    //                        {0, 0, 0, 0, 1, 1},
    //                        {0, 0, 0, 1, 0, 1},
    //                        {0, 0, 0, 1, 1, 0}};

    // Matrixd mincut = maxBack(x_edge, 6);

    // std::cout << "Min cut:\n";
    // for(auto line : mincut)
    // {
    //     for(auto element : line)
    //     {
    //         std::cout << element << " "; 
    //     }
    //     std::cout << std::endl;
    // }

    // std::vector<SuperVertex> supervertices = {};


    // /*Testes para a burma 14*/
    // supervertices.push_back(SuperVertex(std::vector<unsigned int> ({0,1,2,3})));
    // supervertices.push_back(SuperVertex(std::vector<unsigned int> ({4,5})));
    // supervertices.push_back(SuperVertex(std::vector<unsigned int>({6,7})));
    // supervertices.push_back(SuperVertex(std::vector<unsigned int> ({8,9,10,11,12,13,14})));

    
    // std::cout << "Matriz de distancias:\n";

    // int n = data->getDimension();
    
    // for(size_t i = 0; i < n; i++)
    // {
    //     for(size_t j = 0; j < n; j++)
    //     {
    //         std::cout << data->getDistance(i,j) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << "Distância entre (4,5) e (6,7) = " << calculateDistance(supervertices[1], supervertices[2], data->getMatrixCost()) << std::endl;

    // std::cout << "\"Super vértices\":\n";
    // for(auto vertex : supervertices)
    // {
    //     std::cout << vertex  << std::endl;
    // }

    // std::cout << "Fazendo merge dos vértices (1) e (2)\n";
    // mergeSuperVertices(supervertices, 1, 2);

    // std::cout << "\"Super vértices\":\n";
    // for(auto vertex : supervertices)
    // {
    //     std::cout << vertex  << std::endl;
    // }

    data->readData();



    // int n = 8;
    // Matrixlf x_edge = std::vector<std::vector<double> > (n, std::vector<double>(n,0));

    // x_edge[0][1] = x_edge[1][0] = 2;
    // x_edge[0][4] = x_edge[4][0] = 3;
    // x_edge[4][1] = x_edge[1][4] = 2;
    // x_edge[4][5] = x_edge[5][4] = 3;
    // x_edge[1][5] = x_edge[5][1] = 2;
    // x_edge[1][2] = x_edge[2][1] = 3;
    // x_edge[5][6] = x_edge[6][5] = 1;
    // x_edge[2][6] = x_edge[6][2] = 2;
    // x_edge[2][3] = x_edge[3][2] = 4;
    // x_edge[6][3] = x_edge[3][6] = 2;
    // x_edge[6][7] = x_edge[7][6] = 3;
    // x_edge[7][3] = x_edge[3][7] = 2;

    // int n = 6;

    // Matrixlf x_edge =      {{0, 1, 1, 0, 0, 0},
    //                        {1, 0, 1, 0, 0, 0},
    //                        {1, 1, 0, 0, 0, 0},
    //                        {0, 0, 0, 0, 1, 1},
    //                        {0, 0, 0, 1, 0, 1},
    //                        {0, 0, 0, 1, 1, 0}};

    // int n = 6;

    // Matrixlf x_edge =      {{0, 9, 8, 0, 0, 0},
    //                        {0, 0, 0, 4, 0, 4},
    //                        {0, 0, 0, 0, 3, 5},
    //                        {0, 0, 0, 0, 5, 0},
    //                        {0, 0, 0, 0, 0, 0},
    //                        {0, 0, 0, 0, 6, 0}};

    // int n = 8;
    // Matrixlf x_edge =      {{0, 2, 0, 0, 3, 0, 0, 0},
    //                         {2, 0, 3, 0, 2, 2, 0, 0},
    //                         {0, 3, 0, 4, 0, 0, 2, 0},
    //                         {0, 0, 4, 0, 0, 0, 2, 2},
    //                         {3, 2, 0, 0, 0, 3, 0, 0},
    //                         {0, 2, 0, 0, 3, 0, 1, 0},
    //                         {0, 0, 2, 2, 0, 1, 0, 3},
    //                         {0, 0, 0, 2, 0, 0, 3, 0}};

    // double **cost = new double*[n];
	// for (int i = 0; i < n; i++){
	// 	cost[i] = new double[n];
	// 	for (int j = 0; j < n; j++){
    //         cost[i][j] = x_edge[i][j];          
	// 	}
	// }


    string instanceName = getInstanceName(argv);
    STSP_Solve(data, instanceName, ub);
    /*************** Cleaning the memory ***************/
    delete data;
    /***************************************************/

    return 0;
}
