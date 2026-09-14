
#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

struct Quadruple
{
    string op, arg1, arg2, result;
};

vector<Quadruple> quadList;

int tempCount = 1;

string newTemp()
{
    return "t" + to_string(tempCount++);
}

bool isOperator(const string& s)
{
    return s == "+" || s == "-" || s == "*" || s == "/" ||
           s == "==" || s == ">" || s == "<" || s == "u-";
}

int precedence(const string& op)
{
    if (op == "u-") return 3;

    if (op == "*" || op == "/") return 2;

    if (op == "+" || op == "-") return 1;

    if (op == "==" || op == ">" || op == "<") return 0;

    return -1;
}

// Infix to Postfix using Shunting-Yard Algorithm
vector<string> infixToPostfix(const vector<string>& tokens)
{
    vector<string> output;
    stack<string> ops;

    bool expectOperand = true;

    for (string tok : tokens)
    {
        // Detect unary minus
        if (tok == "-" && expectOperand)
        {
            tok = "u-";
        }

        if (tok == "(")
        {
            ops.push(tok);
            expectOperand = true;
        }
        else if (tok == ")")
        {
            while (!ops.empty() && ops.top() != "(")
            {
                output.push_back(ops.top());
                ops.pop();
            }

            if (!ops.empty())
                ops.pop();

            expectOperand = false;
        }
        else if (isOperator(tok))
        {
            while (!ops.empty() &&
                   ops.top() != "(" &&
                   precedence(ops.top()) >= precedence(tok))
            {
                output.push_back(ops.top());
                ops.pop();
            }

            ops.push(tok);
            expectOperand = true;
        }
        else
        {
            output.push_back(tok);
            expectOperand = false;
        }
    }

    while (!ops.empty())
    {
        output.push_back(ops.top());
        ops.pop();
    }

    return output;
}

// Generate TAC in Quadruple Format
void generateTACFromPostfix(const vector<string>& tokens)
{
    stack<string> st;

    for (const auto& token : tokens)
    {
        if (isOperator(token))
        {
            // Unary minus
            if (token == "u-")
            {
                string arg1 = st.top();
                st.pop();

                string t = newTemp();

                quadList.push_back({"u-", arg1, "", t});

                st.push(t);
            }
            else
            {
                string arg2 = st.top();
                st.pop();

                string arg1 = st.top();
                st.pop();

                string t = newTemp();

                quadList.push_back({token, arg1, arg2, t});

                st.push(t);
            }
        }
        else
        {
            st.push(token);
        }
    }
}

int main()
{
    // Example: ((a + b) * c) > (-d)
    vector<string> infix =
    {
        "(", "(", "a", "+", "b", ")", "*", "c", ")",
        ">",
        "(", "-", "d", ")"
    };

    vector<string> postfix = infixToPostfix(infix);

    cout << "Postfix: ";

    for (const auto& t : postfix)
        cout << t << " ";

    cout << "\n\n";

    generateTACFromPostfix(postfix);

    cout << "Quadruples:\n";

    cout << "Operator\tArg1\tArg2\tResult\n";

    for (const auto& q : quadList)
    {
        cout << q.op << "\t\t"
             << q.arg1 << "\t"
             << q.arg2 << "\t"
             << q.result << "\n";
    }

    cout << "\nLab No.: 2\n";
    cout << "Name: Suvekshya Jha\n";
    cout << "Roll No.: 80117729\n";

    return 0;
}

