#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;

map<char, vector<string>> G;
map<char, set<char>> F, L;
set<char> NT;

set<char> first(char x) {
    if (!NT.count(x))
        return {x};

    if (!F[x].empty())
        return F[x];

    for (string p : G[x]) {
        bool eps = true;

        for (char c : p) {
            set<char> t = first(c);

            F[x].insert(t.begin(), t.end());

            if (!t.count('#')) {
                eps = false;
                break;
            }
        }

        if (eps)
            F[x].insert('#');
    }

    return F[x];
}

int main() {
    int n;

    cout << "Enter number of productions: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string s, x;
        cin >> s;

        NT.insert(s[0]);

        for (int j = 3; j <= s.size(); j++) {
            if (j == s.size() || s[j] == '|') {
                G[s[0]].push_back(x);
                x = "";
            }
            else {
                x += s[j];
            }
        }
    }

    // FIRST
    for (char x : NT)
        first(x);

    // FOLLOW
    L[*NT.begin()].insert('$');

    bool change = true;

    while (change) {
        change = false;

        for (auto [A, ps] : G) {
            for (string p : ps) {

                for (int i = 0; i < p.size(); i++) {

                    if (NT.count(p[i])) {
                        char B = p[i];
                        set<char> t;
                        bool eps = true;

                        for (int j = i + 1; j < p.size(); j++) {
                            set<char> q = first(p[j]);

                            t.insert(q.begin(), q.end());

                            if (!q.count('#')) {
                                eps = false;
                                break;
                            }
                        }

                        if (eps)
                            t.insert(L[A].begin(), L[A].end());

                        t.erase('#');

                        int z = L[B].size();

                        L[B].insert(t.begin(), t.end());

                        if (z != L[B].size())
                            change = true;
                    }
                }
            }
        }
    }

    // Display FIRST
    cout << "\nFIRST:\n";

    for (char x : NT) {
        cout << "FIRST(" << x << ") = { ";

        for (char c : F[x])
            cout << c << " ";

        cout << "}\n";
    }

    // Display FOLLOW
    cout << "\nFOLLOW:\n";

    for (char x : NT) {
        cout << "FOLLOW(" << x << ") = { ";

        for (char c : L[x])
            cout << c << " ";

        cout << "}\n";
    }

    // LL(1) Parsing Table
    cout << "\nLL(1) PARSING TABLE\n\n";

    cout << "NT\t";

    set<char> T;

    for (auto [A, ps] : G) {
        for (string p : ps) {
            for (char c : p) {
                if (!NT.count(c) && c != '#')
                    T.insert(c);
            }
        }
    }

    T.insert('$');

    for (char t : T)
        cout << t << "\t";

    cout << "\n";

    for (char A : NT) {
        cout << A << "\t";

        for (char t : T) {
            string cell = "";

            for (string p : G[A]) {
                set<char> x;
                bool eps = true;

                for (char c : p) {
                    set<char> q = first(c);

                    x.insert(q.begin(), q.end());

                    if (!q.count('#')) {
                        eps = false;
                        break;
                    }
                }

                if (eps)
                    x.insert('#');

                if (x.count(t) || (x.count('#') && L[A].count(t)))
                    cell = string(1, A) + "->" + p;
            }

            cout << (cell.empty() ? "-" : cell) << "\t";
        }

        cout << "\n";
    }

     cout << "Lab No. 1 \n  Name:suvekshya jha | Roll No.: 80117729" << endl;

    return 0;
}