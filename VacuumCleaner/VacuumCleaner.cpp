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
    vector <vector <int>> original;
    Environment(int row, int col)
    {
        this->row = row+2;
        this->col = col+2;
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

//creates an environment randomly with clean tiles as 0, dirty tiles as 1 and obstacles as 2. Also creates a padding around the grid.
void Environment :: createEnvironment()
{
    vector <int> pad (col);
    fill(pad.begin(), pad.end(), 2);

    grid.push_back(pad);
    for (int i = 1 ; i < row-1 ; i++)
    {
        vector <int> temp;
        temp.push_back(2);
        for (int j = 1 ; j < col-1; j++)
        {
            if (i == 1 && j ==1)
            {
                //atleast one cell is unclean
                temp.push_back(1);
                continue;
            }
            temp.push_back(rand()%3);
        }
        temp.push_back(2);
        grid.push_back(temp);
    }
    grid.push_back(pad);

    original = grid;
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
    init_x = rand()%(e.row-2) + 1;
    init_y = rand()%(e.col-2) + 1;
    while (e.grid[init_x][init_y] == 2)
    {
        init_x = rand()%(e.row-2) + 1;
        init_y = rand()%(e.col-2) + 1;
    }
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

    //left cell
    if (e.grid[agent.x-1][agent.y] != 2)
    {
        temp[0] = agent.x-1;
        temp[1] = agent.y;
        list.push_back(temp);
    }
    //top cell
    if (e.grid[agent.x][agent.y-1] != 2)
    {
        temp[0] = agent.x;
        temp[1] = agent.y-1;
        list.push_back(temp);
    }
    //right cell
    if (e.grid[agent.x+1][agent.y] != 2)
    {
        temp[0] = agent.x+1;
        temp[1] = agent.y;
        list.push_back(temp);
    }
    //bottom cell
    if (e.grid[agent.x][agent.y+1] != 2)
    {
        temp[0] = agent.x;
        temp[1] = agent.y+1;
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
    cout << "The initial environment is:\n";
    e.printEnvironment();

    //agent is created and placed randomly in the environment
    Agent agent;
    agent.createAgent(e);
    cout << "The initial position of agent is:\n";
    agent.printPosition();

    //creating a set to hold visited cells
    set <vector <int>> visited ;
    vector <int> initial = {agent.init_x, agent.init_y};

    /***********************Implementing BFS*********************/

    //create a queue to hold states
    queue <vector <int>> q;
    q.push(initial);
    cout << "Searching state space using BFS algorithm...\n";
    int bfsCount = 0;
    bool isFound = 0;
    while (!q.empty())
    {
        vector <int> curr = q.front();
        q.pop();
        
        visited.insert(curr);

        //cleaning the cell
        e.grid[curr[0]][curr[1]] = 0;
        bfsCount++;
        agent.x = curr[0];
        agent.y = curr[1];
        vector <vector <int>> list;
        list = moveGen(agent, e, visited);

        for (int i = 0 ; i < list.size(); i++)
        {
            q.push(list[i]);
        }

        if (GoalState(e.grid))
        {
            bfsCount++;
            e.printEnvironment();
            isFound = 1;
            break;
        }
    }
    if (isFound)
    {
        cout << "Total time required to clean the gird using BFS is: " << bfsCount << endl;
    }
    else
    {
        cout << "The above grid can not be cleaned completely due to obstacles\n";
        e.printEnvironment();
    }

    //reset visited matrix and grid
    visited.clear();
    e.grid = e.original;

    /***********************Implementing DFS*********************/

    //create a stack to hold states
    stack <vector <int>> st;
    st.push(initial);
    cout << "Searching state space using DFS algorithm...\n";
    int dfsCount = 0;
    isFound = 0;
    while (!st.empty())
    {
        vector <int> curr = st.top();
        st.pop();
        
        visited.insert(curr);

        //cleaning the cell
        e.grid[curr[0]][curr[1]] = 0;
        dfsCount++;
        agent.x = curr[0];
        agent.y = curr[1];
        vector <vector <int>> list;
        list = moveGen(agent, e, visited);

        for (int i = 0 ; i < list.size(); i++)
        {
            st.push(list[i]);
        }

        if (GoalState(e.grid))
        {
            dfsCount++;
            e.printEnvironment();
            isFound = 1;
            break;
        }
    }
    if (isFound)
    {
        cout << "Total time required to clean the gird using DFS is: " << dfsCount << endl;
    }
    else
    {
        cout << "The above grid can not be cleaned completely due to obstacles\n";
        e.printEnvironment();
    }

    return 0;
}