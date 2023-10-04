#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>

using namespace std;

//-1 represents blank
vector<vector<int>> initial = {{6, -1, 2}, {1, 8, 4}, {7, 3, 5}};

//heuristic function to calculate misplaced tiles
int heuristic(vector <vector <int>> matrix)
{
    int man_dist = 0;
    for (int i = 0 ; i < matrix.size(); i++)
    {
        for (int j = 0 ; j < matrix[0].size(); j++)
        {
            //find manhattan distance as per ideal matrix
            switch(matrix[i][j])
            {
                case(1):
                {
                    man_dist+=(abs(i-0)+abs(j-0));
                    break;
                }
                case(2):
                {
                    man_dist+=(abs(i-0)+abs(j-1));
                    break;
                }
                case(3):
                {
                    man_dist+=(abs(i-0)+abs(j-2));
                    break;
                }
                case(4):
                {
                    man_dist+=(abs(i-1)+abs(j-2));
                    break;
                }
                case(5):
                {
                    man_dist+=(abs(i-2)+abs(j-2));
                    break;
                }
                case(6):
                {
                    man_dist+=(abs(i-2)+abs(j-1));
                    break;
                }
                case(7):
                {
                    man_dist+=(abs(i-2)+abs(j-0));
                    break;
                }
                case(8):
                {
                    man_dist+=(abs(i-1)+abs(j-0));
                    break;
                }
                case(-1):
                {
                    man_dist+=(abs(i-1)+abs(j-1));
                    break;
                }           
            }
        }
    }
    return man_dist;
}

void print(vector <vector <int>> matrix, int heuristic)
{
    for (int i = 0 ; i < matrix.size(); i++)
    {
        for (int j = 0 ; j < matrix[0].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
    }
    cout << "| " << heuristic << endl;
}

//generates the current best neighbour
pair <int, vector <vector<int>>> moveGen(vector <vector <int>> matrix, set <vector <vector <int>>> &visited, int currScore){
    vector <vector <vector <int>>> list;
    pair <int, vector <vector<int>>> bestNeighbour;
    bestNeighbour.first = -1;
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
    int min = currScore;
    int index = -1;
    for (int i = 0 ; i < list.size(); i++)
    {
        auto it = visited.find(list[i]);
        if (it == visited.end())
        {
            int x = heuristic(list[i]);
            if (x <= min)
            {
                index = i;
                min = x;
            }
        }
    }
    if (index != -1)
    {
        bestNeighbour.first = min;
        bestNeighbour.second = list[index];
    }

    return bestNeighbour;
}

int main()
{
    //create a set to store visited states
    set <vector <vector <int>>> visited;
    int count = 0;
    cout << "Searching state space using hill climbing...\n";
    int x = heuristic(initial);
    pair <int, vector <vector<int>>> temp = moveGen(initial, visited, x);
    
    while (temp.first != -1)
    {
        print(temp.second, temp.first);
        visited.insert(temp.second);
        temp = moveGen(temp.second, visited, temp.first);
        count++;
    }

    cout << "Total number of states explored during hill climbing are: " << count << endl;

    return 0;
}