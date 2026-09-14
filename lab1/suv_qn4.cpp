#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string str;
    string keywords[] = {"auto","break","case","char","const","continue","default",
        "do","double","else","enum","extern","float","for","goto","if","int","long",
        "register","return","short","signed","sizeof","static","struct","switch",
        "typedef","union","unsigned","void","volatile","while"};
    int numKeywords = 32;

    cout << "Enter a string: ";
    cin >> str;

    int n = str.length();
    bool isKeyword = false;
    bool valid = true;
    string reason = "";

    // Check if it matches a keyword
    for (int i = 0; i < numKeywords; i++) {
        if (str == keywords[i]) {
            isKeyword = true;
            break;
        }
    }

    if (!isKeyword) {
        // Rule 1: must start with letter or underscore
        if (!(isalpha(str[0]) || str[0] == '_')) {
            valid = false;
            reason = "Identifier cannot start with '" + string(1, str[0]) + "' (must start with a letter or underscore)";
        }
        else {
            // Rule 2: remaining characters must be alphanumeric or underscore
            for (int i = 1; i < n; i++) {
                if (!(isalnum(str[i]) || str[i] == '_')) {
                    valid = false;
                    reason = "Invalid character '" + string(1, str[i]) + "' found at position " + to_string(i + 1);
                    break;
                }
            }
        }
    }

    if (isKeyword)
        cout << "\"" << str << "\" is a Reserved Keyword" << endl;
    else if (valid)
        cout << "\"" << str << "\" is a Valid Identifier" << endl;
    else
        cout << "\"" << str << "\" is an Invalid Identifier - " << reason << endl;

    cout << "\n----------------------------------\n";
    cout << "Lab No.  : 1\n";
    cout << "Name     : Suvekhsya Jha\n";
    cout << "Roll No./Section : 80117729\n";
    cout << "----------------------------------\n";

    return 0;
}
