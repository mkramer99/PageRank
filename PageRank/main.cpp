#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <iomanip>
using namespace std;


class Graph {
private:
    // the graph
    map<string, vector<pair<string, float>>> graph;
    // map to hold final ranks after each pagerank iteration
    map<string, float> rank;
    // map to hold new rank during the pagerank iteration
    map<string, float> temprank;
    // map to hold calculated outdegrees during map creation
    map<string, float> outdegrees;
public:
    void PageRank(int p);
    Graph(int n);
};


// prints the PageRank of all pages after p iterations
// ascending alphabetical order of pages
// rounding rank to 2 deci places
void Graph::PageRank(int p) {
    // perform p iterations on graph
    if (p > 0) {
        map<string, vector<pair<string, float>>>::iterator itt;
        float sum = 0;
        // iterate p times
        for (int k = 0; k < p; k++) {
            // iterate through graph
            for (itt = graph.begin(); itt != graph.end(); itt++) {
                for (int j = 0; j < itt->second.size(); j++) {
                    // dot product of outdegrees and ranks
                    sum += ((1.00 / itt->second[j].second) * (float)rank[itt->second[j].first]);
                }
                // mult sum by current page rank
                temprank[itt->first] = sum;
                sum = 0;
            }
            // assign temprank values to rank for next iteration
            map<string, float>::iterator it;
            for (it = rank.begin(); it != rank.end(); it++) {
                rank[it->first] = temprank[it->first];
            }
        }
    }
    // print final result
    std::cout << std::fixed << std::setprecision(2);
    map<string, float>::iterator it;
    for (it = rank.begin(); it != rank.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }
}


Graph::Graph(int n) {
    string line;
    string from;
    string to;
    // skip whitespace
    getline(cin, line);
    // read vertices and create graph
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        istringstream in(line);
        // source vertex
        in >> to;
        // destination vertex
        in >> from;
        // add vertices/edges (from->to) to graph here
        graph[from].push_back(make_pair(to, 1.00/(float)n));
        // keep track of outdegrees with outdegrees map
        if (outdegrees.count(to) == 0) {
            outdegrees[to] = 1;
            rank[to] = 0;
        } else {
            outdegrees[to] = ++outdegrees[to];
        }
        // assign rank for page if non existent
        if (rank.count(from) == 0) {
            rank[from] = 0;
        }
    }
    // assign initial ranks to rank map of 1/number of pages
    map<string, float>::iterator it;
    for (it = rank.begin(); it != rank.end(); it++) {
        rank[it->first] = 1.00/(float)rank.size();
        temprank[it->first] = 0;
    }

    // assign outdegrees to pages in graph
    map<string, vector<pair<string, float>>>::iterator itt;
    for (itt = graph.begin(); itt != graph.end(); itt++) {
        for (int j = 0; j < itt->second.size(); j++) {
            // assign outdegrees to linked pages
            itt->second[j].second = outdegrees[itt->second[j].first];
        }
    }
}


int main() {

    // number of lines
    int n;
    cin >> n;

    // number of power iterations
    int p;
    cin >> p;

    // create graph
    Graph graph(n);

    // do power iterations
    graph.PageRank(p - 1);

    return 0;
}
