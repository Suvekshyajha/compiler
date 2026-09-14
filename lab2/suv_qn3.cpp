#include <iostream>

using namespace std;

enum DataType {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_ARRAY,
    TYPE_ERROR
};

string typeName(DataType t) {

    switch (t) {
        case TYPE_INT:
            return "INT";

        case TYPE_FLOAT:
            return "FLOAT";

        case TYPE_BOOL:
            return "BOOL";

        case TYPE_ARRAY:
            return "ARRAY";

        default:
            return "ERROR";
    }
}

DataType evaluate_binary_type(DataType left, DataType right, int lineNo) {

    if (left == TYPE_ERROR || right == TYPE_ERROR)
        return TYPE_ERROR;

    // INT + INT -> INT
    if (left == TYPE_INT && right == TYPE_INT)
        return TYPE_INT;

    // INT + FLOAT or FLOAT + INT -> FLOAT
    if ((left == TYPE_INT && right == TYPE_FLOAT) ||
        (left == TYPE_FLOAT && right == TYPE_INT))
        return TYPE_FLOAT;

    // FLOAT + FLOAT -> FLOAT
    if (left == TYPE_FLOAT && right == TYPE_FLOAT)
        return TYPE_FLOAT;

    cout << "Line " << lineNo
         << ": Type Error - Incompatible operands.\n";

    return TYPE_ERROR;
}

DataType checkArrayIndex(DataType indexType, int lineNo) {

    if (indexType != TYPE_INT) {

        cout << "Line " << lineNo
             << ": Type Error - Array index must be INT.\n";

        return TYPE_ERROR;
    }

    return TYPE_INT;
}

int main() {

    cout << "INT + INT -> "
         << typeName(evaluate_binary_type(TYPE_INT, TYPE_INT, 1))
         << "\n";

    cout << "INT + FLOAT -> "
         << typeName(evaluate_binary_type(TYPE_INT, TYPE_FLOAT, 2))
         << "\n";

    cout << "FLOAT + FLOAT -> "
         << typeName(evaluate_binary_type(TYPE_FLOAT, TYPE_FLOAT, 3))
         << "\n";

    cout << "INT + BOOL -> "
         << typeName(evaluate_binary_type(TYPE_INT, TYPE_BOOL, 4))
         << "\n";

    checkArrayIndex(TYPE_INT, 5);

    checkArrayIndex(TYPE_FLOAT, 6);

    cout << "\nLab No.: 2\n";
    cout << "Name: Suvekshya Jha\n";
    cout << "Roll No.: 80117729\n";

    return 0;
}