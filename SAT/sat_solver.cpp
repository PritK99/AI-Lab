#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

class Generator
{
    public:
    int vars;
    int clauses;
    vector <vector<int>> expr;
    
    Generator(int vars, int clauses)
    {
        this->vars = vars;
        this->clauses = clauses;
    }
    void generate();
    void printExpr();
};

class Solver
{
    public:
    bool *assignment;
    vector <vector<int>> expr;

    Solver(int vars, vector <vector<int>> expr)
    {
        assignment = new bool[vars];
        for (int i = 0; i < vars; i++)
        {
            assignment[i]=0;
        }
        this->expr = expr;
    }
    void solve(int vars, vector <vector<int>> expr, int k);
    bool CheckCurrent();
};

void Generator::generate()
{
    while (expr.size() != clauses)
    {
        vector <int> temp;
        int counter = 0;
        vector <int> variables (vars);
        while(counter < 3)
        {
            int index = rand()%vars;
            if (variables[index] == 0)
            {
                int sign = rand()%2;
                if (sign == 0)
                {
                    temp.push_back(index);
                }
                else
                {
                    if (index == 0)
                    {
                        temp.push_back(INT_MIN);
                    }
                    else
                    {
                        temp.push_back(-index);
                    }
                }
                variables[index]=1;
                counter++;
            }
        }
        sort(temp.begin(), temp.end());
        bool flag = 0;
        for (int i = 0; i < expr.size(); i++)
        {
            if (temp == expr[i])
            {
                flag = 1;
            }
        }
        if (flag)
        {
            continue;
        }
        expr.push_back(temp);
    }
}

void Generator::printExpr()
{
    for (int i = 0; i < expr.size(); i++)
    {
        cout << "( " ;
        for (int j = 0; j < 3; j++)
        {
            if (expr[i][j] < 0)
            {
                if (expr[i][j] == INT_MIN)
                {
                    cout << "~" << char(97) << " ";
                }
                else
                {
                    cout << "~" << char(abs(expr[i][j])+97) << " ";
                }
            }
            else
            {
                cout << char(expr[i][j]+97) << " ";
            }
            if (j != 2)
            {
                cout << "v ";
            }
        }

        if (i != expr.size()-1)
        {
            cout << ") ^ ";
        }
        else
        {
            cout << ")";
        }
    }
    cout << endl;
}

void Solver::solve(int vars, vector <vector<int>> expr, int k)
{
    if (k == vars)
    {
        if(CheckCurrent())
        {
            for (int i = 0; i < vars; i++)
            {
                cout << assignment[i] << " ";
            }
            cout << endl;
        }
        return;
    }

    solve(vars, expr, k+1);
    assignment[k] = 1;
    solve(vars, expr, k+1);
    assignment[k] = 0;
}

bool Solver::CheckCurrent()
{
    for (int i = 0; i < expr.size(); i++)
    {
        bool a = 0, b = 0, c = 0;
        cout << "Hey: " << expr[i][0] << " " << expr[i][1] << " " << expr[i][2] << endl;
        if(expr[i][0] < 0)
        {
            if (expr[i][0] == INT_MIN)
            {
                a = ~assignment[0];
            }
            else
            {
                a = ~assignment[-expr[i][0]];
            }
        }
        else
        {
            a = assignment[expr[i][0]];
        }

        if(expr[i][1] < 0)
        {
            if (expr[i][0] == INT_MIN)
            {
                b = ~assignment[0];
            }
            else
            {
                b = ~assignment[-expr[i][1]];
            }
        }
        else
        {
            b = assignment[expr[i][1]];
        }

        if(expr[i][2] < 0)
        {
            if (expr[i][0] == INT_MIN)
            {
                c = ~assignment[0];
            }
            else
            {
                c = ~assignment[-expr[i][2]];
            }
        }
        else
        {
            c = assignment[expr[i][2]];
        }
        bool result = (a || b || c) ;
        cout << "Assignments: " << a << " " << b << " " << c << " " << result << endl;
        if (!result)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    srand(time(0));
    int vars, clauses;
    cout << "Please enter number of variables: ";
    cin >> vars;
    cout << "Please enter number of clauses: ";
    cin >> clauses;
    Generator G(vars,clauses);
    G.generate();
    G.printExpr();
    Solver S(vars, G.expr);
    S.solve(vars, G.expr, 0);
    return 0;
}