#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

enum DataType { TYPE_INT, TYPE_FLOAT, TYPE_BOOL, TYPE_ERROR };

class IfNode; class WhileNode; class ForNode;
class BreakNode; class ContinueNode; class ExprNode; class VarNode;

class Visitor {
public:
    virtual DataType visit(IfNode*) = 0;
    virtual DataType visit(WhileNode*) = 0;
    virtual DataType visit(ForNode*) = 0;
    virtual DataType visit(BreakNode*) = 0;
    virtual DataType visit(ContinueNode*) = 0;
    virtual DataType visit(ExprNode*) = 0;
    virtual DataType visit(VarNode*) = 0;
    virtual ~Visitor() {}
};

class ASTNode {
public:
    int line;
    virtual DataType accept(Visitor*) = 0;
    virtual ~ASTNode() {}
};

class ExprNode : public ASTNode {
public:
    DataType type;
    ExprNode(DataType t, int l) : type(t) { line = l; }
    DataType accept(Visitor* v) { return v->visit(this); }
};

class VarNode : public ASTNode {
public:
    string name;
    DataType type;
    bool is_initialized;

    VarNode(string n, DataType t, bool init, int l)
        : name(n), type(t), is_initialized(init) { line = l; }

    DataType accept(Visitor* v) { return v->visit(this); }
};

class IfNode : public ASTNode {
public:
    ASTNode *cond, *body;
    IfNode(ASTNode* c, ASTNode* b, int l) : cond(c), body(b) { line = l; }
    DataType accept(Visitor* v) { return v->visit(this); }
};

class WhileNode : public IfNode {
public:
    WhileNode(ASTNode* c, ASTNode* b, int l) : IfNode(c,b,l) {}
    DataType accept(Visitor* v) { return v->visit(this); }
};

class ForNode : public IfNode {
public:
    ForNode(ASTNode* c, ASTNode* b, int l) : IfNode(c,b,l) {}
    DataType accept(Visitor* v) { return v->visit(this); }
};

class BreakNode : public ASTNode {
public:
    BreakNode(int l) { line = l; }
    DataType accept(Visitor* v) { return v->visit(this); }
};

class ContinueNode : public ASTNode {
public:
    ContinueNode(int l) { line = l; }
    DataType accept(Visitor* v) { return v->visit(this); }
};

class SemanticAnalyzer : public Visitor {
    int loop_depth = 0;
    unordered_map<string, bool> initialized;

    void checkCondition(ASTNode* c) {
        DataType t = c->accept(this);
        if (t != TYPE_BOOL && t != TYPE_INT)
            cout << "Line " << c->line
                 << ": Condition must be BOOL or INT\n";
    }

public:
    DataType visit(ExprNode* n) { return n->type; }

    DataType visit(VarNode* n) {
        if (!n->is_initialized)
            cout << "Line " << n->line
                 << ": Warning - '" << n->name
                 << "' used before initialization\n";
        return n->type;
    }

    DataType visit(IfNode* n) {
        checkCondition(n->cond);
        if (n->body) n->body->accept(this);
        return TYPE_BOOL;
    }

    DataType visit(WhileNode* n) {
        checkCondition(n->cond);
        loop_depth++;
        if (n->body) n->body->accept(this);
        loop_depth--;
        return TYPE_BOOL;
    }

    DataType visit(ForNode* n) {
        checkCondition(n->cond);
        loop_depth++;
        if (n->body) n->body->accept(this);
        loop_depth--;
        return TYPE_BOOL;
    }

    DataType visit(BreakNode* n) {
        if (loop_depth == 0)
            cout << "Line " << n->line
                 << ": Error - break outside loop\n";
        return TYPE_BOOL;
    }

    DataType visit(ContinueNode* n) {
        if (loop_depth == 0)
            cout << "Line " << n->line
                 << ": Error - continue outside loop\n";
        return TYPE_BOOL;
    }
};

int main() {
    SemanticAnalyzer a;

    ExprNode boolCond(TYPE_BOOL, 1);
    ExprNode floatCond(TYPE_FLOAT, 2);

    BreakNode br(3);
    ContinueNode con(4);

    WhileNode w(&boolCond, &br, 1);
    w.accept(&a);

    ForNode f(&boolCond, &con, 4);
    f.accept(&a);

    IfNode invalidIf(&floatCond, nullptr, 5);
    invalidIf.accept(&a);

    BreakNode outsideBreak(6);
    outsideBreak.accept(&a);

    VarNode x("x", TYPE_INT, false, 7);
    x.accept(&a);

    cout << "\nLab No.: 2\n";
    cout << "Name: Suvekshya Jha\n";
    cout << "Roll No.: 80117729\n";

    return 0;
}