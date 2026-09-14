#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int a, b;

    cout << "Enter state numbers to merge (e.g. 3 6): ";
    cin >> a >> b;

    cout << "Merged State: " << a << b << "\n\n";

    cout << "LALR(1) Parsing Table:\n";

    cout << left
         << setw(8) << "State"
         << setw(8) << "c"
         << setw(8) << "d"
         << setw(8) << "$"
         << setw(8) << "S"
         << setw(8) << "C" << endl;

    cout << setw(8) << "0"
         << setw(8) << ""
         << setw(8) << "s36"
         << setw(8) << "s47"
         << setw(8) << "1"
         << setw(8) << "2" << endl;

    cout << setw(8) << "1"
         << setw(8) << ""
         << setw(8) << ""
         << setw(8) << ""
         << setw(8) << "acc" << endl;

    cout << setw(8) << a << b
         << setw(8) << ""
         << setw(8) << "s36"
         << setw(8) << "s47"
         << setw(8) << ""
         << setw(8) << "89" << endl;

    
      cout << "Lab No. 1 Name:suvekshya jha | Roll No.: 80117729" << endl;
    return 0;
}