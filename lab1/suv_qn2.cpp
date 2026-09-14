#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;
    int n;

    cout << "Enter a string: ";
    cin >> str;
    n = str.length();

    // All prefixes (proper + improper: empty string to full string)
    cout << "\nAll Prefixes:\n";
    for (int i = 0; i <= n; i++) {
        cout << "\"" << str.substr(0, i) << "\"" << endl;
    }

    // All suffixes (proper + improper: empty string to full string)
    cout << "\nAll Suffixes:\n";
    for (int i = 0; i <= n; i++) {
        cout << "\"" << str.substr(i, n - i) << "\"" << endl;
    }

    // All substrings
    cout << "\nAll Substrings:\n";
    for (int i = 0; i < n; i++) {
        for (int len = 1; len <= n - i; len++) {
            cout << "\"" << str.substr(i, len) << "\"" << endl;
        }
    }

    cout << "\n----------------------------------\n";
    cout << "Lab No.  : 1\n";
    cout << "Name     : Suvekhsya Jha\n";
    cout << "Roll No./Section : 80117729\n";
    cout << "----------------------------------\n";

    return 0;
}
