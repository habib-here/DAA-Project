# Quick Reference Guide

## Compilation
```bash
g++ -o social_network.exe main.cpp
```

## Run
```bash
./social_network.exe
```

## Sample Test Cases

### Test 1: Direct Connection
- Source: 0
- Destination: 4262
- Expected: 1-hop path with weight 35

### Test 2: Medium Path
- Source: 0
- Destination: 1000
- Expected: Multi-hop path

### Test 3: Random Nodes
- Source: 100
- Destination: 5000
- Expected: Various path lengths

## Algorithm Summary

### Dijkstra
- Classic shortest path
- Explores all nodes systematically
- Time: O(V²)

### A* (with h(n) = degree)
- Guided search using heuristic
- Explores fewer nodes
- Time: O(V²) worst case, but faster in practice
- Heuristic: Uses node degree (number of connections)

### Dynamic Programming
- Finds longest increasing influence chain
- Uses DFS + memoization
- Time: O(V + E)

## Output Files
None - all output to console

## Important Notes
1. All data files must be in the same directory
2. Node IDs range from 0 to 39999
3. Program shows detailed paths and timing
4. Both algorithms guarantee optimal paths
5. A* is typically faster due to heuristic guidance

## Expected Performance
- Dijkstra: 50-200 ms (depending on path length)
- A*: 30-150 ms (typically faster)
- DP: 100-500 ms (depends on graph density)

## Data Format

### Graph File (social-network-proj-graph.txt)
```
node1 node2 weight
0 4262 35
1 3822 41
...
```

### Influence File (social-network-proj-Influences.txt)
```
node influence_score
0 71
1 1
2 26
...
```

## Troubleshooting

**Q: Compilation error?**
A: Make sure g++ is installed and in PATH

**Q: File not found?**
A: Check that .txt files are in the same directory

**Q: Program crashes?**
A: Verify input nodes are in valid range (0-39999)

**Q: Very slow execution?**
A: Normal for large graphs - Dijkstra can take 100-200ms

## Success Criteria
✓ Graph loads successfully
✓ Both algorithms find the same shortest distance
✓ Path is displayed correctly
✓ Timing comparison is shown
✓ Longest influence chain is found
✓ All without using vector or map
