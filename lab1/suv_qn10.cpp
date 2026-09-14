#include <iostream>
#include <stack>
#include <map>
#include <string>
using namespace std;

int main() {

    // LL(1) Parsing Table
    map<pair<char, char>, string> table;

    // Grammar:
    // S -> aA
    // A -> bA | #

    table[{'S', 'a'}] = "aA";

    table[{'A', 'b'}] = "bA";
    table[{'A', '$'}] = "#";

    string input;

    cout << "Grammar:\n";
    cout << "S -> aA\n";
    cout << "A -> bA | #\n\n";

    cout << "Enter input string: ";
    cin >> input;

    input += '$';

    stack<char> st;
    st.push('$');
    st.push('S');

    int i = 0;

    cout << "\nStack\tInput\tAction\n";

    while (!st.empty()) {

        char top = st.top();
        char current = input[i];

        // Accept
        if (top == '$' && current == '$') {
            cout << "$\t$\tAccept\n";
            break;
        }

        // Terminal
        if (top == current) {

            cout << top << "\t"
                 << input.substr(i)
                 << "\tMatch " << current << "\n";

            st.pop();
            i++;
        }

        // Non-terminal
        else if (top == 'S' || top == 'A') {

            auto it = table.find({top, current});

            if (it == table.end()) {

                cout << "\t"
                     << input.substr(i)
                     << "\tError\n";

                cout << "\nString Rejected.\n";
                return 0;
            }

            string production = it->second;

            cout << top << "\t"
                 << input.substr(i)
                 << "\t"
                 << top << " -> " << production << "\n";

            st.pop();

            // Epsilon production
            if (production != "#") {

                // Push production in reverse order
                for (int j = production.length() - 1; j >= 0; j--) {
                    st.push(production[j]);
                }
            }
        }

        else {

            cout << "\nString Rejected.\n";
            return 0;
        }
    }

    cout << "Lab No. 1 Name: Suvekshya Jha | Roll No.: 80117729\n";

    return 0;
}
