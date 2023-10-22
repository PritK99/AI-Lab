#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class SATGenerator
{
    public:
    int num_var;
    int num_clauses;
    
    SATGenerator(int num_var, int num_clauses)
    {
        this->num_var = num_var;
        this->num_clauses = num_clauses;
    }
    void generate()
    {
        vector <bool> mask (num_var);

        for (int i = 0; i < num_clauses; i++)
        {
            vector <int> temp ;
            while(temp.size() <= 3) // 3-SAT
            {
                int x = rand() % num_var;
                bool flag = 0;
                for (int i = 0; i < temp.size(); i++)
                {
                    if (temp[i] == x)
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 1)
                {
                    continue;
                }
                cout << "pass";
                temp.push_back(x);
            }

            //Print the clauses generated
            for (int i = 0; i < 3; i++)
            {
                cout << temp[i] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    srand(time(0));
    SATGenerator SG(3,1);
    SG.generate();
    return 0;
}