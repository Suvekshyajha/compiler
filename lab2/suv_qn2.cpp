#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct SymbolInfo {
    string name;
    string type;
    int size;
    int scopeLevel;
};

class ScopedSymbolTable {

private:
    vector<unordered_map<string, SymbolInfo>> scopeStack;

public:

    // Constructor creates global scope
    ScopedSymbolTable() {
        enter_scope();
    }

    // Enter a new scope
    void enter_scope() {
        scopeStack.push_back({});
    }

    // Leave the current scope
    void leave_scope() {
        if (!scopeStack.empty()) {
            scopeStack.pop_back();
        }
    }

    // Insert symbol into current scope
    void insert(string name, SymbolInfo info) {

        auto& top = scopeStack.back();

        // Check redeclaration in current scope only
        if (top.find(name) != top.end()) {
            cout << "Redeclaration Error: "
                 << name << " in current scope\n";
            return;
        }

        top[name] = info;
    }

    // Lookup from current scope to global scope
    SymbolInfo* lookup(const string& name) {

        for (int i = (int)scopeStack.size() - 1; i >= 0; --i) {

            auto it = scopeStack[i].find(name);

            if (it != scopeStack[i].end()) {
                return &(it->second);
            }
        }

        cout << "Undeclared Error: " << name << "\n";

        return nullptr;
    }
};

int main() {

    ScopedSymbolTable table;

    // AST simulation: Global scope

    cout << "Global Scope\n";

    table.insert("x", {"x", "int", 4, 0});


    // Block entry {
    cout << "\nEntering Inner Scope\n";

    table.enter_scope();

    table.insert("y", {"y", "float", 4, 1});

    // Shadowing x is allowed
    table.insert("x", {"x", "int", 4, 1});


    // Lookup inside inner scope

    SymbolInfo* symbol;

    symbol = table.lookup("y");

    if (symbol != nullptr) {
        cout << "Found: " << symbol->name
             << ", Type: " << symbol->type
             << ", Scope Level: " << symbol->scopeLevel << endl;
    }

    symbol = table.lookup("x");

    if (symbol != nullptr) {
        cout << "Found: " << symbol->name
             << ", Type: " << symbol->type
             << ", Scope Level: " << symbol->scopeLevel << endl;
    }


    // Block exit }
    cout << "\nLeaving Inner Scope\n";

    table.leave_scope();


    // x should be found in global scope

    symbol = table.lookup("x");

    if (symbol != nullptr) {
        cout << "Found: " << symbol->name
             << ", Type: " << symbol->type
             << ", Scope Level: " << symbol->scopeLevel << endl;
    }


    // y should no longer exist

    table.lookup("y");


    cout << "\nLab No.: 2\n";
    cout << "Name: Suvekshya Jha\n";
    cout << "Roll No.: 80117729\n";

    return 0;
}