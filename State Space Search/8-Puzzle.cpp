#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>

using namespace std;

//-1 represents blank
vector<vector<int>> initial = {{6, -1, 2}, {1, 8, 4}, {7, 3, 5}};

//generates all possible moves from current state
vector <vector <vector <int>>> moveGen(vector <vector <int>> matrix, set <vector <vector <int>>> &visited){
    vector <vector <vector <int>>> list;
    vector <vector <vector <int>>> moves;
    vector <vector <int>> temp = matrix;

    if (matrix[0][0] == -1)
    {
        swap(temp[0][0], temp[0][1]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[0][0], temp[1][0]);
        list.push_back(temp);
        temp = matrix;
    }
    else if (matrix[0][1] == -1)
    {
        swap(temp[0][1], temp[0][0]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[0][1], temp[1][1]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[0][1], temp[0][2]);
        list.push_back(temp);
        temp = matrix;
    }
    else if (matrix[0][2] == -1)
    {
        swap(temp[0][2], temp[0][1]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[0][2], temp[1][2]);
        list.push_back(temp);
        temp = matrix;
    }
    else if (matrix[1][0] == -1)
    {
        swap(temp[1][0], temp[0][0]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[1][0], temp[1][1]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[1][0], temp[2][0]);
        list.push_back(temp);
        temp = matrix;
    }
    else if (matrix[1][1] == -1)
    {
        swap(temp[1][1], temp[1][0]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[1][1], temp[0][1]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[1][1], temp[2][1]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[1][1], temp[1][2]);
        list.push_back(temp);
        temp = matrix;
    }
    else if (matrix[1][2] == -1)
    {
        swap(temp[1][2], temp[0][2]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[1][2], temp[1][1]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[1][2], temp[2][2]);
        list.push_back(temp);
        temp = matrix;        
    }
    else if (matrix[2][0] == -1)
    {
        swap(temp[2][0], temp[1][0]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[2][0], temp[2][1]);
        list.push_back(temp);
        temp = matrix;        
    }
    else if (matrix[2][1] == -1)
    {
        swap(temp[2][1], temp[1][1]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[2][1], temp[2][0]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[2][1], temp[2][2]);
        list.push_back(temp);
        temp = matrix;        
    }
    else
    {
        swap(temp[2][2], temp[1][2]);
        list.push_back(temp);
        temp = matrix;
        swap(temp[2][2], temp[2][1]);
        list.push_back(temp);
        temp = matrix;           
    }

    for (int i = 0 ; i < list.size(); i++)
    {
        auto it = visited.find(list[i]);
        if (it == visited.end())
        {
            moves.push_back(list[i]);
        }
    }

    return moves;
}

//defining goal state
bool GoalState(vector <vector <int>> matrix)
{
    return (matrix[0][0] == 1 && matrix[0][1] == 2 && matrix[0][2] == 3 && matrix[1][2] == 4 && matrix[2][2] == 5 && matrix[2][1] == 6 && matrix[2][0] == 7 && matrix[1][0] == 8);
}

void print(vector <vector <int>> matrix)
{
    for (int i = 0 ; i < matrix.size(); i++)
    {
        for (int j = 0 ; j < matrix[0].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
    }
    cout << endl;
}

int main()
{
    //create a set to store visited states
    set <vector <vector <int>>> visited;

    /***********************Implementing BFS*********************/

    //create a queue to hold states
    queue <vector <vector <int>>> q;
    q.push(initial);
    cout << "Searching state space using BFS algorithm...\n";
    int bfsCount = 0;
    while (!q.empty())
    {
        vector <vector <int>> curr = q.front();
        q.pop();

        if (GoalState(curr))
        {
            bfsCount++;
            print(curr);
            break ;
        }
        
        visited.insert(curr);
        print(curr);
        bfsCount++;
        vector <vector <vector <int>>> list;
        list = moveGen(curr, visited);

        for (int i = 0 ; i < list.size(); i++)
        {
            q.push(list[i]);
        }
    }

    /***********************Implementing DFS*********************/

    //reset visited data structure
    visited.clear();

    //create a stack to hold states
    stack <vector <vector <int>>> st;
    st.push(initial);
    cout << "Searching state space using DFS algorithm...\n";
    int dfsCount = 0;
    while (!st.empty())
    {
        vector <vector <int>> curr = st.top();
        st.pop();

        if (GoalState(curr))
        {
            dfsCount++;
            print(curr);
            break ;
        }
        
        visited.insert(curr);
        print(curr);
        dfsCount++;
        vector <vector <vector <int>>> list;
        list = moveGen(curr, visited);

        for (int i = 0 ; i < list.size(); i++)
        {
            st.push(list[i]);
        }
    }

    cout << "Total number of states explored during bfs are: " << bfsCount << endl;
    cout << "Total number of states explored during dfs are: " << dfsCount << endl;

    return 0;
}