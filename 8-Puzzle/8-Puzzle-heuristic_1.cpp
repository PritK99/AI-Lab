#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>

using namespace std;

//ideal matrix for comparisons
vector <vector <int>> ideal_matrix = {{1,2,3},{8,-1,4}, {7,6,5}};

//-1 represents blank
vector<vector<int>> initial = {{6, -1, 2}, {1, 8, 4}, {7, 3, 5}};

//heuristic function to calculate misplaced tiles
int heuristic(vector <vector <int>> matrix)
{
    int miss = 0;
    for (int i = 0 ; i < matrix.size(); i++)
    {
        for (int j = 0 ; j < matrix[0].size(); j++)
        {
            if (matrix[i][j] != ideal_matrix[i][j])
            {
                miss++;
            }
        }
    }
    return miss;
}

//generates all possible moves from current state
vector <pair <int, vector <vector<int>>>> moveGen(vector <vector <int>> matrix, set <vector <vector <int>>> &visited){
    vector <vector <vector <int>>> list;
    vector <pair <int, vector <vector<int>>>> moves;
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
            pair <int, vector <vector<int>>> temp;
            int x = heuristic(list[i]);
            temp.first = -x;
            temp.second = list[i];
            moves.push_back(temp);
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

    //create a priority queue to hold states
    priority_queue <pair <int, vector <vector<int>>>> pq;
    int x = heuristic(initial);
    pair <int, vector <vector<int>>> temp;
    temp.first = -x;
    temp.second = initial;
    pq.push(temp);
    cout << "Searching state space using heuristic function 1...\n";
    int bfsCount = 0;
    while (!pq.empty())
    {
        pair <int, vector <vector<int>>> curr = pq.top();
        pq.pop();

        if (GoalState(curr.second))
        {
            bfsCount++;
            print(curr.second);
            break ;
        }
        
        visited.insert(curr.second);
        print(curr.second);
        bfsCount++;
        vector <pair <int, vector <vector<int>>>> list;
        list = moveGen(curr.second, visited);

        for (int i = 0 ; i < list.size(); i++)
        {
            pq.push(list[i]);
        }
    }

    cout << "Total number of states explored during heuristic function 1 are: " << bfsCount << endl;

    return 0;
}