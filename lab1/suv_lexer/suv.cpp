// lexer.cpp - Lexical Analyzer for a C subset (pure C++, no Flex)
// Compile: g++ lexer.cpp -o lexer
// Run    : ./lexer test.cpp
#include <bits/stdc++.h>
using namespace std;

set<string> initKeywords() {
    set<string> k;
    string words[] = {"int","float","char","double","if","else","while","for","return"};
    for (int i = 0; i < 9; i++) k.insert(words[i]);
    return k;
}
set<string> kw = initKeywords();
int line_no = 1;

void lex(const string& s) {
    int n = s.size(), i = 0;
    while (i < n) {
        char c = s[i];

        if (c == '\n') { line_no++; i++; }
        else if (isspace((unsigned char)c)) { i++; }

        else if (c=='/' && i+1<n && s[i+1]=='/') {                // line comment
            while (i<n && s[i]!='\n') i++;
        }
        else if (c=='/' && i+1<n && s[i+1]=='*') {                // block comment
            i += 2;
            while (i+1<n && !(s[i]=='*' && s[i+1]=='/')) { if (s[i]=='\n') line_no++; i++; }
            i += 2;
        }
        else if (isalpha((unsigned char)c) || c=='_') {            // ID / keyword
            int j=i;
            while (j<n && (isalnum((unsigned char)s[j]) || s[j]=='_')) j++;
            string lex = s.substr(i, j-i);
            cout << "<" << (kw.count(lex)?"KEYWORD":"IDENTIFIER") << ", " << lex << ", " << line_no << ">\n";
            i=j;
        }
        else if (isdigit((unsigned char)c)) {                      // INTEGER / FLOAT
            int j=i; bool isFloat=false;
            while (j<n && isdigit((unsigned char)s[j])) j++;
            if (j<n && s[j]=='.') { isFloat=true; j++; while (j<n && isdigit((unsigned char)s[j])) j++; }
            string lex = s.substr(i, j-i);
            cout << "<" << (isFloat?"FLOAT":"INTEGER") << ", " << lex << ", " << line_no << ">\n";
            i=j;
        }
        else if ((c=='='||c=='!'||c=='<'||c=='>') && i+1<n && s[i+1]=='=') { // == != <= >=
            cout << "<RELATIONAL_OPERATOR, " << s.substr(i,2) << ", " << line_no << ">\n"; i+=2;
        }
        else if (c=='<'||c=='>') {                                 // < >
            cout << "<RELATIONAL_OPERATOR, " << c << ", " << line_no << ">\n"; i++;
        }
        else if (c=='+'||c=='-'||c=='*'||c=='/'||c=='%') {         // arithmetic
            cout << "<ARITHMETIC_OPERATOR, " << c << ", " << line_no << ">\n"; i++;
        }
        else if (c=='=') {                                          // assignment
            cout << "<ASSIGNMENT_OPERATOR, " << c << ", " << line_no << ">\n"; i++;
        }
        else if (string(";,(){}[]").find(c)!=string::npos) {       // delimiter
            cout << "<DELIMITER, " << c << ", " << line_no << ">\n"; i++;
        }
        else {
            cout << "<UNKNOWN, " << c << ", " << line_no << ">\n"; i++;
        }
    }
}

int main(int argc, char** argv) {
    ifstream fin(argv[1]);
    string src((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

    cout << "Lexical Analysis Output:\n\n";
    lex(src);

    cout << "-------------------------------------------\n";
    cout << "       LEXICAL ANALYZER USING C++\n";
    cout << "-------------------------------------------\n";
    cout << "Lab No.  : 1\n";
    cout << "Name     : Suvekshya Jha\n";
    cout << "Roll No  : 80117729\n";
    cout << "-------------------------------------------\n";
    return 0;
}
