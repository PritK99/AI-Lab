#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std ;

class Jug{
    public:
    int capacity;
    int current;
    Jug(int capacity)
    {
        this->capacity = capacity;
        this->current = 0;
    }
};

//this will pour contents of Jug1 to Jug2
void pour(Jug *from, Jug *to, vector <int> &temp, bool flag = 0)
{
    int c = min(from->current, to->capacity - to->current);
    if (flag == 0)
    {
        temp[0] = from->current - c;
        temp[1] = to->current + c;
    }
    else
    {
        temp[0] = to->current + c;
        temp[1] = from->current - c;        
    }

}

//generates all possible moves from current state
vector <vector <int>> moveGen(Jug *J1, Jug *J2, vector <int> curr, vector <vector <int>> &visited){
    vector <vector <int>> list;
    vector <vector <int>> moves;
    //empty Jug1
    if (J1->current != 0)
    {
        vector <int> temp = {0, J2->current};
        list.push_back(temp);
    }
    //empty Jug2
    if (J2->current != 0)
    {
        vector <int> temp = {J1->current, 0};
        list.push_back(temp);
    }
    //fill Jug1
    if (J1->current != J1->capacity)
    {
        vector <int> temp = {J1->capacity, J2->current};
        list.push_back(temp);
    }
    //fill Jug2
    if (J2->current != J2->capacity)
    {
        vector <int> temp = {J1->current, J2->capacity};
        list.push_back(temp);
    }
    //pour from Jug1 to Jug2
    if (J2->current != J2->capacity && J1->current != 0)
    {
        vector <int> temp (2);
        pour(J1, J2, temp);
        list.push_back(temp);
    }
    //pour from Jug2 to Jug1
    if (J1->current != J1->capacity && J2->current != 0)
    {
        vector <int> temp (2);
        pour(J2, J1, temp, 1);
        list.push_back(temp);
    }

    for (int i = 0 ; i < list.size(); i++)
    {
        if (visited[list[i][0]][list[i][1]] == 0)
        {
            moves.push_back(list[i]);
        }
    }

    return moves;
}

int main()
{
    int cap1, cap2, target;
    cout << "Enter capacity of Jug1: ";
    cin >> cap1;
    cout << "Enter capacity of Jug2: ";
    cin >> cap2;
    cout << "Enter the target value: ";
    cin >> target;

    //create two jugs of given capacity
    Jug J1(cap1), J2(cap2);

    //create a matrix to store visited states
    vector <vector <int>> visited (cap1+1, vector <int> (cap2+1,0));

    /***********************Implementing BFS*********************/

    //create a queue to hold states
    queue <vector <int>> q;
    vector <int> initial = {0,0};
    q.push(initial);
    cout << "Searching state space using BFS algorithm...\n";
    int bfsCount = 0;
    while (!(J1.current == target || J2.current == target) && !q.empty())
    {
        vector <int> curr = q.front();
        q.pop();
        
        visited[curr[0]][curr[1]] = 1;
        cout << curr[0] << " " << curr[1] << endl;
        bfsCount++;
        J1.current = curr[0];
        J2.current = curr[1];
        vector <vector <int>> list;
        list = moveGen(&J1, &J2, curr, visited);

        for (int i = 0 ; i < list.size(); i++)
        {
            q.push(list[i]);
        }
    }
    cout << "Total number of states explored during bfs are: " << bfsCount << endl;

    /***********************Implementing DFS*********************/

    //reset visited matrix
    for (int i = 0 ; i < visited.size(); i++)
    {
        for (int j = 0; j < visited[0].size(); j++)
        {
            visited[i][j] = 0;
        }
    }
    J1.current = 0;
    J2.current = 0;

    //create a queue to hold states
    stack <vector <int>> st;
    st.push(initial);
    cout << "Searching state space using DFS algorithm...\n";
    int dfsCount = 0;
    while (!(J1.current == target || J2.current == target) && !st.empty())
    {
        vector <int> curr = st.top();
        st.pop();
        
        visited[curr[0]][curr[1]] = 1;
        cout << curr[0] << " " << curr[1] << endl;
        dfsCount++;
        J1.current = curr[0];
        J2.current = curr[1];
        vector <vector <int>> list;
        list = moveGen(&J1, &J2, curr, visited);

        for (int i = 0 ; i < list.size(); i++)
        {
            st.push(list[i]);
        }
    }
    cout << "Total number of states explored during dfs are: " << dfsCount << endl;

    return 0;
}