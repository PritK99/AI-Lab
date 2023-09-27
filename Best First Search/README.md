# Best First Search


## Introduction

Unlike DFS and BFS, which are uninformed search, we choose the best possible option of the given moves in Best First Search. This is achieved by using a heuristic function ```h(x)``` which determines the similarity of current state with goal state. 

For example, while solving maze, we might prefer left follow rule over right follow rule if we know that the end is at the top-left of maze. Thus, at every junction we arrive in the maze, the one which leads us to left seems the best option to choose first.

## Results
Consider ```8-Puzzle``` problem with initial configuration as 
```cpp
//-1 represents blank
vector<vector<int>> initial = {{6, -1, 2}, {1, 8, 4}, {7, 3, 5}};
```

* No. of states explored using BFS: ```2428```
* No. of states explored using DFS: ```75333```
* No. of states explored using heuristic function 1: ```653```
* No. of states explored using heuristic function 2: ```27```