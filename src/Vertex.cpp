#include "Vertex.h"


SuperVertex::SuperVertex(int initVertexIdx, double costToOthers)
{
  this->vertices = {initVertexIdx};
  this->costToOthers = costToOthers;
}

SuperVertex::SuperVertex(std::vector<int> vertices)
{
  this->vertices = vertices;
}


void SuperVertex::addVertex(int a)
{
  this->vertices.push_back(a);
  this->isUnique = false;
}

std::ostream &operator<<(std::ostream &os, const SuperVertex &v)
{
  const size_t tam = v.vertices.size();
  os << "(";
  for(size_t i = 0; i < tam; i++)
  {
    os << v.vertices[i];

    if(i < (v.vertices.size()-1))
    {
      os << ", ";
    }else{
      os << ")";
    }
  }

  return os;
}

std::ostream& operator << (std::ostream& os, const Vertex& v)
{

  os << "Vértice " << v.idx << std::endl;
  os << "\tMax-back value: " << v.maxBackValue << std::endl;

  return os;
}

Vertex::Vertex(unsigned int idx, double maxBackValue) {
    this->idx = idx;
    this->maxBackValue = maxBackValue;
}

bool byGreaterMaxBack(Vertex a, Vertex b) {
  return a.maxBackValue > b.maxBackValue;
}