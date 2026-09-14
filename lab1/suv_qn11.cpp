// Top-Down Non-Recursive Descent Parser
// Original Grammar:
// E -> E+E
// E -> E*E
// E -> (E)
// E -> i
// i = identifier
//
// LL(1) equivalent grammar used internally:
// E -> TX
// X -> +TX | *TX | #
// T -> (E) | i
// # = epsilon

#include <bits/stdc++.h>
using namespace std;

string getStack(vector<char> st)
{
    string s;

    for (char c : st)
        s += c;

    return s;
}

int main()
{
    string input;

    cout << "Enter expression: ";
    cin >> input;

    // Add end marker
    input += "$";

    vector<char> st;

    // Push start symbol
    st.push_back('$');
    st.push_back('E');

    int pos = 0;
    bool accepted = false;

    cout << "\n";
    cout << left
         << setw(20) << "Stack"
         << setw(20) << "Input"
         << "Action" << endl;

    cout << string(60, '-') << endl;

    while (!st.empty())
    {
        char top = st.back();
        char current = input[pos];

        // ACCEPT
        if (top == '$' && current == '$')
        {
            cout << left
                 << setw(20) << getStack(st)
                 << setw(20) << input.substr(pos)
                 << "Accept" << endl;

            accepted = true;
            break;
        }

        // NON-TERMINAL E
        if (top == 'E')
        {
            if (current == 'i' || current == '(')
            {
                st.pop_back();

                // E -> TX
                st.push_back('X');
                st.push_back('T');

                cout << left
                     << setw(20) << getStack(st)
                     << setw(20) << input.substr(pos)
                     << "E -> TX" << endl;
            }
            else
            {
                cout << left
                     << setw(20) << getStack(st)
                     << setw(20) << input.substr(pos)
                     << "Error" << endl;
                break;
            }
        }

        // NON-TERMINAL X
        else if (top == 'X')
        {
            if (current == '+')
            {
                st.pop_back();

                // X -> +TX
                st.push_back('X');
                st.push_back('T');
                st.push_back('+');

                cout << left
                     << setw(20) << getStack(st)
                     << setw(20) << input.substr(pos)
                     << "X -> +TX" << endl;
            }
            else if (current == '*')
            {
                st.pop_back();

                // X -> *TX
                st.push_back('X');
                st.push_back('T');
                st.push_back('*');

                cout << left
                     << setw(20) << getStack(st)
                     << setw(20) << input.substr(pos)
                     << "X -> *TX" << endl;
            }
            else if (current == ')' || current == '$')
            {
                st.pop_back();

                // X -> #
                cout << left
                     << setw(20) << getStack(st)
                     << setw(20) << input.substr(pos)
                     << "X -> #" << endl;
            }
            else
            {
                cout << left
                     << setw(20) << getStack(st)
                     << setw(20) << input.substr(pos)
                     << "Error" << endl;
                break;
            }
        }

        // NON-TERMINAL T
        else if (top == 'T')
        {
            if (current == 'i')
            {
                st.pop_back();
                st.push_back('i');

                cout << left
                     << setw(20) << getStack(st)
                     << setw(20) << input.substr(pos)
                     << "T -> i" << endl;
            }
            else if (current == '(')
            {
                st.pop_back();

                // T -> (E)
                st.push_back(')');
                st.push_back('E');
                st.push_back('(');

                cout << left
                     << setw(20) << getStack(st)
                     << setw(20) << input.substr(pos)
                     << "T -> (E)" << endl;
            }
            else
            {
                cout << left
                     << setw(20) << getStack(st)
                     << setw(20) << input.substr(pos)
                     << "Error" << endl;
                break;
            }
        }

        // TERMINAL MATCH
        else
        {
            if (top == current)
            {
                st.pop_back();

                cout << left
                     << setw(20) << getStack(st)
                     << setw(20) << input.substr(pos + 1)
                     << "Match '" << current << "'" << endl;

                pos++;
            }
            else
            {
                cout << left
                     << setw(20) << getStack(st)
                     << setw(20) << input.substr(pos)
                     << "Error" << endl;
                break;
            }
        }
    }

    cout << "\nResult: ";

    if (accepted)
        cout << "Accepted";
    else
        cout << "Rejected";

    cout << "\n\nLab No. 1"
         << "\tName: Suvekshya Jha"
         << "\tRoll No: 80117729" << endl;

    return 0;
}