#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>

using namespace std;

#define N 6

vector <vector <int>> initial (N, vector <int> (N));

bool isValid(vector <vector <int>> matrix)
{

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (matrix[i][j] == 1)
            {
                int x = i;
                int y = j;

                while (x>0 && y>0)
                {
                    x--;
                    y--;
                    if(matrix[x][y] == 1)
                    {
                        return false;
                    }
                }

                x = i;
                y = j;

                while (x>0 && y<N-1)
                {
                    x--;
                    y++;
                    if(matrix[x][y] == 1)
                    {
                        return false;
                    }
                }

                x = i;
                y = j;

                while (x<N-1 && y>0)
                {
                    x++;
                    y--;
                    if(matrix[x][y] == 1)
                    {
                        return false;
                    }
                }

                x = i;
                y = j;

                while (x<N-1 && y<N-1)
                {
                    x++;
                    y++;
                    if(matrix[x][y] == 1)
                    {
                        return false;
                    }
                }

                for (x=0; x < N; x++)
                {
                    if (x == i || x == j)
                    {
                        continue;
                    }
                    if(matrix[i][x] == 1 || matrix[x][j] == 1)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

vector <vector <vector <int>>> moveGen(vector <vector <int>> matrix, set <vector <vector <int>>> &visited)
{
    vector <vector <vector <int>>> list;
    vector <vector <vector <int>>> moves;
    vector <vector <int>> temp = matrix;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (temp[i][j] == 0)
            {
                temp[i][j] = 1;
                if(isValid(temp))
                {
                    list.push_back(temp);
                }
                temp[i][j] = 0;
            }
        }
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

void print(vector <vector <int>> matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

//defining goal state
bool GoalState(vector <vector <int>> matrix)
{
    if (isValid(matrix))
    {
        int ctr = 0;
        for (int i=0; i<N; i++)
        {
            for (int j=0; j<N; j++)
            {
                if (matrix[i][j] == 1)
                {
                    ctr++;
                }
            }
        }
        if (ctr == N)
        {
            return true;
        }
    }
    return false;
}

int main ()
{
    //create a set to store visited states
    set <vector <vector <int>>> visited;

    /***********************Implementing DFS*********************/
    stack <vector <vector <int>>> st;
    st.push(initial);
    cout << "Searching state space using DFS algorithm...\n";
    int dfsCount = 0;
    bool solution = false;
    while (!st.empty())
    {
        vector <vector <int>> curr = st.top();
        st.pop();

        if (GoalState(curr))
        {
            solution = 1;
            dfsCount++;
            cout << "Solution state: " << endl;
            print(curr);
            cout << "Total number of states explored during dfs are: " << dfsCount << endl;
            break ;
        }
        
        visited.insert(curr);
        dfsCount++;
        vector <vector <vector <int>>> list;
        list = moveGen(curr, visited);

        for (int i = 0 ; i < list.size(); i++)
        {
            st.push(list[i]);
        }
    }
    if (!solution)
    {
        cout << "No solution possible for " << N << "-Queen problem";
    }

    /***********************Implementing BFS*********************/
    //reset visited data structure
    visited.clear();

    //create a queue to hold states
    queue <vector <vector <int>>> q;
    q.push(initial);
    cout << "Searching state space using BFS algorithm...\n";
    int bfsCount = 0;
    solution = false;
    while (!st.empty())
    {
        vector <vector <int>> curr = q.front();
        q.pop();

        if (GoalState(curr))
        {
            solution = 1;
            bfsCount++;
            cout << "Solution state: " << endl;
            print(curr);
            cout << "Total number of states explored during bfs are: " << bfsCount << endl;
            break ;
        }
        
        visited.insert(curr);
        bfsCount++;
        vector <vector <vector <int>>> list;
        list = moveGen(curr, visited);

        for (int i = 0 ; i < list.size(); i++)
        {
            q.push(list[i]);
        }
    }
    if (!solution)
    {
        cout << "No solution possible for " << N << "-Queen problem";
    }
    return 0;
}