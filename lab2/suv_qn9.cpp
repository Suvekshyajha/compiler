#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cctype>

using namespace std;

struct Quadruple
{
    string op, arg1, arg2, result;
};

vector<Quadruple> quadList;

unordered_map<string, double> constTable;

bool isNumber(const string& s)
{
    if (s.empty())
        return false;

    for (char c : s)
    {
        if (!isdigit(c) && c != '.' && c != '-')
            return false;
    }

    return true;
}

void optimize()
{
    bool modified = true;

    while (modified)
    {
        modified = false;

        for (auto& quad : quadList)
        {
            // Constant propagation
            if (constTable.count(quad.arg1))
            {
                quad.arg1 = to_string(constTable[quad.arg1]);
                modified = true;
            }

            if (constTable.count(quad.arg2))
            {
                quad.arg2 = to_string(constTable[quad.arg2]);
                modified = true;
            }

            // Constant folding
            if (isNumber(quad.arg1) && isNumber(quad.arg2))
            {
                double a = stod(quad.arg1);
                double b = stod(quad.arg2);
                double res;

                if (quad.op == "+")
                    res = a + b;
                else if (quad.op == "-")
                    res = a - b;
                else if (quad.op == "*")
                    res = a * b;
                else if (quad.op == "/" && b != 0)
                    res = a / b;
                else
                    continue;

                quad.op = "=";
                quad.arg1 = to_string(res);
                quad.arg2 = "";

                constTable[quad.result] = res;

                modified = true;
            }

            // Direct constant assignment
            else if (quad.op == "=" && isNumber(quad.arg1))
            {
                double value = stod(quad.arg1);

                if (!constTable.count(quad.result) ||
                    constTable[quad.result] != value)
                {
                    constTable[quad.result] = value;
                    modified = true;
                }
            }

            // Non-constant assignment invalidates the variable
            else if (quad.op == "=")
            {
                constTable.erase(quad.result);
            }

            // Non-constant expression also invalidates the result
            else if (quad.op == "+" || quad.op == "-" ||
                     quad.op == "*" || quad.op == "/")
            {
                constTable.erase(quad.result);
            }
        }
    }
}

int main()
{
    // t1 = 4 + 5
    // t2 = t1 * 2
    // x = t2 + y

    quadList =
    {
        {"+", "4", "5", "t1"},
        {"*", "t1", "2", "t2"},
        {"+", "t2", "y", "x"}
    };

    optimize();

    cout << "Optimized Quadruples:\n";

    for (const auto& q : quadList)
    {
        cout << q.result << " "
             << q.op << " "
             << q.arg1;

        if (!q.arg2.empty())
            cout << " " << q.arg2;

        cout << "\n";
    }

    cout << "\nLab No.: 2\n";
    cout << "Name: Suvekshya Jha\n";
    cout << "Roll No.: 80117729\n";

    return 0;
}