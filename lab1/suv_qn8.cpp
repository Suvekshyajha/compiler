#include <bits/stdc++.h>
using namespace std;

map<char, string> g;
map<char, set<char>> F, W;
set<char> nt;
char start;

vector<string> split(string s) {
    vector<string> r;
    stringstream ss(s);
    string t;

    while (getline(ss, t, '|'))
        r.push_back(t);

    return r;
}

void doFirst() {
    bool changed = true;

    while (changed) {
        changed = false;

        for (auto &p : g) {
            char A = p.first;

            for (string rhs : split(p.second)) {

                bool nullable = true;

                for (char X : rhs) {

                    // Terminal
                    if (!nt.count(X)) {
                        if (F[A].insert(X).second)
                            changed = true;

                        nullable = false;
                        break;
                    }

                    // Non-terminal
                    for (char x : F[X]) {
                        if (x != '#') {
                            if (F[A].insert(x).second)
                                changed = true;
                        }
                    }

                    // X cannot produce epsilon
                    if (!F[X].count('#')) {
                        nullable = false;
                        break;
                    }
                }

                // All symbols can produce epsilon
                if (nullable) {
                    if (F[A].insert('#').second)
                        changed = true;
                }
            }
        }
    }
}

void doFollow() {

    W[start].insert('$');

    bool changed = true;

    while (changed) {
        changed = false;

        for (auto &p : g) {

            char A = p.first;

            for (string rhs : split(p.second)) {

                for (int i = 0; i < (int)rhs.size(); i++) {

                    char B = rhs[i];

                    if (!nt.count(B))
                        continue;

                    bool nullable = true;

                    // Look at symbols after B
                    for (int j = i + 1; j < (int)rhs.size(); j++) {

                        char C = rhs[j];

                        // Terminal
                        if (!nt.count(C)) {
                            if (W[B].insert(C).second)
                                changed = true;

                            nullable = false;
                            break;
                        }

                        // FIRST(C) goes to FOLLOW(B)
                        for (char x : F[C]) {
                            if (x != '#') {
                                if (W[B].insert(x).second)
                                    changed = true;
                            }
                        }

                        // C is not nullable
                        if (!F[C].count('#')) {
                            nullable = false;
                            break;
                        }
                    }

                    // If everything after B is nullable,
                    // FOLLOW(A) goes to FOLLOW(B)
                    if (nullable) {

                        for (char x : W[A]) {

                            if (W[B].insert(x).second)
                                changed = true;
                        }
                    }
                }
            }
        }
    }
}

int main() {

    int n;

    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions:\n";

    for (int i = 0; i < n; i++) {

        string s;
        cin >> s;

        g[s[0]] = s.substr(3);

        nt.insert(s[0]);

        if (i == 0)
            start = s[0];
    }

    doFirst();
    doFollow();

    cout << "\nFIRST:\n";

    for (auto &p : F) {
        cout << "FIRST(" << p.first << ") = { ";

        for (char c : p.second)
            cout << c << " ";

        cout << "}\n";
    }

    cout << "\nFOLLOW:\n";

    for (auto &p : W) {
        cout << "FOLLOW(" << p.first << ") = { ";

        for (char c : p.second)
            cout << c << " ";

        cout << "}\n";
    }

    cout << "Lab No. 1 Name: Suvekshya Jha | Roll No.: 80117729\n";

    return 0;
}