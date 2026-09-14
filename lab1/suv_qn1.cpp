#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;
    int state = 0; // 0=q0, 1=q1, 2=qf, 3=qd

    cout << "Enter a binary string (0s and 1s only): ";
    cin >> str;

    for (int i = 0; i < str.length(); i++) {
        char c = str[i];

        if (state == 0) {          // q0
            if (c == '0') state = 1;
            else state = 3;
        }
        else if (state == 1) {     // q1
            if (c == '1') state = 2;
            else state = 3;
        }
        else if (state == 2) {     // qf
            state = 2;
        }
        else if (state == 3) {     // qd
            state = 3;
        }
    }

    if (state == 2)
        cout << "String \"" << str << "\" is ACCEPTED (starts with 01)" << endl;
    else
        cout << "String \"" << str << "\" is REJECTED" << endl;

    cout << "\n----------------------------------\n";
    cout << "Lab No.  : 1\n";
    cout << "Name     : Suvekhsya Jha\n";
    cout << "Roll No. : 80117729\n";
    cout << "----------------------------------\n";

    return 0;
}
