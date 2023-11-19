#ifndef _VERTEX_H
#define _VERTEX_H

#include <iostream>
#include <vector>


typedef std::vector<double> Vectorlf;
typedef std::vector<std::vector<int> > Matrixd;
typedef std::vector<std::vector<double> > Matrixlf;
typedef std::vector<int> Vectord;
typedef std::vector<bool> Vectorb;

class SuperVertex{
  public:
    std::vector<int> vertices;
    double costToOthers; /*Esta variável armazena a soma dos custos das arestas que ligam o vértice ao restante*/
    bool isUnique = true;

    SuperVertex(){}
    SuperVertex(int initVertexIdx, double costToOthers);

    SuperVertex(std::vector<int> vertices);

    void addVertex(int a);

    friend std::ostream &operator<<(std::ostream &os, const SuperVertex &v);
};

class Vertex {
public:
  unsigned int idx;
  double maxBackValue;
  double costToOthers; /*Esta variável armazena a soma dos custos das arestas que ligam o vértice ao restante*/

  Vertex(unsigned int idx, double maxBackValue);

  Vertex(){}

  friend std::ostream &operator<<(std::ostream &os, const Vertex &v);
};

std::ostream& operator << (std::ostream& os, const Vertex& v);

typedef std::vector<Vertex> VertexVector;

bool byGreaterMaxBack(Vertex a, Vertex b);


#endif 