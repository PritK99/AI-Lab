# State Space Search

## Introduction

<img src = "../assets/State-Space-Search.png" alt="State-Space-Search">

## Results

1. <b>Vacuum Cleaner Agent</b>

The environment is created randomly. Even the initial state is choosen randomly. In general, DFS outperforms BFS.

2. <b>Water Jug problem</b>

Consider input as

```cpp
Enter capacity of Jug1: 3
Enter capacity of Jug2: 5
Enter the target value: 4
```

* Total number of states explored during bfs are: ```15```
* Total number of states explored during dfs are: ```12```

3. <b>8-Puzzle</b>
Consider initial configuration as 
```cpp
//-1 represents blank
vector<vector<int>> initial = {{6, -1, 2}, {1, 8, 4}, {7, 3, 5}};
```

* No. of states explored using BFS: ```2428```
* No. of states explored using DFS: ```75333```

4. <b>N-Queens Problem</b>
Consider N as ```6```

* No. of states explored using BFS: ```60190```
* No. of states explored using DFS: ```251```

Output: 
```0 1 0 0 0 0
0 0 0 1 0 0
0 0 0 0 0 1
1 0 0 0 0 0
0 0 1 0 0 0
0 0 0 0 1 0 
```



