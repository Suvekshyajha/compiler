#include <iostream>
using namespace std;

// A -> A alpha | beta  =>  A -> beta A' , A' -> alpha A' | #
void directLR(string A, string alpha, string beta) {
    cout << A << " -> " << beta << A << "'\n";
    cout << A << "' -> " << alpha << A << "' | #\n"; // # = epsilon
}

// Indirect: S -> Aa | b , A -> Ac | Sd | #
void indirectLR() {
    cout << "Original: S -> Aa | b , A -> Ac | Sd | #\n";
    cout << "Substitute S into A: A -> Ac | Aad | bd | #\n";
    cout << "Remove direct recursion on A:\n";
    cout << "A -> bd A' | A'\nA' -> c A' | ad A' | #\n";
}

// A -> alpha beta1 | alpha beta2  =>  A -> alpha A' , A' -> beta1 | beta2
void leftFactor(string A, string alpha, string beta1, string beta2) {
    cout << A << " -> " << alpha << A << "'\n";
    cout << A << "' -> " << (beta1.empty() ? "#" : beta1) << " | " << beta2 << endl;
}

int main() {
    cout << "=== 1. Direct Left Recursion ===\n";
    cout << "Original: E -> E+T | T\n";
    directLR("E", "+T", "T");

    cout << "\n=== 2. Indirect Left Recursion ===\n";
    indirectLR();

    cout << "\n=== 3. Left Factoring ===\n";
    cout << "Original: A -> iEtS | iEtSeS\n";
    leftFactor("A", "iEtS", "", "eS");

    cout << "\n--------------------------------------------------\n";
    cout << "Lab No. 1  \n Name: Suvekshya Jha \n Roll No.: 80117729\n";
    return 0;
}
