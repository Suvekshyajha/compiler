
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct Quadruple
{
    string op, arg1, arg2, result;
};

vector<Quadruple> quadList;

int tempCount = 1;

string newTemp()
{
    return "t" + to_string(tempCount++);
}

// Symbol table: function name -> declared parameter count
unordered_map<string, int> funcParamCount;

void declareFunction(const string& name, int paramCount)
{
    funcParamCount[name] = paramCount;

    quadList.push_back({"FUNC_BEGIN", name, "", ""});
}

void endFunction(const string& name)
{
    quadList.push_back({"FUNC_END", name, "", ""});
}

void genReturn(const string& value)
{
    quadList.push_back({"RETURN", value, "", ""});
}

// Generate PARAM and CALL quads
string genCall(const string& funcName, const vector<string>& args)
{
    // Signature verification
    if (!funcParamCount.count(funcName))
    {
        cout << "Error: Function " << funcName
             << " is not declared.\n";
        return "";
    }

    if (funcParamCount[funcName] != (int)args.size())
    {
        cout << "Error: " << funcName
             << " expects " << funcParamCount[funcName]
             << " args, got " << args.size() << "\n";
        return "";
    }

    // Parameter passing by value
    for (const auto& arg : args)
        quadList.push_back({"PARAM", arg, "", ""});

    // Function call
    string resultTemp = newTemp();

    quadList.push_back(
        {"CALL", funcName, to_string(args.size()), resultTemp}
    );

    return resultTemp;
}

int main()
{
    // Function declaration:
    // foo(a, b) { return x; }

    declareFunction("foo", 2);

    quadList.push_back({"PARAM_DECL", "a", "", ""});
    quadList.push_back({"PARAM_DECL", "b", "", ""});

    genReturn("x");

    endFunction("foo");

    // Function call:
    // x = foo(a, b)

    string t = genCall("foo", {"a", "b"});

    if (!t.empty())
        quadList.push_back({"=", t, "", "x"});

    cout << "Generated Quadruples:\n";

    for (const auto& q : quadList)
    {
        cout << q.op << "\t"
             << q.arg1 << "\t"
             << q.arg2 << "\t"
             << q.result << "\n";
    }

    cout << "\nLab No.: 2\n";
    cout << "Name: Suvekshya Jha\n";
    cout << "Roll No.: 80117729\n";

    return 0;
}

