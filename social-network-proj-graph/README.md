# Social Network Analysis - DAA Project

## Project Description

This project implements graph-based algorithms and dynamic programming to analyze social network data.

### Part 1: Graph-Based Shortest Path Algorithms
- **Dijkstra's Algorithm**: Finds the shortest path between two users
- **A* Algorithm**: Uses heuristic (node degree) to optimize pathfinding
- **Performance Comparison**: Measures and compares execution times

### Part 2: Dynamic Programming
- Finds the longest chain of influence where each user's influence score is strictly greater than the previous user

## Implementation Details

### Data Structures
- **Graph**: Adjacency list using linked list (no vectors/maps)
- **Arrays**: Fixed-size arrays for storing distances, parents, and influences
- **Custom Edge structure**: Using pointers for linked list implementation

### Algorithms
1. **Dijkstra's Algorithm**: Classic shortest path with O(V²) complexity
2. **A* Algorithm**: Heuristic-based search using h(n) = degree of node
3. **Dynamic Programming**: DFS with memoization for longest increasing path

## Compilation

### Using g++:
```bash
g++ -o social_network main.cpp
```

### Using MinGW (Windows):
```bash
g++ -o social_network.exe main.cpp
```

### Using Visual Studio:
Create a new C++ console project and add `main.cpp` to it.

## Running the Program

### Make sure these files are in the same directory:
- main.cpp
- social-network-proj-graph.txt
- social-network-proj-Influences.txt

### Execute:
```bash
./social_network      # Linux/Mac
social_network.exe    # Windows
```

### Input:
The program will prompt you to enter:
1. Source node (e.g., 0)
2. Destination node (e.g., 1000)

### Sample Run:
```
Enter source node: 0
Enter destination node: 1000
```

## Output

The program provides:
1. **Dijkstra's Results**: 
   - Shortest distance
   - Complete path
   - Execution time

2. **A* Results**:
   - Shortest distance
   - Complete path
   - Execution time

3. **Performance Comparison**:
   - Time difference between algorithms

4. **Longest Influence Chain**:
   - Maximum chain length
   - Complete sequence of users with influence scores

## Features

✅ No vectors or maps used (as per requirements)
✅ Undirected graph implementation
✅ Efficient adjacency list using arrays and pointers
✅ Heuristic function: h(n) = degree of node
✅ Dynamic programming with DFS and memoization
✅ Execution time measurement
✅ Complete path reconstruction

## Notes

- The program handles up to 40,001 nodes and 120,001 edges
- Memory is managed manually (no STL containers)
- Graph is loaded from file at runtime
- All algorithms use optimal space complexity given the constraints
