#include "PMaxBack.hpp"


pair<int,double> chooseBestMaxBack(vector<int> *s, int n, double **x, vector<bool>& inS){

    int bestNode;
    double bestMaxBack = -1;//Ensure that it's lower than first maxBack

    for(int i = 0; i < n; i++){

        double maxBack = 0;

        if(inS[i] == 1){
            continue;
        }

        for(int j = 0; j < s->size(); j++){

            if((*s)[j] < i){

                maxBack += x[(*s)[j]][i];
            }

            else{

                maxBack += x[i][(*s)[j]];
            }
        }

        if(maxBack > bestMaxBack){

            bestMaxBack = maxBack;
            bestNode = i;
        }
    }

    return make_pair(bestNode, bestMaxBack);
}

double calculatInitialMaxBackCutMin(int node, int n, double **x){

    double value = 0;

    for(int i = 0; i < n; i++){

        if(i < node){

            value += x[i][node];
        }

        else if(i == node){

            continue;
        }

        else{

            value += x[node][i];
        }
    }

    return value;
}

void updateBool(vector<bool>&chosed, vector<int> Smin){

    int n = Smin.size();

    for(int i = 0; i < n; i++){
        chosed[Smin[i]] = 1;
    }
}

vector<vector<int>> PMaxBack(double **x, int n){

    vector<vector<int>> result;
    bool cont;
    vector<bool> alreadyChosed(n, 0);

    for(int i = 0; i < n; i++){

        for(int j = 0; j < n; j++){

            if(x[i][j] < 1e-4){

                x[i][j] = 0;
            }
        }
    }

    for(int i = 0; i < n; i++){

        if(alreadyChosed[i] == 1){
            continue;
        }

        vector<int> s = {i};
        vector<int> sMin;
        double cutMin = calculatInitialMaxBackCutMin(s[0], n, x);
        double cutVal = cutMin;

        vector<bool> inS(n, 0);
        inS[i] = 1;
        alreadyChosed[i] = 1;

        while(s.size() < n){

            pair<int,double> bestNode = chooseBestMaxBack(&s, n, x, inS);

            s.push_back(bestNode.first);
            inS[bestNode.first] = 1;
            cutVal += 2 + - (bestNode.second * 2);

            if(cutVal < cutMin){

                cutMin = cutVal;
                sMin = s;
            }
        }

        updateBool(alreadyChosed, sMin);

        if(sMin.size() != n){
            result.push_back(sMin);
        }
    }

    return result;
}

double sumSuperNodeMaxBack(int firstNode, int secondNode, vector<super_node> *superNodes, double **x){

    double sum = 0;

    for(int i = 0; i < (*superNodes)[firstNode].size(); i++){

        int iNode = (*superNodes)[firstNode][i];

        for(int j = 0; j < (*superNodes)[secondNode].size(); j++){

            int jNode = (*superNodes)[secondNode][j];

            if(iNode < jNode){

                sum += x[iNode][jNode];
            }

            else{

                sum += x[jNode][iNode];
            }
        }
    }

    return sum;
}

pair<int,double> chooseBestMaxBackSuperNodes(vector<int> *s, vector<super_node> *superNodes, double **x){

    int bestNode;
    double bestMaxBack = -1;//Ensure that it's lower than first maxBack

    for(int i = 0; i < superNodes->size(); i++){

        double maxBack = 0;

        if(find(s->begin(), s->end(), i) != s->end()){
          
            continue;
        }

        for(int j = 0; j < s->size(); j++){

            maxBack += sumSuperNodeMaxBack(i, (*s)[j], superNodes, x);
        }     
        
        if(maxBack > bestMaxBack){

            bestMaxBack = maxBack;
            bestNode = i;
        }
    }

    return make_pair(bestNode, bestMaxBack);
}