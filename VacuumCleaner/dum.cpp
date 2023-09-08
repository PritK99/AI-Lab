#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>

using namespace std;

class Environment{
    public:
    int row;
    int col;
    vector <vector <int>> grid;
    Environment(int row, int col)
    {
        this->row = row;
        this->col = col;
    }
    void createEnvironment();
    void printEnvironment();
};

class Agent{
    public:
    int init_x;
    int init_y;
    int x;
    int y;
    void createAgent(Environment e);
    void printPosition();
};

//creates an environment randomly with clean tiles as 0 and dirty tiles as 1
void Environment :: createEnvironment()
{
    for (int i = 0 ; i < row ; i++)
    {
        vector <int> temp;
        for (int j = 0 ; j < col; j++)
        {
            temp.push_back(rand()%2);
        }
        grid.push_back(temp);
    }
}

//prints the current environment
void Environment :: printEnvironment()
{
    for (int i = 0 ; i < row ; i++)
    {
        for (int j = 0 ; j < col; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

//places the agent randomly in the environment
void Agent :: createAgent(Environment e)
{
    init_x = rand()%e.row ;
    init_y = rand()%e.col;
    x = init_x;
    y = init_y;
}

//prints the current position of agent
void Agent :: printPosition()
{
    cout << "The agent is at (" << x << ", " << y << ")" << endl;
}

bool GoalState(vector <vector <int>> grid)
{
    for (int i = 0 ; i < grid.size() ; i++)
    {
        for (int j = 0 ; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 1)
            {
                return false;
            }
        }
    }  
    return true;
}

//generates all possible moves from current state
vector <vector <int>> moveGen(Agent agent, Environment e, set <vector <int>> &visited){
    vector <vector <int>> list;
    vector <vector <int>> moves;
    vector <int> temp(2);

    //corner cases
    if (agent.x == 0 && agent.y == 0)
    {
        temp[0] = agent.x;
        temp[1] = agent.y + 1;
        list.push_back(temp);
        temp[0] = agent.x + 1;
        temp[1] = agent.y;
        list.push_back(temp);
    }
    else if (agent.x == e.row - 1 && agent.y == e.col - 1)
    {
        temp[0] = agent.x - 1;
        temp[1] = agent.y;
        list.push_back(temp);
        temp[0] = agent.x;
        temp[1] = agent.y - 1;
        list.push_back(temp);
    }
    else if (agent.x == e.row - 1 && agent.y == 0)
    {
        temp[0] = agent.x;
        temp[1] = agent.y + 1;
        list.push_back(temp);
        temp[0] = agent.x - 1;
        temp[1] = agent.y;
        list.push_back(temp);
    }
    else if (agent.x == 0 && agent.y == e.col - 1)
    {
        temp[0] = agent.x;
        temp[1] = agent.y - 1;
        list.push_back(temp);
        temp[0] = agent.x + 1;
        temp[1] = agent.y;
        list.push_back(temp);
    }
    //boundary cases
    else if (agent.x == 0)
    {
        temp[0] = agent.x;
        temp[1] = agent.y - 1;
        list.push_back(temp);
        temp[0] = agent.x + 1;
        temp[1] = agent.y;
        list.push_back(temp);
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

int main()
{
    srand(time(0));
    int row = (rand()%10) + 1;
    int col = (rand()%10) + 1;

    //the environment is created randomly such that the agent is unaware of the geography of the environment
    Environment e(row, col);
    e.createEnvironment();

    //agent is created and placed randomly in the environment
    Agent agent;
    agent.createAgent(e);

    //creating a set to hold visited cells
    set <vector <int>> visited ;
    vector <int> initial = {agent.init_x, agent.init_y};
    /***********************Implementing BFS*********************/

    // //create a queue to hold states
    // queue <vector <int>> q;
    // vector <int> initial = {0,0};
    // q.push(initial);
    // cout << "Searching state space using BFS algorithm...\n";
    // int bfsCount = 0;
    // while (!q.empty())
    // {
    //     vector <int> curr = q.front();
    //     q.pop();

    //     if (GoalState(e.grid))
    //     {
    //         bfsCount++;
    //         e.printEnvironment();
    //         break;
    //     }
        
    //     visited.insert(curr);
    //     bfsCount++;
    //     agent.x = curr[0];
    //     agent.y = curr[1];
    //     vector <vector <int>> list;
    //     list = moveGen(visited);

    //     for (int i = 0 ; i < list.size(); i++)
    //     {
    //         q.push(list[i]);
    //     }
    // }

    // cout << "Total number of states explored during bfs are: " << bfsCount << endl;

    //print and debug
    e.printEnvironment();
    agent.printPosition();

    return 0;
}