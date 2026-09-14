#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;

    cout << "Enter a line: ";
    getline(cin, str);

    int n = str.length();
    bool isComment = false;

    // Check for single line comment: starts with //
    if (n >= 2 && str[0] == '/' && str[1] == '/') {
        isComment = true;
    }
    // Check for multi line comment: starts with /* and ends with */
    else if (n >= 4 && str[0] == '/' && str[1] == '*' &&
             str[n-2] == '*' && str[n-1] == '/') {
        isComment = true;
    }

    if (isComment)
        cout << "Comment" << endl;
    else
        cout << "Not a Comment" << endl;

    cout << "\n----------------------------------\n";
    cout << "Lab No.  : 1\n";
    cout << "Name     : Suvekhsya Jha\n";
    cout << "Roll No./Section : 80117729\n";
    cout << "----------------------------------\n";

    return 0;
}
