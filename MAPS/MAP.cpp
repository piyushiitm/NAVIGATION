#include <iostream>   // Preprocessor directive: includes the standard input-output stream library (for cout, cerr)
#include <fstream>    // Includes file stream library (for ifstream to read files)
#include <sstream>    // Includes string stream library (for parsing CSV line strings)
#include <vector>     // Includes vector container (dynamic array in C++)
#include <string>     // Includes string class (for handling text like lines in CSV)
using namespace std;  // Allows us to use standard library names (cout, vector, etc.) without writing std:: prefix

int main() {  // main() is the entry point of every C++ program
    string filename = "MainBlock.csv";   // string: text type; filename stores the name of the CSV file
    ifstream file(filename);         // ifstream: input file stream; 'file' object opens the CSV file for reading

    if (!file.is_open()) {           // if: conditional; !file.is_open() checks if the file failed to open
        cerr << "Error opening file!" << endl; // cerr: standard error stream; endl: newline
        return 1;                    // return 1: exits program with error code 1
    }

    int u, v;        // int: integer variables u and v (will hold nodes from CSV line)
    char comma;      // char: single character variable to hold ',' from CSV
    int maxNode = 0; // maxNode keeps track of the highest numbered node (used to size adjacency list)

    vector<pair<int,int>> edges;  // vector: dynamic array; pair<int,int>: stores a pair of integers (an edge)

    // Read CSV file line by line
    string line;   // line: string variable to hold each row of CSV
    while (getline(file, line)) {     // getline(file, line): reads one line of text from file into 'line'
        stringstream ss(line);        // stringstream: allows us to treat line as a stream for parsing
        ss >> u >> comma >> v;        // >>: extraction operator; reads "u,comma,v" from the line
        edges.push_back({u, v});      // push_back: adds a new edge (u,v) to the edges vector
        maxNode = max(maxNode, max(u, v)); // update maxNode with the largest node seen so far
    }
    file.close();   // close the file after reading all lines

    // Build adjacency list representation of graph
    vector<vector<int>> graph(maxNode + 1); // graph is a vector of vectors (2D); each index holds neighbors
    for (auto &edge : edges) {              // range-based for loop: iterate over each edge in edges
        graph[edge.first].push_back(edge.second); // add v to adjacency list of u
        graph[edge.second].push_back(edge.first); // add u to adjacency list of v (undirected graph)
    }

    // Print adjacency list
    cout << "Graph Adjacency List:" << endl; // cout: console output stream
    for (int i = 1; i <= maxNode; i++) {     // for loop: iterate from node 1 to maxNode
        cout << i << ": ";                   // print node number
        for (int neighbor : graph[i]) {      // inner loop: iterate through neighbors of node i
            cout << neighbor << " ";         // print each neighbor
        }
        cout << endl;                        // print newline after each adjacency list
    }

    return 0;  // return 0: signals successful program completion
}
