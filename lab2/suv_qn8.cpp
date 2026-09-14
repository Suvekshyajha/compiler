#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct Quadruple
{
    string op, arg1, arg2, result;
};

unordered_map<string, int> varOffset;

int nextOffset = 2;

vector<string> regs = {"AX", "BX", "CX", "DX"};

int regIndex = 0;

int getOffset(const string& var)
{
    if (!varOffset.count(var))
    {
        varOffset[var] = nextOffset;
        nextOffset += 2;
    }

    return varOffset[var];
}

string allocReg()
{
    string r = regs[regIndex % regs.size()];

    if (regIndex >= (int)regs.size())
    {
        cout << "PUSH " << r << "\n";
    }

    regIndex++;

    return r;
}

void emitPrologue()
{
    cout << "PUSH BP\n";
    cout << "MOV BP, SP\n";

    // Reserve stack space for local variables and temporaries
    cout << "SUB SP, " << 20 << "\n";
}

void emitEpilogue()
{
    cout << "MOV SP, BP\n";
    cout << "POP BP\n";
    cout << "RET\n";
}

void generateAsm(const Quadruple& q)
{
    if (q.op == "+" || q.op == "-" || q.op == "*")
    {
        string reg = allocReg();

        cout << "MOV " << reg
             << ", [BP - " << getOffset(q.arg1) << "]\n";

        if (q.op == "+")
        {
            cout << "ADD " << reg
                 << ", [BP - " << getOffset(q.arg2) << "]\n";
        }
        else if (q.op == "-")
        {
            cout << "SUB " << reg
                 << ", [BP - " << getOffset(q.arg2) << "]\n";
        }
        else if (q.op == "*")
        {
            cout << "IMUL WORD PTR [BP - "
                 << getOffset(q.arg2) << "]\n";
        }

        cout << "MOV [BP - " << getOffset(q.result)
             << "], " << reg << "\n";
    }

    else if (q.op == "ifFalse")
    {
        string reg = allocReg();

        cout << "MOV " << reg
             << ", [BP - " << getOffset(q.arg1) << "]\n";

        cout << "CMP " << reg << ", 0\n";

        cout << "JE " << q.result << "\n";
    }
}

int main()
{
    vector<Quadruple> quadList =
    {
        {"+", "a", "b", "t1"},
        {"*", "a", "b", "t2"},
        {"ifFalse", "t1", "", "L1"}
    };

    // Allocate offsets before generating the prologue
    for (const auto& q : quadList)
    {
        if (q.arg1 != "")
            getOffset(q.arg1);

        if (q.arg2 != "")
            getOffset(q.arg2);

        if (q.result != "")
            getOffset(q.result);
    }

    emitPrologue();

    for (const auto& q : quadList)
        generateAsm(q);

    emitEpilogue();

    cout << "\nLab No.: 2\n";
    cout << "Name: Suvekshya Jha\n";
    cout << "Roll No.: 80117729\n";

    return 0;
}