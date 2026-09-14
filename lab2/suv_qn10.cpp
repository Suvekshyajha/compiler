#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;

struct I {
    string op, a, b;
    bool live = false;
};

vector<I> p = {
    {"=", "i", "1"}, {"LABEL", "L1", ""},
    {"=", "t1", "i*4"}, {"if", "t1>100", "L2"},
    {"=", "i", "i+1"}, {"goto", "L1", ""},
    {"LABEL", "L2", ""}, {"return", "i", ""}
};

vector<int> leaders() {
    set<int> s{0};
    for (int i = 0; i < p.size(); i++) {
        if (p[i].op == "LABEL") s.insert(i);
        if (p[i].op == "goto" || p[i].op == "if")
            if (i + 1 < p.size()) s.insert(i + 1);
    }
    return vector<int>(s.begin(), s.end());
}

int main() {
    auto L = leaders();

    cout << "Basic Blocks:\n";
    map<int,int> block;
    for (int i = 0; i < L.size(); i++) {
        int e = i + 1 < L.size() ? L[i + 1] : p.size();
        cout << "B" << i << ": ";
        for (int j = L[i]; j < e; j++) {
            block[j] = i;
            cout << j << " ";
        }
        cout << "\n";
    }

    cout << "\nCFG:\n";
    for (int i = 0; i < L.size(); i++) {
        int e = i + 1 < L.size() ? L[i + 1] : p.size();
        I x = p[e - 1];

        if (x.op == "goto" || x.op == "if") {
            for (int j = 0; j < p.size(); j++)
                if (p[j].op == "LABEL" && p[j].a == x.b)
                    cout << "B" << i << " -> B" << block[j] << "\n";
            if (x.op == "if" && i + 1 < L.size())
                cout << "B" << i << " -> B" << i + 1 << "\n";
        }
        else if (i + 1 < L.size())
            cout << "B" << i << " -> B" << i + 1 << "\n";
    }

    // Backward liveness
    set<string> live;
    for (int i = p.size() - 1; i >= 0; i--) {
        if (p[i].op == "return") {
            p[i].live = true;
            live.insert(p[i].a);
        }
        else if (p[i].op == "LABEL" || p[i].op == "goto" ||
                 p[i].op == "if")
            p[i].live = true;
        else if (live.count(p[i].a)) {
            p[i].live = true;
            live.erase(p[i].a);
            live.insert(p[i].b);
        }
    }

    cout << "\nAfter Dead Code Elimination:\n";
    for (auto x : p)
        if (x.live)
            cout << x.op << " " << x.a << " " << x.b << "\n";

    cout << "\nLab No.: 2\nName: Suvekshya Jha\nRoll No.: 80117729\n";
}