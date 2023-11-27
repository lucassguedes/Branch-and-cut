//---------------------------------------------------------------------------

/*******************************************************/
/* Auxiliary Function's Set by Prof. Anand Subramanian */
/*******************************************************/

#include "auxFunctions.h"
#include <map>
#include <vector>

string getInstanceName(char **argv)
{
	string temp(argv[1]);
	string::size_type loc = temp.find_last_of(".", temp.size() );
	string::size_type loc2 = temp.find_last_of("/", temp.size() );
	string nomeDaInstancia;
	
	if (loc != string::npos) {
		nomeDaInstancia.append(temp, loc2+1, loc-loc2-1 );
		//cout << "\n1-" << nomeDaInstancia << endl;
	}
	else {
		nomeDaInstancia.append(temp, loc2+1, temp.size() );
		//cout << "\n2-" << nomeDaInstancia << endl;
	}
	
	return nomeDaInstancia;
}

void printResults(IloCplex cplex, string instanceName, double time)
{

	cout << "\n\nBranch-and-cut_Results: \n" << endl;

	cout << "Instance: " << instanceName << endl;
	cout << "Tree_Size: " << cplex.getNnodes() + cplex.getNnodesLeft() + 1 << endl;
	cout << "Total_Time: " << time << endl;
	cout << "LB: " << cplex.getBestObjValue() << endl;
	cout << "UB: " << cplex.getObjValue() << endl; 
	cout << "Status: " << cplex.getStatus() << endl;
}

void printResultsToFile(IloCplex cplex, string instanceName, double time)
{
	ofstream results1("Results1.txt", ios::app);
	results1 << "Instance: " << instanceName;
	results1 << " Tree_Size: " <<  cplex.getNnodes() + cplex.getNnodesLeft() + 1;
	results1 << " Total_Time: " << time;
	results1 << " LB: " << cplex.getBestObjValue();
	results1 << " UB: " << cplex.getObjValue() ; 
	results1 << " Status: " << cplex.getStatus();
	results1 << endl;
	results1.close();
}

void printSolution(IloCplex cplex, IloArray <IloBoolVarArray> x, int n)
{

	// std::cout << "N: " << n << std::endl;
	bool **sol = new bool*[n];
	vector< vector<int> > solutions;

	for (int i = 0; i < n; i++) {
		sol[i] = new bool[n];
	}
	/************** Getting the solution **************/
	//cout << "\nSolution:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if(j > i){
				sol[i][j] = 0;
				if (cplex.getValue(x[i][j]) > 0.5) {
					// cout << "X(" << i << "," << j << ") = " << cplex.getValue(x[i][j]) << "\n";
					sol[i][j] = 1;
					sol[j][i] = 1;
				}
			}
			else{
				sol[i][j] = 0;
			}
		}
		//cout << endl;
	}
	
	/**************************************************/
	
	/*************** Building the route ***************/

	solutions.push_back({0});
	int p;
	vector<bool> in_solution(n, false); /*indica se cada um dos vértice está ou não dentro da solução*/
	in_solution[0] = true;
	bool find = true;
	int last_index = 0, current_index = 0;
	int inclusion_counter = 1;
	int current_subroute = 0;
	int first_vertex = 0;
	// std::cout << "Inicializando (sub)rota com o vértice 0...\n";
	std::vector<std::vector<bool> > includedEdges = std::vector< std::vector<bool> > (n, std::vector<bool> (n , false));
	while (inclusion_counter < n){
		p = solutions[current_subroute][last_index]; /*p é o último vértice até então adicionado na solução a ser impressa*/
		// std::cout << "in solution: [";
		// for(auto k : in_solution)
		// {
		// 	std::cout << k << " ";
		// }
		// std::cout << "]" << std::endl;
		for(int j = 0; j < n; j++){
			if (sol[p][j] == 1) {/*Se x_{ij} = 1 na solução gerada*/
				if(!includedEdges[p][j]){ /*Se o vértice j ainda não estiver na solução*/
				
					// std::cout << "Adicionando " << j << " na solução...\n";
					solutions[current_subroute].insert(solutions[current_subroute].begin() + current_index + 1, j); /*Insere o novo vértice j*/
					includedEdges[p][j] = true;
					if(!in_solution[j])
						inclusion_counter++;
					in_solution[j] = true;
					current_index++;
					last_index++;
					p = solutions[current_subroute][last_index];
					// std::cout << "p = " << p << std::endl;
					j = -1;
				}
			}else if(sol[j][p] == 1)
			{
				if(!includedEdges[j][p]){ /*Se o vértice j ainda não estiver na solução*/
					
					// std::cout << "Adicionando " << j << " na solução...\n";
					solutions[current_subroute].insert(solutions[current_subroute].begin() + current_index + 1, j); /*Insere o novo vértice j*/
					includedEdges[j][p] = true;
					if(!in_solution[j])
						inclusion_counter++;
					in_solution[j] = true;
					current_index++;
					last_index++;
					p = solutions[current_subroute][last_index];
					// std::cout << "p = " << p << std::endl;
					j = -1;
				}
			}
			
		}
		// std::cout << "(sub)rota: [";
		for(int i = 0; i < solutions[current_subroute].size(); i++)
		{
			std::cout << solutions[current_subroute][i];
			// if(i < solutions[current_subroute].size() - 1)
			// 	// std::cout << " ";
			// else 
			// 	// std::cout << "]\n";
		}
		if(inclusion_counter < n)
		{
			// std::cout << "Não foi encontrada nenhuma outra aresta ligada ao vértice " << solutions[current_subroute][last_index] << std::endl;
			// std::cout << "Inicializando nova subrota...\n";
			solutions.push_back({});
			current_subroute++;
			current_index = last_index = 0;
			for(int i = 0; i < in_solution.size(); i++)
			{
				if(!in_solution[i])
				{
					solutions[current_subroute].push_back(i);
					first_vertex = i;
					// std::cout << "Vértice inicial: " << i << std::endl;
					in_solution[i] = true;
					inclusion_counter++;
					// std::cout << "Vértices inclusos: " << inclusion_counter << std::endl;
					break;
				}

			}
		}else{
			// std::cout << "Finalizando...\n";
			// std::cout << "in solution: [";
			// for(auto k : in_solution)
			// {
			// 	std::cout << k << " ";
			// }
			// std::cout << "]" << std::endl;

		}
	}
	// solution.push_back(0);
	// std::cout << "Chegou aqui!\n";
	
	/**************************************************/

	std::cout << "\nRoute(s): \n";
	for(int i = 0; i < solutions.size(); i++)
	{
		for (int j = 0; j < solutions[i].size(); j++) {
			std::cout << solutions[i][j] << " ";
		}
		std::cout << endl;
	}
	

	/************** Cleaning the memory ***************/
	for (int i = 0; i < n; i++) {
		delete[] sol[i];
	}
	delete[] sol;
	/**************************************************/
}
//---------------------------------------------------------------------------