#include <iostream>
#include <cstring>

using namespace std;

#define MAX_SYMBOLS 100

struct Symbol {
    char name[32];
    char type[10];
    int address;
    int size;
};

Symbol symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

int findSymbol(const char* name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0)
            return i;
    }
    return -1;
}

void insertSymbol() {
    char name[32];

    cout << "Enter name: ";
    cin >> name;

    if (findSymbol(name) != -1) {
        cout << "Duplicate symbol\n";
        return;
    }

    if (symbolCount >= MAX_SYMBOLS) {
        cout << "Symbol table is full\n";
        return;
    }

    Symbol s;

    strcpy(s.name, name);

    cout << "Enter type: ";
    cin >> s.type;

    cout << "Enter address: ";
    cin >> s.address;

    cout << "Enter size: ";
    cin >> s.size;

    symbolTable[symbolCount++] = s;

    cout << "Symbol inserted successfully\n";
}

void displaySymbols() {
    if (symbolCount == 0) {
        cout << "Symbol table is empty\n";
        return;
    }

    cout << "\nIndex\tName\tType\tAddress\tSize\n";

    for (int i = 0; i < symbolCount; i++) {
        cout << i << "\t"
             << symbolTable[i].name << "\t"
             << symbolTable[i].type << "\t"
             << symbolTable[i].address << "\t"
             << symbolTable[i].size << "\n";
    }
}

void deleteSymbol() {
    char name[32];

    cout << "Enter name to delete: ";
    cin >> name;

    int idx = findSymbol(name);

    if (idx == -1) {
        cout << "Label not found\n";
        return;
    }

    for (int i = idx; i < symbolCount - 1; i++) {
        symbolTable[i] = symbolTable[i + 1];
    }

    symbolCount--;

    cout << "Symbol deleted successfully\n";
}

void searchSymbol() {
    char name[32];

    cout << "Enter name to search: ";
    cin >> name;

    int idx = findSymbol(name);

    if (idx == -1) {
        cout << "Symbol not found\n";
        return;
    }

    cout << "\nIndex: " << idx << endl;
    cout << "Name: " << symbolTable[idx].name << endl;
    cout << "Type: " << symbolTable[idx].type << endl;
    cout << "Address: " << symbolTable[idx].address << endl;
    cout << "Size: " << symbolTable[idx].size << endl;
}

void modifySymbol() {
    char name[32];

    cout << "Enter name to modify: ";
    cin >> name;

    int idx = findSymbol(name);

    if (idx == -1) {
        cout << "Symbol not found\n";
        return;
    }

    int choice;

    cout << "\n1. Modify Type\n";
    cout << "2. Modify Address\n";
    cout << "3. Modify Both\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Enter new type: ";
            cin >> symbolTable[idx].type;
            break;

        case 2:
            cout << "Enter new address: ";
            cin >> symbolTable[idx].address;
            break;

        case 3:
            cout << "Enter new type: ";
            cin >> symbolTable[idx].type;

            cout << "Enter new address: ";
            cin >> symbolTable[idx].address;
            break;

        default:
            cout << "Invalid choice\n";
            return;
    }

    cout << "Symbol modified successfully\n";
}

int main() {
    int choice;

    do {
        cout << "\n----- SYMBOL TABLE MENU -----\n";
        cout << "1. Insert\n";
        cout << "2. Display\n";
        cout << "3. Delete\n";
        cout << "4. Search\n";
        cout << "5. Modify\n";
        cout << "6. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                insertSymbol();
                break;

            case 2:
                displaySymbols();
                break;

            case 3:
                deleteSymbol();
                break;

            case 4:
                searchSymbol();
                break;

            case 5:
                modifySymbol();
                break;

            case 6:
                cout << "\nLab No.: 2\n";
                cout << "Name: Suvekshya Jha\n";
                cout << "Roll No.: 80117729\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while (choice != 6);

    return 0;
}