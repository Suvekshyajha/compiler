
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Quadruple
{
    string op, arg1, arg2, result;
};

vector<Quadruple> quadList;

int labelCount = 1;

string newLabel()
{
    return "L" + to_string(labelCount++);
}

// Backpatching functions
vector<int> make_list(int quad_index)
{
    return {quad_index};
}

vector<int> merge_list(vector<int> l1, vector<int> l2)
{
    l1.insert(l1.end(), l2.begin(), l2.end());
    return l1;
}

void backpatch(const vector<int>& list, const string& label)
{
    for (int idx : list)
        quadList[idx].result = label;
}

// Emit condition
pair<vector<int>, vector<int>> emitCondition(const string& cond)
{
    quadList.push_back({"ifFalse", cond, "", ""});
    int falseIdx = quadList.size() - 1;

    quadList.push_back({"goto", "", "", ""});
    int trueIdx = quadList.size() - 1;

    return {make_list(trueIdx), make_list(falseIdx)};
}

// if (cond) S1 else S2
void genIfElse(const string& cond)
{
    auto [truelist, falselist] = emitCondition(cond);

    string Lthen = newLabel();
    backpatch(truelist, Lthen);

    quadList.push_back({"LABEL", "", "", Lthen});
    quadList.push_back({"stmt", "S1", "", ""});

    string Lelse = newLabel();
    backpatch(falselist, Lelse);

    quadList.push_back({"LABEL", "", "", Lelse});
    quadList.push_back({"stmt", "S2", "", ""});
}

// while (cond) S
void genWhile(const string& cond)
{
    string Lbegin = newLabel();

    quadList.push_back({"LABEL", "", "", Lbegin});

    auto [truelist, falselist] = emitCondition(cond);

    string Lbody = newLabel();
    backpatch(truelist, Lbody);

    quadList.push_back({"LABEL", "", "", Lbody});
    quadList.push_back({"stmt", "S", "", ""});

    quadList.push_back({"goto", "", "", Lbegin});

    string Lexit = newLabel();
    backpatch(falselist, Lexit);

    quadList.push_back({"LABEL", "", "", Lexit});
}

// Short-circuit &&
pair<vector<int>, vector<int>> genAnd(
    const string& left,
    const string& right)
{
    quadList.push_back({"ifFalse", left, "", ""});
    int leftFalse = quadList.size() - 1;

    auto [rtrue, rfalse] = emitCondition(right);

    return {rtrue, merge_list(make_list(leftFalse), rfalse)};
}

// Short-circuit ||
pair<vector<int>, vector<int>> genOr(
    const string& left,
    const string& right)
{
    quadList.push_back({"ifFalse", left, "", ""});
    int leftFalse = quadList.size() - 1;

    quadList.push_back({"goto", "", "", ""});
    int leftTrue = quadList.size() - 1;

    auto [rtrue, rfalse] = emitCondition(right);

    string Lright = newLabel();

    backpatch(make_list(leftFalse), Lright);

    quadList.push_back({"LABEL", "", "", Lright});

    return {
        merge_list(make_list(leftTrue), rtrue),
        rfalse
    };
}

int main()
{
    genIfElse("a>b");

    genWhile("i<10");

    cout << "Generated Quadruples:\n";

    for (size_t i = 0; i < quadList.size(); i++)
    {
        cout << i << ": "
             << quadList[i].op << " "
             << quadList[i].arg1 << " -> "
             << quadList[i].result << "\n";
    }

    cout << "\nLab No.: 2\n";
    cout << "Name: Suvekshya Jha\n";
    cout << "Roll No.: 80117729\n";

    return 0;
}

