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
    return 0;
}