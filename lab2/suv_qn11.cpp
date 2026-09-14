#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Parses "MOV dest, src"
bool parseMov(const string& instr, string& dest, string& src)
{
    if (instr.size() < 4 || instr.substr(0, 3) != "MOV")
        return false;

    stringstream ss(instr.substr(4));

    getline(ss, dest, ',');
    ss >> src;

    return true;
}

void applyPeephole(vector<string>& instrs)
{
    bool changed = true;

    while (changed)
    {
        changed = false;

        for (size_t i = 0; i < instrs.size(); i++)
        {
            // Unreachable code removal
            // Delete instructions after JMP until next label
            if (instrs[i].substr(0, 4) == "JMP " &&
                i + 1 < instrs.size())
            {
                size_t j = i + 1;

                while (j < instrs.size() &&
                       instrs[j].back() != ':')
                {
                    instrs.erase(instrs.begin() + j);
                    changed = true;
                }

                if (changed)
                    break;
            }

            if (i + 1 >= instrs.size())
                continue;

            string dest1, src1, dest2, src2;

            // Redundant Load/Store
            // MOV AX, [BP-2]
            // MOV [BP-2], AX
            if (parseMov(instrs[i], dest1, src1) &&
                parseMov(instrs[i + 1], dest2, src2))
            {
                if (dest1 == src2 && src1 == dest2)
                {
                    instrs.erase(instrs.begin() + i + 1);
                    changed = true;
                    break;
                }
            }

            // Algebraic identities
            if (instrs[i] == "ADD AX, 0" ||
                instrs[i] == "SUB AX, 0" ||
                instrs[i] == "MUL AX, 1")
            {
                instrs.erase(instrs.begin() + i);
                changed = true;
                break;
            }

            // MUL AX, 0 -> MOV AX, 0
            if (instrs[i] == "MUL AX, 0")
            {
                instrs[i] = "MOV AX, 0";
                changed = true;
                break;
            }

            // Strength reduction
            // IMUL AX, 2 -> SHL AX, 1
            if (instrs[i] == "IMUL AX, 2")
            {
                instrs[i] = "SHL AX, 1";
                changed = true;
                break;
            }

            // Redundant jump
            // JMP L1
            // L1:
            if (instrs[i].substr(0, 4) == "JMP " &&
                instrs[i + 1] == instrs[i].substr(4) + ":")
            {
                instrs.erase(instrs.begin() + i);
                changed = true;
                break;
            }
        }
    }
}

int main()
{
    vector<string> instrs =
    {
        "MOV AX, [BP-2]",
        "MOV [BP-2], AX",
        "ADD AX, 0",
        "MUL AX, 0",
        "IMUL AX, 2",
        "JMP L1",
        "MOV BX, AX",
        "MOV CX, BX",
        "L1:"
    };

    applyPeephole(instrs);

    cout << "Optimized instructions:\n";

    for (const auto& i : instrs)
        cout << i << "\n";

    cout << "\nLab No.: 2\n";
    cout << "Name: Suvekshya Jha\n";
    cout << "Roll No.: 80117729\n";

    return 0;
}