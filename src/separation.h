//---------------------------------------------------------------------------

/***************************************************/
/* Functions prototypes by Prof. Anand Subramanian */
/***************************************************/

#ifndef Separation_H
#define Separation_H

#include <ilcplex/ilocplex.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <pthread.h>
#include "Vertex.h"
#include <map>

#define EPSILON 0.00000001

using namespace std;

typedef struct{
    vector<int> nodes;
    int id;
    bool is_vertexA;
} vertex_type;

extern vector <vector<int> > MaxBack(double** x, int n);
extern vector <vector<int> > MinCut(double** x, int n);


double calculateDistance(SuperVertex s1, SuperVertex s2, double ** costs);
void mergeSuperVertices(std::vector<SuperVertex> &supervertices, int i, int j);
SuperVertex mergeSuperVertices(SuperVertex sp1, SuperVertex sp2);

std::vector<int> getA(int a, std::vector<SuperVertex> vertices, double ** costs, int n, int & rest);

double calculateCutmin(Vectord s, Vectorb includedVertices, double ** costs, int n);
double minCutPhase(std::vector<int> A, SuperVertex rest, std::vector<SuperVertex> supervertices, double ** costs);


bool hasMoreThanOneLonelyVertex(std::vector<SuperVertex> supervertices); /*Esta função não é muito eficiente, devo fazer essa verificação de outra forma*/

bool byGreaterCost(std::pair<int, double> a, std::pair<int, double> b);

VertexVector getMaxBackValues(double ** costs, std::vector<int> &s, std::vector<bool> includedVertices, int n);
void updateMaxBackValues(double ** costs, std::vector<double> &maxBackValues, int newVertex, std::vector<bool> &includedVertices, int n);

#endif

//---------------------------------------------------------------------------
