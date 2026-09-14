#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

struct P { string l; vector<string> r; };

struct I {
    int p,d; string la;
    bool operator<(const I& x) const {
        if(p!=x.p) return p<x.p;
        if(d!=x.d) return d<x.d;
        return la<x.la;
    }
    bool operator==(const I& x) const {
        return p==x.p && d==x.d && la==x.la;
    }
};

vector<P> g={
    {"S'",{"S"}},{"S",{"E"}},
    {"E",{"E","+","T"}},{"E",{"T"}},
    {"T",{"T","*","F"}},{"T",{"F"}},
    {"F",{"(","E",")"}},{"F",{"id"}}
};

set<string>N,T;
map<string,set<string>> F;
vector<set<I>> C;
map<pair<int,string>,int> go;

set<string> first(vector<string> v){
    set<string> r;
    bool nullable=true;
    for(string x:v){
        if(T.count(x)){r.insert(x); nullable=false; break;}
        for(string y:F[x]) if(y!="#") r.insert(y);
        if(!F[x].count("#")){ nullable=false; break; }
    }
    if(nullable) r.insert("#");
    return r;
}

void makeFirst(){
    for(string t:T) F[t]={t};          // FIRST of every terminal is itself (fix)
    bool ch=true;
    while(ch){
        ch=false;
        for(auto p:g){
            auto old=F[p.l];
            if(p.r.empty()){ F[p.l].insert("#"); }
            bool nullable=true;
            for(string x:p.r){
                for(string y:F[x])
                    if(y!="#") F[p.l].insert(y);
                if(!F[x].count("#")){ nullable=false; break; }
            }
            if(nullable) F[p.l].insert("#");     // whole RHS nullable (fix, general case)
            if(old!=F[p.l]) ch=true;
        }
    }
}

set<I> closure(set<I> s){
    bool ch=true;
    while(ch){
        ch=false;
        for(auto x:s){
            if(x.d>=(int)g[x.p].r.size()) continue;
            string B=g[x.p].r[x.d];
            if(!N.count(B)) continue;

            vector<string>b;
            for(int i=x.d+1;i<(int)g[x.p].r.size();i++)
                b.push_back(g[x.p].r[i]);
            b.push_back(x.la);

            for(string la:first(b))
                for(int i=0;i<(int)g.size();i++)
                    if(g[i].l==B)
                        if(s.insert({i,0,la}).second) ch=true;
        }
    }
    return s;
}

set<I> GOTO(set<I>s,string x){
    set<I> r;
    for(auto i:s)
        if(i.d<(int)g[i.p].r.size()&&g[i.p].r[i.d]==x)
            r.insert({i.p,i.d+1,i.la});
    return r.empty()?r:closure(r);
}

void print(I x){
    cout<<"  "<<g[x.p].l<<" -> ";
    for(int i=0;i<=(int)g[x.p].r.size();i++){
        if(i==x.d) cout<<". ";
        if(i<(int)g[x.p].r.size()) cout<<g[x.p].r[i]<<" ";
    }
    cout<<", "<<x.la<<"\n";
}

int main(){

    cout<<"Lab No.: 1\n";
    cout<<"Name: Suvekshya Jha\n";
    cout<<"Roll No.: 80117729\n\n";

    for(auto p:g){
        N.insert(p.l);
        for(string x:p.r) T.insert(x);
    }

    for(string x:N) T.erase(x);
    T.insert("$");

    makeFirst();

    C.push_back(closure({{0,0,"$"}}));

    for(int i=0;i<(int)C.size();i++){
        set<string>s;

        for(auto x:C[i])
            if(x.d<(int)g[x.p].r.size())
                s.insert(g[x.p].r[x.d]);

        for(string x:s){
            auto z=GOTO(C[i],x);
            int j=-1;

            for(int k=0;k<(int)C.size();k++)
                if(C[k]==z) j=k;

            if(j==-1){
                j=C.size();
                C.push_back(z);
            }

            go[{i,x}]=j;
        }
    }

    cout<<"===== CANONICAL LR(1) ITEMS =====\n";

    for(int i=0;i<(int)C.size();i++){
        cout<<"\nI"<<i<<":\n";
        for(auto x:C[i]) print(x);
    }

    map<pair<int,string>,string>A;
    bool conflict=false;

    for(int i=0;i<(int)C.size();i++)
        for(auto x:C[i]){
            auto p=g[x.p];

            if(x.d<(int)p.r.size()){
                string a=p.r[x.d];
                if(T.count(a)&&go.count({i,a})){
                    string act="s"+to_string(go[{i,a}]);
                    auto key=make_pair(i,a);
                    if(A.count(key)&&A[key]!=act) conflict=true;
                    A[key]=act;
                }
            }
            else if(p.l=="S'" && x.la=="$"){
                A[{i,"$"}]="acc";
            }
            else {
                string act="r"+to_string(x.p);
                auto key=make_pair(i,x.la);
                if(A.count(key)&&A[key]!=act) conflict=true;
                A[key]=act;
            }
        }

    vector<string>ts(T.begin(),T.end());
    vector<string>ns;

    for(string x:N)
        if(x!="S'") ns.push_back(x);

    cout<<"\n===== LR(1) PARSING TABLE =====\n\n";
    cout<<left<<setw(8)<<"State";

    for(string x:ts) cout<<setw(8)<<x;
    for(string x:ns) cout<<setw(8)<<x;

    cout<<"\n"<<string(8+8*(ts.size()+ns.size()),'-')<<"\n";

    for(int i=0;i<(int)C.size();i++){
        cout<<setw(8)<<i;

        for(string x:ts)
            cout<<setw(8)<<A[{i,x}];

        for(string x:ns)
            cout<<setw(8)
                <<(go.count({i,x})?to_string(go[{i,x}]):"");

        cout<<"\n";
    }

    if(conflict) cout<<"\n[!] Conflicts detected -> grammar is NOT LR(1).\n";

    return 0;
}