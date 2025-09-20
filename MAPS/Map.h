#include <iostream>     // For input and output
#include <fstream>      // For reading files
#include <sstream>      // For parsing each line of CSV
#include <vector>       // For adjacency list
#include <string>       // For handling strings
#include <map>
using namespace std;    // To avoid writing std:: everywhere

// We will represent each edge as a pair (neighbor, weight)
struct Edge{
        int neighbor;   // The connected node
    int weight;     // The weight of the edge

};
class Graph {
    public:
    vector<vector<Edge>> adjacencyList; // Graph as adjacency list
    int maxNode = 0;                    // To find how many nodes exist
    map<int, string> idToLabel;
    Graph(string fileName){
        ifstream file(fileName);            // Input file stream object

        // Check if file opened successfully
        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;                       // Exit program if file not found
        }

        string line;                        // To store each line from the file
        // Step 1: Read all edges from CSV
        vector<vector<int>> rawEdges;       // Temporary storage for edges

        while (getline(file, line)) {       // Read one line at a time
            stringstream ss(line);          // Use stringstream to split line
            string item;                    // Temporary string

            int fromNode, toNode, edgeWeight;

            // Read first number (fromNode)
            getline(ss, item, ',');         
            fromNode = stoi(item);          // Convert string to int

            // Read second number (toNode)
            getline(ss, item, ',');
         toNode = stoi(item);

            // Read third number (weight)
            getline(ss, item, ',');
            edgeWeight = stoi(item);

            // Store the edge in a temporary vector
            rawEdges.push_back({fromNode, toNode, edgeWeight});

            // Update maximum node number (needed for adjacency list size)
            maxNode = max(maxNode, max(fromNode, toNode));
        }

            file.close();   // Close the file after reading

        // Step 2: Resize adjacency list based on maximum node number
        adjacencyList.resize(maxNode + 1);  // +1 so we can use 1-based indexing

        // Step 3: Fill adjacency list with edges
        for (auto edge : rawEdges) {
            int fromNode = edge[0];     // First node
            int toNode   = edge[1];     // Second node
            int weight   = edge[2];     // Weight of edge

            // Add edge fromNode -> toNode
            adjacencyList[fromNode].push_back({toNode, weight});

            // Add reverse edge (toNode -> fromNode) because graph is undirected
           adjacencyList[toNode].push_back({fromNode, weight});
        }

        //Assigning Labels
        idToLabel[1]  = "Entrance";
        idToLabel[2]  = "Document Counter";
        idToLabel[3]  = "Accounts";
        idToLabel[4]  = "Right Corridor";
        idToLabel[5]  = "Boys Toilet";
        idToLabel[6]  = "1st RIntersection";
        idToLabel[7]  = "F15";
        idToLabel[8]  = "2nd RIntersection";
        idToLabel[9]  = "F16";
        idToLabel[10] = "Alumni Cell";
        idToLabel[11] = "3rd RIntersection";
        idToLabel[12] = "Counselling Cell";
        idToLabel[13] = "4th RIntersection";
        idToLabel[14] = "F19";
        idToLabel[15] = "Xerox Shop";
        idToLabel[16] = "First to Ground";
        idToLabel[17] = "First to Second";
        idToLabel[18] = "Lakshmi Narain Temple";
        idToLabel[19] = "Left Corridor";
        idToLabel[20] = "Sitting Area";
        idToLabel[21] = "F11";
        idToLabel[22] = "1st LIntersection";
        idToLabel[23] = "4th LItersection";
        idToLabel[24] = "F10";
        idToLabel[25] = "F9";
        idToLabel[26] = "2nd LCorridor";
        idToLabel[27] = "Male Washroom";
        idToLabel[28] = "Female Washroom";
        idToLabel[29] = "F8";
        idToLabel[30] = "F7";
        idToLabel[31] = "F6";
        idToLabel[32] = "3rd LIntersection";
        idToLabel[33] = "2nd LIntersection";
        idToLabel[34] = "F5";
        idToLabel[35] = "Admission Cell";
        idToLabel[36] = "Reception";
    }

        // Step 4: Print adjacency list
    void display_map(){
        cout << "Weighted Adjacency List Representation:" << endl;

        for (int i = 1; i <= maxNode; i++) {    // Loop over all nodes
            cout << idToLabel[i] << " -> ";                // Print current node
            for (auto edge : adjacencyList[i]) {
                cout << "(" << idToLabel[edge.neighbor] << ", " << edge.weight << ") ";
        // Print neighbor and weight
            }
        cout << endl;   // Move to next line
        }
    }
    void displayNodes() {
    cout << "List of Nodes:\n";
    for (int i = 1; i <= maxNode; i++) {
        // If label exists, print label; otherwise print ID
        if (!idToLabel[i].empty())
            cout << i << " : " << idToLabel[i] << endl;
        else
            cout << i << " : Node" << i << endl;
    }
}

};