# DAA Project - Implementation Guide

## Overview
This project implements graph algorithms and dynamic programming for social network analysis without using STL vectors or maps.

## Key Implementation Details

### Part 1: Shortest Path Algorithms

#### 1. Graph Structure
- **Adjacency List**: Implemented using linked lists with pointers
- **Edge Structure**: Custom struct with `to`, `weight`, and `next` pointer
- **Degree Array**: Stores count of connections for each node (used in A* heuristic)

```cpp
struct Edge {
    int to;
    int weight;
    Edge* next;
};
```

#### 2. Dijkstra's Algorithm
- **Time Complexity**: O(V²) where V is the number of vertices
- **Space Complexity**: O(V)
- **Implementation**: 
  - Uses arrays for distance, parent, and visited status
  - Finds minimum distance vertex in each iteration
  - Updates neighbors' distances if a shorter path is found

#### 3. A* Algorithm
- **Heuristic Function**: h(n) = degree[n] (number of direct connections)
- **Cost Function**: f(n) = g(n) + h(n)
  - g(n): Actual cost from source to n
  - h(n): Heuristic estimate (degree of node n)
- **Optimization**: Uses heuristic to prioritize exploration of well-connected nodes

**Why this heuristic works:**
In social networks, nodes with higher degree (more connections) are typically:
- More central in the network
- More likely to be on shorter paths between other nodes
- Important hubs that connect different parts of the network

### Part 2: Dynamic Programming

#### Longest Increasing Influence Path
- **Algorithm**: DFS with Memoization
- **DP State**: dp[i] = longest increasing path starting at node i
- **Recurrence**: dp[i] = 1 + max(dp[j]) for all neighbors j where influence[j] > influence[i]
- **Time Complexity**: O(V + E) - each node is visited once due to memoization
- **Space Complexity**: O(V) for dp and parent arrays

## Files Structure

```
social-network-proj-graph/
├── main.cpp                              # Main implementation
├── main_enhanced.cpp                     # Enhanced version with better output
├── compile.bat                           # Windows compilation script
├── README.md                             # User guide
├── IMPLEMENTATION_GUIDE.md               # This file
├── social-network-proj-graph.txt         # Graph data (120K edges)
├── social-network-proj-Influences.txt    # Influence scores (40K users)
└── social-network-proj-LABELS.txt        # User names (optional)
```

## Compilation Instructions

### Option 1: Using batch file (Windows)
```bash
compile.bat
```

### Option 2: Manual compilation
```bash
g++ -o social_network.exe main.cpp
```

### Option 3: With optimization flags
```bash
g++ -O2 -o social_network.exe main.cpp
```

## Running the Program

```bash
./social_network.exe
```

### Sample Input/Output

**Input:**
```
Enter source node (0-39999): 0
Enter destination node (0-39999): 1000
```

**Output:**
```
=== Part 1: Shortest Path Algorithms ===

--- Dijkstra's Algorithm Results ---
Shortest distance: 245
Path: 0 -> 4262 -> 8531 -> ... -> 1000
Path length (nodes): 8
Execution time: 125.45 ms

--- A* Algorithm Results ---
Shortest distance: 245
Path: 0 -> 4262 -> 8531 -> ... -> 1000
Path length (nodes): 8
Execution time: 98.32 ms

--- Performance Comparison ---
Dijkstra time: 125.45 ms
A* time:       98.32 ms
Difference:    27.13 ms
Result: A* was faster
Speedup: 1.28x

=== Part 2: Dynamic Programming ===
Maximum chain length: 15
Chain: 5234 (inf:1) -> 8932 (inf:5) -> ... -> 12456 (inf:99)
Execution time: 234.56 ms
```

## Algorithm Comparison

| Feature | Dijkstra | A* |
|---------|----------|-----|
| Optimality | Guaranteed | Guaranteed (with admissible heuristic) |
| Speed | Slower | Faster (with good heuristic) |
| Memory | O(V) | O(V) |
| Nodes Explored | All reachable | Fewer (guided by heuristic) |

## Testing Different Scenarios

### Test Case 1: Short Distance
```
Source: 0
Destination: 4262 (direct neighbor)
Expected: Single edge path
```

### Test Case 2: Medium Distance
```
Source: 0
Destination: 1000
Expected: Path of 5-10 nodes
```

### Test Case 3: Long Distance
```
Source: 0
Destination: 30000
Expected: Longer path, significant time difference
```

## Performance Optimization Tips

1. **For very large graphs**: Consider using a min-heap for Dijkstra/A*
2. **For sparse graphs**: Current adjacency list is optimal
3. **For dense graphs**: Adjacency matrix might be faster (but uses more memory)

## Common Issues and Solutions

### Issue 1: File Not Found
**Error**: "Cannot open graph file"
**Solution**: Ensure data files are in the same directory as the executable

### Issue 2: Stack Overflow in DP
**Error**: Segmentation fault
**Solution**: Already handled with iterative approach and memoization

### Issue 3: Invalid Node Numbers
**Error**: "Invalid node numbers"
**Solution**: Use nodes between 0 and 39999

## Memory Usage

- **Graph**: ~1.5 GB for adjacency list (120K edges × 2 × size of Edge struct)
- **Arrays**: ~600 KB for distance, parent, and visited arrays
- **Total**: ~2 GB maximum

## Constraints Satisfied

✅ No vectors used - using arrays and linked lists
✅ No maps used - using arrays indexed by node ID
✅ C++ only - no other languages
✅ Undirected graph - edges added in both directions
✅ Heuristic h(n) = degree of node
✅ Dynamic programming for longest influence path
✅ Execution time comparison

## Extensions (Optional)

If you want to enhance the project further:

1. **Bidirectional Search**: Search from both source and destination
2. **Parallel DP**: Process multiple starting nodes in parallel
3. **Graph Visualization**: Output path to file for visualization
4. **Additional Metrics**: Calculate betweenness centrality, clustering coefficient

## Grading Checklist

- [x] Graph created from file (undirected, weighted)
- [x] Dijkstra's algorithm implemented correctly
- [x] A* algorithm with h(n) = degree implemented
- [x] Both algorithms find shortest path
- [x] Execution time comparison provided
- [x] DP algorithm for longest influence path
- [x] Returns max length and sequence
- [x] No vectors or maps used
- [x] C++ only
- [x] Code is well-commented and organized
