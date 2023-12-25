#include "MyCutCallback.h"
#include <cstdio>
#include "mincut.hpp"

/********************************************** Class' Constructor **********************************************/
MyCutCallback::MyCutCallback(IloEnv env, const IloArray<IloBoolVarArray>& x_ref, int nodes) : IloCplex::UserCutCallbackI(env), x(x_ref), x_vars(env), n(nodes)
{
	/********** Filling x_vars **********/ 
	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++){
			x_vars.add(x[i][j]);
		}
	}
	/************************************/
} 
/*****************************************************************************************************************/

/************************** Return a callback copy. This method is a CPLEX requirement ***************************/
IloCplex::CallbackI* MyCutCallback::duplicateCallback() const 
{ 
   return new (getEnv()) MyCutCallback(getEnv(), x, n); 
}
/*****************************************************************************************************************/

/************************************ Callback's code that is runned by CPLEX ************************************/

bool compareCutSetPool(std::vector<std::vector<int> > c1, std::vector<std::vector<int> > c2)
{
	if(c1.size() != c2.size())
		return false;
	
	for(int i = 0; i < c1.size(); i++)
	{
		if(c1[i].size() != c2[i].size())
			return false;
		
		for(int j = 0; j < c1[i].size(); j++)
		{
			if(c1[i][j] != c2[i][j])
				return false;
		}
	}

	return true;
}


void MyCutCallback::main() 
{
	std::cout << "MyCutCallback\n";
	/**************** Getting the node's depth ****************/
	//int depth = 0;
	/*NodeInfo *data = dynamic_cast<NodeInfo*>(getNodeData());

	if (!data){
        if (NodeInfo::rootData == NULL)
            NodeInfo::initRootData();
        
		data = NodeInfo::rootData;
    }
	if (data) {
		depth = data->getDepth();
	}*/
	int depth = getCurrentNodeDepth();
	/**********************************************************/

	/********** Getting the relaxed variables values **********/
	IloNumArray x_vals(getEnv(), (0.5*(n)*(n-1)));
	getValues(x_vals, x_vars);
	/**********************************************************/

	vector< vector<int> > cutSetPool;
	vector<IloConstraint> cons; 

	double **x_edge = new double*[n];
	double **x_edge2 = new double*[n];
 
	for (int i = 0; i < n; i++) {
		x_edge[i] = new double[n];
		x_edge2[i] = new double[n];

	}

	int l = 0;
	for(int i = 0; i < n; i++) {
		for(int j = i+1; j < n; j++) {
			x_edge2[i][j] = x_edge[i][j] = x_vals[l++];
		}
	}

	x_vals.end();

	// std::cout << "Executando max-back...\n";
	cutSetPool = MaxBack(x_edge, n);
	// std::cout << "Max-back finalizado...\n";

	// std::cout << "cutSetPool (Max-back): \n";
	// for(int i = 0; i < cutSetPool.size(); i++)
	// {
	// 	for(int j = 0; j < cutSetPool[i].size(); j++)
	// 	{
	// 		std::cout << cutSetPool[i][j] << " ";
	// 	}
	// 	if(cutSetPool[i].size())
	// 		std::cout << std::endl;
	// }
	//PMaxBack(x_edge, n);

	std::vector<std::vector<int> > cutSetPool2;
	if (cutSetPool.empty() && depth <= 7) {
		// cutSetPool = MinCut(x_edge, n);
		// std::cout.setstate(std::ios_base::failbit);
		// std::cout << "Executando mincut...\n";

		for(int i = 0; i < n; i++) {
			for(int j = i+1; j < n; j++) {
				x_edge2[i][j] = x_edge[i][j];
			}
		}

		// cutSetPool = MinCut(x_edge, n);
		cutSetPool = minCut(n, x_edge2);

		// if(compareCutSetPool(cutSetPool, cutSetPool2))
		// {
		// 	std::cout << "They are equal!\n";
		// }else
		// {
		// 	std::cout << "They are different!\n";

		// 	std::cout << "cutSetPool: \n";
		// 	for(int i = 0; i < cutSetPool.size(); i++)
		// 	{
		// 		for(int j = 0; j < cutSetPool[i].size(); j++)
		// 		{
		// 			std::cout << cutSetPool[i][j] << " ";
		// 		}
		// 		if(cutSetPool[i].size())
		// 			std::cout << std::endl;
		// 	}

		// 	std::cout << "cutSetPool2: \n";
		// 	for(int i = 0; i < cutSetPool2.size(); i++)
		// 	{
		// 		for(int j = 0; j < cutSetPool2[i].size(); j++)
		// 		{
		// 			std::cout << cutSetPool2[i][j] << " ";
		// 		}
		// 		if(cutSetPool2[i].size())
		// 			std::cout << std::endl;
		// 	}
		// 	getchar();
		// }

		// std::cout << "Mincut finalizado...\n";
		// std::cout.clear();


		
		// cutSetPool = MultipleMinCut(x_edge, n);
	}

	/***************** Creating the constraints ***************/
	if (!cutSetPool.empty()){
		for (int c = 0; c < cutSetPool.size(); c++) {
			IloExpr p(getEnv());
			for(int i = 0; i < cutSetPool[c].size(); i++){
				for(int j = 0; j < cutSetPool[c].size(); j++){
					if(cutSetPool[c][i] < cutSetPool[c][j]){
						p += x[cutSetPool[c][i]][cutSetPool[c][j]];
					}
				}
			}
			int RHS = cutSetPool[c].size(); /*Quantidade de arestas no subtour com o maior valor de max-back (?)*/
			cons.push_back(p <= RHS - 1);
		}
		/*********** Adding the constraints to the model **********/
		for(int i = 0; i < cons.size(); i++){
			add(cons.at(i)).end();
		}
		/**********************************************************/
	}
	/**********************************************************/

	/******************* Cleaning the memory ******************/
	for (int i = 0; i < n; i++) {
		delete[] x_edge[i];
		delete[] x_edge2[i];

	}
	delete[] x_edge;
	delete[] x_edge2;

	/**********************************************************/
}
/*****************************************************************************************************************/
