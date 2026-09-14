#include <bits/stdc++.h>
using namespace std;

struct Item {
    int p, dot;

    bool operator<(const Item& x) const {
        return p != x.p ? p < x.p : dot < x.dot;
    }

    bool operator==(const Item& x) const {
        return p == x.p && dot == x.dot;
    }
};

vector<pair<string, vector<string>>> prod = {
    {"S'", {"S"}},
    {"S", {"E"}},
    {"E", {"E", "+", "T"}},
    {"E", {"T"}},
    {"T", {"T", "*", "F"}},
    {"T", {"F"}},
    {"F", {"(", "E", ")"}},
    {"F", {"id"}}
};

set<string> nonterm = {"S'", "S", "E", "T", "F"};

vector<set<Item>> C;
map<pair<int, string>, int> go;

set<Item> closure(set<Item> I) {
    bool change = true;

    while (change) {
        change = false;
        set<Item> add;

        for (auto x : I) {
            auto r = prod[x.p].second;

            if (x.dot < r.size() && nonterm.count(r[x.dot])) {
                string B = r[x.dot];

                for (int j = 0; j < prod.size(); j++) {
                    if (prod[j].first == B) {
                        Item n = {j, 0};

                        if (!I.count(n))
                            add.insert(n);
                    }
                }
            }
        }

        for (auto x : add) {
            if (I.insert(x).second)
                change = true;
        }
    }

    return I;
}

set<Item> GOTO(set<Item> I, string X) {
    set<Item> J;

    for (auto x : I) {
        auto r = prod[x.p].second;

        if (x.dot < r.size() && r[x.dot] == X)
            J.insert({x.p, x.dot + 1});
    }

    return closure(J);
}

void items() {
    C.push_back(closure({{0, 0}}));

    for (int i = 0; i < C.size(); i++) {
        set<string> symbols;

        for (auto x : C[i]) {
            auto r = prod[x.p].second;

            if (x.dot < r.size())
                symbols.insert(r[x.dot]);
        }

        for (string X : symbols) {
            set<Item> J = GOTO(C[i], X);

            if (J.empty())
                continue;

            int k = -1;

            for (int j = 0; j < C.size(); j++) {
                if (C[j] == J) {
                    k = j;
                    break;
                }
            }

            if (k == -1) {
                C.push_back(J);
                k = C.size() - 1;
            }

            go[{i, X}] = k;
        }
    }
}

int main() {
    items();

    vector<string> terms = {
        "id", "+", "*", "(", ")", "$"
    };

    vector<string> nts = {
        "S", "E", "T", "F"
    };

    map<string, set<string>> follow;

    follow["S"].insert("$");
    follow["E"] = {"+", ")", "$"};
    follow["T"] = {"*", "+", ")", "$"};
    follow["F"] = {"*", "+", ")", "$"};

    cout << "LR(0) CANONICAL COLLECTION\n\n";

    for (int i = 0; i < C.size(); i++) {
        cout << "I" << i << ":\n";

        for (auto x : C[i]) {
            cout << "  " << prod[x.p].first << " -> ";

            for (int j = 0; j <= prod[x.p].second.size(); j++) {
                if (j == x.dot)
                    cout << ". ";

                if (j < prod[x.p].second.size())
                    cout << prod[x.p].second[j] << " ";
            }

            cout << "\n";
        }

        cout << "\n";
    }

    vector<vector<string>> ACTION(
        C.size(),
        vector<string>(terms.size(), "")
    );

    vector<vector<string>> GOTO_TABLE(
        C.size(),
        vector<string>(nts.size(), "")
    );

    for (int i = 0; i < C.size(); i++) {
        for (int j = 0; j < nts.size(); j++) {
            if (go.count({i, nts[j]}))
                GOTO_TABLE[i][j] =
                    to_string(go[{i, nts[j]}]);
        }
    }

    for (int i = 0; i < C.size(); i++) {
        for (auto x : C[i]) {
            auto r = prod[x.p].second;

            if (x.dot < r.size()) {
                string X = r[x.dot];

                if (!nonterm.count(X) && go.count({i, X})) {
                    for (int j = 0; j < terms.size(); j++) {
                        if (terms[j] == X) {
                            ACTION[i][j] =
                                "s" + to_string(go[{i, X}]);
                        }
                    }
                }
            }
            else {
                if (x.p == 0) {
                    ACTION[i][5] = "acc";
                }
                else {
                    string A = prod[x.p].first;

                    for (string a : follow[A]) {
                        for (int j = 0; j < terms.size(); j++) {
                            if (terms[j] == a) {
                                ACTION[i][j] =
                                    "r" + to_string(x.p);
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "\nSLR(1) PARSING TABLE\n\n";

    cout << left << setw(8) << "State";

    for (string x : terms)
        cout << setw(8) << x;

    for (string x : nts)
        cout << setw(8) << x;

    cout << "\n";

    cout << string(
        8 + 8 * (terms.size() + nts.size()),
        '-'
    ) << "\n";

    for (int i = 0; i < C.size(); i++) {
        cout << left << setw(8) << i;

        for (int j = 0; j < terms.size(); j++)
            cout << setw(8) << ACTION[i][j];

        for (int j = 0; j < nts.size(); j++)
            cout << setw(8) << GOTO_TABLE[i][j];

        cout << "\n";
    }
    
    cout << "\n\nLab No. 1"
         << "\tName: Suvekshya Jha"
         << "\tRoll No: 80117729" << endl;

    return 0;
}