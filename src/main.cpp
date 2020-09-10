#include <vector>
#include <iostream>
#include <map>
#include <iomanip>
using namespace std;

class AdjacencyList{

private:
    int vertexCounter;
    vector<float> ranks;
    map<string, int > vertices;
    map<int, vector< int > > edges;                     // Stores all the edges to count outdegrees.
    map<int, vector< pair<int, float> > > rankMap;      // Stores the "matrix" used for page rank computation.
public:
    AdjacencyList(){
        vertexCounter = 0;
    }

    void addEdge(string from, string to){
        if(vertices.find(from) == vertices.end()){      //Adds from and to vertices in case they were not created.
            vertices[from] = vertexCounter;
            ranks.push_back(0);
            vertexCounter++;
        }
        if(vertices.find(to) == vertices.end()){
            vertices[to] = vertexCounter;
            ranks.push_back(0);
            vertexCounter++;
        }
        if (rankMap.find(vertices[from]) == rankMap.end()){     //Makes sure all vertices are in the rankMap.
            rankMap[vertices[from]];
        }
        edges[vertices[from]].push_back(vertices[to]);
        rankMap[vertices[to]].push_back(make_pair(vertices[from], 0));
    }

    int getVertexCounter(){
        return vertexCounter;
    }

    int getOutDegree(int vertex){
        return edges[vertex].size();
    }

    void updateRankMap(){                                       //Updates the values of the rankMap for computation.
        for(auto i = rankMap.begin(); i != rankMap.end(); i++){
            for (int j = 0; j < i->second.size(); j++){
                i->second[j].second = (1.0 / (float) getOutDegree(i->second[j].first));
            }
        }
    }

    void pageRank(int p){                                       //Computes page ranks based on rankMap and ranks
        updateRankMap();
        float r = 1.0 / (float) getVertexCounter();
        for (int i = 0; i < getVertexCounter(); i++){
            ranks[i] = r;
        }
        for (int k = 0; k < (p - 1); k++) {
            float rank = 0.0;
            vector<float> currentRanks = ranks;
            for (auto i = rankMap.begin(); i != rankMap.end(); i++) {
                rank = 0;
                for (int j = 0; j < i->second.size(); j++) {
                    rank += i->second[j].second * currentRanks[i->second[j].first];
                }
                ranks[i->first] = rank;
            }
        }
        for (auto i = vertices.begin(); i != vertices.end(); i++){
            cout << i->first << " " << fixed << setprecision(2) << ranks[i->second] << endl;

        }
    }
};

int main() {
    int numLines;
    int power;
    cin >> numLines >> power;

    AdjacencyList mainGraph = AdjacencyList();
    string from;
    string to;

    for(int i = 0; i < numLines; i++){
        cin >> from >> to;
        mainGraph.addEdge(from, to);
    }

    mainGraph.pageRank(power);

    return 0;
}