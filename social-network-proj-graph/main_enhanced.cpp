#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <climits>

using namespace std;

const int MAX_NODES = 40001;
const int MAX_EDGES = 120001;
const int INF = INT_MAX;

// Edge structure for adjacency list
struct Edge {
    int to;
    int weight;
    Edge* next;
};

// Graph structure using adjacency list with arrays
class Graph {
private:
    Edge* adjacencyList[MAX_NODES];
    int nodeCount;
    int edgeCount;
    int degree[MAX_NODES]; // For heuristic function h(n)
    
public:
    Graph() {
        nodeCount = 0;
        edgeCount = 0;
        for (int i = 0; i < MAX_NODES; i++) {
            adjacencyList[i] = nullptr;
            degree[i] = 0;
        }
    }
    
    ~Graph() {
        // Clean up dynamically allocated edges
        for (int i = 0; i < MAX_NODES; i++) {
            Edge* current = adjacencyList[i];
            while (current != nullptr) {
                Edge* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
    
    void addEdge(int u, int v, int weight) {
        // Add edge u -> v
        Edge* newEdge1 = new Edge();
        newEdge1->to = v;
        newEdge1->weight = weight;
        newEdge1->next = adjacencyList[u];
        adjacencyList[u] = newEdge1;
        degree[u]++;
        
        // Add edge v -> u (undirected graph)
        Edge* newEdge2 = new Edge();
        newEdge2->to = u;
        newEdge2->weight = weight;
        newEdge2->next = adjacencyList[v];
        adjacencyList[v] = newEdge2;
        degree[v]++;
        
        edgeCount++;
        if (u >= nodeCount) nodeCount = u + 1;
        if (v >= nodeCount) nodeCount = v + 1;
    }
    
    int getDegree(int node) {
        return degree[node];
    }
    
    Edge* getNeighbors(int node) {
        return adjacencyList[node];
    }
    
    int getNodeCount() {
        return nodeCount;
    }
    
    // Dijkstra's Algorithm
    void dijkstra(int source, int destination, int* dist, int* parent) {
        bool visited[MAX_NODES];
        
        // Initialize
        for (int i = 0; i < nodeCount; i++) {
            dist[i] = INF;
            parent[i] = -1;
            visited[i] = false;
        }
        
        dist[source] = 0;
        
        for (int count = 0; count < nodeCount; count++) {
            // Find minimum distance vertex
            int minDist = INF;
            int u = -1;
            
            for (int i = 0; i < nodeCount; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }
            
            if (u == -1 || u == destination) break;
            
            visited[u] = true;
            
            // Update distances of neighbors
            Edge* edge = adjacencyList[u];
            while (edge != nullptr) {
                int v = edge->to;
                int weight = edge->weight;
                
                if (!visited[v] && dist[u] != INF && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
                
                edge = edge->next;
            }
        }
    }
    
    // A* Algorithm with heuristic h(n) = degree of node
    void aStar(int source, int destination, int* dist, int* parent) {
        bool visited[MAX_NODES];
        int gScore[MAX_NODES]; // Actual cost from source
        int fScore[MAX_NODES]; // gScore + heuristic
        
        // Initialize
        for (int i = 0; i < nodeCount; i++) {
            gScore[i] = INF;
            fScore[i] = INF;
            parent[i] = -1;
            visited[i] = false;
        }
        
        gScore[source] = 0;
        fScore[source] = degree[source]; // h(source)
        
        while (true) {
            // Find node with minimum fScore
            int minF = INF;
            int current = -1;
            
            for (int i = 0; i < nodeCount; i++) {
                if (!visited[i] && fScore[i] < minF) {
                    minF = fScore[i];
                    current = i;
                }
            }
            
            if (current == -1 || current == destination) break;
            
            visited[current] = true;
            
            // Explore neighbors
            Edge* edge = adjacencyList[current];
            while (edge != nullptr) {
                int neighbor = edge->to;
                int weight = edge->weight;
                
                if (!visited[neighbor]) {
                    int tentativeG = gScore[current] + weight;
                    
                    if (tentativeG < gScore[neighbor]) {
                        parent[neighbor] = current;
                        gScore[neighbor] = tentativeG;
                        // f(n) = g(n) + h(n), where h(n) = degree of neighbor
                        fScore[neighbor] = gScore[neighbor] + degree[neighbor];
                    }
                }
                
                edge = edge->next;
            }
        }
        
        // Copy gScore to dist for consistency
        for (int i = 0; i < nodeCount; i++) {
            dist[i] = gScore[i];
        }
    }
    
    void printPath(int source, int destination, int* parent) {
        if (parent[destination] == -1 && source != destination) {
            cout << "No path exists!" << endl;
            return;
        }
        
        // Build path using parent array
        int path[MAX_NODES];
        int pathLength = 0;
        int current = destination;
        
        while (current != -1) {
            path[pathLength++] = current;
            current = parent[current];
        }
        
        // Print path in reverse
        cout << "Path: ";
        for (int i = pathLength - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) cout << " -> ";
        }
        cout << endl;
        cout << "Path length (nodes): " << pathLength << endl;
    }
    
    void printGraphStats() {
        cout << "Graph Statistics:" << endl;
        cout << "  Total nodes: " << nodeCount << endl;
        cout << "  Total edges: " << edgeCount << endl;
        
        // Calculate average degree
        int totalDegree = 0;
        int maxDegree = 0;
        int minDegree = INF;
        
        for (int i = 0; i < nodeCount; i++) {
            if (degree[i] > 0) {
                totalDegree += degree[i];
                if (degree[i] > maxDegree) maxDegree = degree[i];
                if (degree[i] < minDegree) minDegree = degree[i];
            }
        }
        
        cout << "  Average degree: " << (double)totalDegree / nodeCount << endl;
        cout << "  Max degree: " << maxDegree << endl;
        cout << "  Min degree: " << minDegree << endl;
    }
};

// Dynamic Programming for longest increasing influence path
class InfluenceAnalyzer {
private:
    int influences[MAX_NODES];
    int dp[MAX_NODES]; // dp[i] = longest increasing path ending at i
    int parent[MAX_NODES]; // To reconstruct the path
    Graph* graph;
    
    int dfs(int node, bool* visited) {
        if (dp[node] != -1) return dp[node];
        
        visited[node] = true;
        dp[node] = 1;
        parent[node] = -1;
        
        Edge* edge = graph->getNeighbors(node);
        while (edge != nullptr) {
            int neighbor = edge->to;
            
            // Only follow edges where influence increases
            if (influences[neighbor] > influences[node]) {
                int length = 1 + dfs(neighbor, visited);
                if (length > dp[node]) {
                    dp[node] = length;
                    parent[node] = neighbor;
                }
            }
            
            edge = edge->next;
        }
        
        visited[node] = false;
        return dp[node];
    }
    
public:
    InfluenceAnalyzer(Graph* g) {
        graph = g;
        for (int i = 0; i < MAX_NODES; i++) {
            influences[i] = 0;
            dp[i] = -1;
            parent[i] = -1;
        }
    }
    
    void loadInfluences(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Cannot open influence file!" << endl;
            return;
        }
        
        int user, influence;
        while (file >> user >> influence) {
            influences[user] = influence;
        }
        
        file.close();
        cout << "Influence data loaded successfully." << endl;
    }
    
    void findLongestInfluencePath() {
        int maxLength = 0;
        int startNode = -1;
        bool visited[MAX_NODES] = {false};
        
        cout << "\nComputing longest influence chain..." << endl;
        
        // Try all nodes as starting points
        for (int i = 0; i < graph->getNodeCount(); i++) {
            int length = dfs(i, visited);
            if (length > maxLength) {
                maxLength = length;
                startNode = i;
            }
        }
        
        cout << "\n=== Longest Influence Chain (Part 2) ===" << endl;
        cout << "Maximum chain length: " << maxLength << endl;
        cout << "Chain: ";
        
        // Reconstruct and print the path
        int current = startNode;
        int count = 0;
        while (current != -1 && count < maxLength) {
            cout << current << " (inf:" << influences[current] << ")";
            if (parent[current] != -1) cout << " -> ";
            current = parent[current];
            count++;
        }
        cout << endl;
    }
};

int main() {
    Graph graph;
    
    cout << "=====================================" << endl;
    cout << "  Social Network Analysis - DAA Project" << endl;
    cout << "=====================================" << endl;
    cout << "\nLoading graph from file..." << endl;
    
    // Load graph from file
    ifstream graphFile("social-network-proj-graph.txt");
    if (!graphFile.is_open()) {
        cerr << "Error: Cannot open graph file 'social-network-proj-graph.txt'" << endl;
        cerr << "Please ensure the file is in the same directory as the executable." << endl;
        return 1;
    }
    
    int u, v, weight;
    int edgeCount = 0;
    while (graphFile >> u >> v >> weight) {
        graph.addEdge(u, v, weight);
        edgeCount++;
        if (edgeCount % 10000 == 0) {
            cout << "  Loaded " << edgeCount << " edges..." << endl;
        }
    }
    graphFile.close();
    
    cout << "\nGraph loaded successfully!" << endl;
    graph.printGraphStats();
    
    // Part 1: Dijkstra and A* comparison
    cout << "\n=====================================" << endl;
    cout << "  Part 1: Shortest Path Algorithms" << endl;
    cout << "=====================================" << endl;
    
    int source, destination;
    cout << "\nEnter source node (0-" << graph.getNodeCount()-1 << "): ";
    cin >> source;
    cout << "Enter destination node (0-" << graph.getNodeCount()-1 << "): ";
    cin >> destination;
    
    // Validate input
    if (source < 0 || source >= graph.getNodeCount() || 
        destination < 0 || destination >= graph.getNodeCount()) {
        cerr << "Error: Invalid node numbers!" << endl;
        return 1;
    }
    
    int distDijkstra[MAX_NODES];
    int parentDijkstra[MAX_NODES];
    int distAStar[MAX_NODES];
    int parentAStar[MAX_NODES];
    
    // Dijkstra's Algorithm
    cout << "\nRunning Dijkstra's Algorithm..." << endl;
    clock_t startDijkstra = clock();
    graph.dijkstra(source, destination, distDijkstra, parentDijkstra);
    clock_t endDijkstra = clock();
    double timeDijkstra = double(endDijkstra - startDijkstra) / CLOCKS_PER_SEC * 1000;
    
    cout << "\n--- Dijkstra's Algorithm Results ---" << endl;
    if (distDijkstra[destination] == INF) {
        cout << "No path exists between " << source << " and " << destination << endl;
    } else {
        cout << "Shortest distance: " << distDijkstra[destination] << endl;
        graph.printPath(source, destination, parentDijkstra);
    }
    cout << "Execution time: " << timeDijkstra << " ms" << endl;
    
    // A* Algorithm
    cout << "\nRunning A* Algorithm..." << endl;
    clock_t startAStar = clock();
    graph.aStar(source, destination, distAStar, parentAStar);
    clock_t endAStar = clock();
    double timeAStar = double(endAStar - startAStar) / CLOCKS_PER_SEC * 1000;
    
    cout << "\n--- A* Algorithm Results ---" << endl;
    if (distAStar[destination] == INF) {
        cout << "No path exists between " << source << " and " << destination << endl;
    } else {
        cout << "Shortest distance: " << distAStar[destination] << endl;
        graph.printPath(source, destination, parentAStar);
    }
    cout << "Execution time: " << timeAStar << " ms" << endl;
    
    cout << "\n--- Performance Comparison ---" << endl;
    cout << "Dijkstra time: " << timeDijkstra << " ms" << endl;
    cout << "A* time:       " << timeAStar << " ms" << endl;
    cout << "Difference:    " << abs(timeDijkstra - timeAStar) << " ms" << endl;
    
    if (timeDijkstra < timeAStar) {
        cout << "Result: Dijkstra was faster" << endl;
        if (timeAStar > 0) {
            cout << "Speedup: " << (timeAStar / timeDijkstra) << "x" << endl;
        }
    } else if (timeAStar < timeDijkstra) {
        cout << "Result: A* was faster" << endl;
        if (timeDijkstra > 0) {
            cout << "Speedup: " << (timeDijkstra / timeAStar) << "x" << endl;
        }
    } else {
        cout << "Result: Both algorithms took the same time" << endl;
    }
    
    // Part 2: Dynamic Programming for longest influence chain
    cout << "\n=====================================" << endl;
    cout << "  Part 2: Dynamic Programming" << endl;
    cout << "=====================================" << endl;
    
    InfluenceAnalyzer analyzer(&graph);
    analyzer.loadInfluences("social-network-proj-Influences.txt");
    
    clock_t startDP = clock();
    analyzer.findLongestInfluencePath();
    clock_t endDP = clock();
    double timeDP = double(endDP - startDP) / CLOCKS_PER_SEC * 1000;
    
    cout << "Execution time: " << timeDP << " ms" << endl;
    
    cout << "\n=====================================" << endl;
    cout << "  Analysis Complete!" << endl;
    cout << "=====================================" << endl;
    
    return 0;
}
