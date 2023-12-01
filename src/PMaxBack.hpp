#include <vector>
#include <map>
#include <algorithm>


using namespace std;

typedef vector<int> super_node;


pair<int,double> chooseBestMaxBack(vector<int> *s, int n, double **x, vector<bool>& inS);
double calculatInitialMaxBackCutMin(int node, int n, double **x);
void updateBool(vector<bool>&chosed, vector<int> Smin);
vector<vector<int>> PMaxBack(double **x, int n);
double sumSuperNodeMaxBack(int firstNode, int secondNode, vector<super_node> *superNodes, double **x);
pair<int,double> chooseBestMaxBackSuperNodes(vector<int> *s, vector<super_node> *superNodes, double **x);