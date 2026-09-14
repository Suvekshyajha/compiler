#include <iostream>
#include <string>
using namespace std;

int main() {
    string line;
    int lineNum = 0;

    cout << "Enter input (type 'end' on a new line to stop):\n";

    while (getline(cin, line) && line != "end") {
        lineNum++;
        int n = line.length();
        int i = 0;

        while (i < n) {
            char c = line[i];
            char next = (i + 1 < n) ? line[i + 1] : '\0';

            // Arithmetic
            if (c == '+' && next == '=') { cout << "<+=, Assignment, " << lineNum << ">\n"; i += 2; }
            else if (c == '-' && next == '=') { cout << "<-=, Assignment, " << lineNum << ">\n"; i += 2; }
            else if (c == '*' && next == '=') { cout << "<*=, Assignment, " << lineNum << ">\n"; i += 2; }
            else if (c == '/' && next == '=') { cout << "</=, Assignment, " << lineNum << ">\n"; i += 2; }
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
                cout << "<" << c << ", Arithmetic, " << lineNum << ">\n"; i += 1;
            }
            // Relational
            else if (c == '<' && next == '=') { cout << "<<=, Relational, " << lineNum << ">\n"; i += 2; }
            else if (c == '>' && next == '=') { cout << "<>=, Relational, " << lineNum << ">\n"; i += 2; }
            else if (c == '=' && next == '=') { cout << "<==, Relational, " << lineNum << ">\n"; i += 2; }
            else if (c == '!' && next == '=') { cout << "<!=, Relational, " << lineNum << ">\n"; i += 2; }
            else if (c == '<' || c == '>') {
                cout << "<" << c << ", Relational, " << lineNum << ">\n"; i += 1;
            }
            // Logical
            else if (c == '&' && next == '&') { cout << "<&&, Logical, " << lineNum << ">\n"; i += 2; }
            else if (c == '|' && next == '|') { cout << "<||, Logical, " << lineNum << ">\n"; i += 2; }
            else if (c == '!') {
                cout << "<!, Logical, " << lineNum << ">\n"; i += 1;
            }
            // Assignment
            else if (c == '=') {
                cout << "<=, Assignment, " << lineNum << ">\n"; i += 1;
            }
            // Invalid incomplete operators
            else if (c == '&' || c == '|') {
                cout << "Invalid Operator: " << c << "\n"; i += 1;
            }
            else {
                i += 1; // skip non-operator characters (letters, digits, spaces)
            }
        }
    }

    cout << "\n----------------------------------\n";
    cout << "Lab No.  : 1\n";
    cout << "Name     : Suvekhsya Jha\n";
    cout << "Roll No./Section : 80117729\n";
    cout << "----------------------------------\n";

    return 0;
}
