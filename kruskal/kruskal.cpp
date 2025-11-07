#include <bits/stdc++.h>
using namespace std;

struct E { int u, v, w; };
struct DSU {
    vector<int> p, r;
    DSU(int n=0){init(n);}
    void init(int n){ p.resize(n); r.assign(n,0); iota(p.begin(),p.end(),0); }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    bool unite(int a,int b){
        a=find(a); b=find(b); if(a==b) return false;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a; if(r[a]==r[b]) r[a]++;
        return true;
    }
};

enum { OUT_FILE, IN_FILE, SOLUTION_OUT, BEGIN, END };
string options[] = {"", "", "0", "", ""};

void argParse(int argc, char* argv[]);
int  handleOption(int index, char* argv[]);
void validateOptions();
void printHelp();
void writeToFile(const string& content);

int n, m;
vector<E> edges;

void readFromFile();
pair<long long, vector<pair<int,int>>> kruskalAlg();
void printOut(const pair<long long, vector<pair<int,int>>>& ans);

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    argParse(argc, argv);
    readFromFile();
    pair<long long, vector<pair<int,int>>> ans = kruskalAlg();
    printOut(ans);
    return 0;
}

void argParse(int argc, char* argv[]) {
    if (argc == 1) { cout << "Argumentos faltando.\n"; printHelp(); exit(1); }
    for (int i = 1; i < argc; i++) i = handleOption(i, argv);
    validateOptions();
}
int handleOption(int index, char* argv[]) {
    string option = argv[index];
    if (option == "-h") { printHelp(); exit(0); }
    else if (option == "-o") { index++; options[OUT_FILE] = argv[index]; }
    else if (option == "-f") { index++; options[IN_FILE] = argv[index]; }
    else if (option == "-s") { options[SOLUTION_OUT] = "1"; }
    return index;
}
void validateOptions() {
    int count = 0;
    if (options[IN_FILE].empty()) { cout << "Arquivo de entrada faltando.\n"; count -= 1; }
    if (count < 0) { printHelp(); exit(1); }
}
void printHelp() {
    const int sp1 = 16;
    cout << left << setw(sp1) << "  -h" << ": mostra o help." << '\n';
    cout << setw(sp1) << "  -o <arquivo>" << ": redireciona a saida para o ''arquivo''" << '\n';
    cout << setw(sp1) << "  -f <arquivo>" << ": indica o ''arquivo'' que contÃ©m o grafo de entrada" << '\n';
    cout << setw(sp1) << "  -s" << ": mostra a soluÃ§Ã£o" << '\n';
}
void writeToFile(const string& content) { ofstream outFile(options[OUT_FILE]); outFile << content; }

void readFromFile() {
    ifstream in(options[IN_FILE]);
    if (!in) { cerr << "Erro ao abrir arquivo de entrada.\n"; exit(1); }
    in >> n >> m;
    edges.clear(); edges.reserve(m);
    for (int i = 0; i < m; i++) {
        int u, v, w; in >> u >> v >> w;
        edges.push_back((E){u-1, v-1, w});
    }
}

pair<long long, vector<pair<int,int>>> kruskalAlg() {
    sort(edges.begin(), edges.end(), [](const E& a, const E& b){ return a.w < b.w; });
    DSU dsu(n);
    long long cost = 0;
    vector<pair<int,int> > mst;
    for (size_t i = 0; i < edges.size(); ++i) {
        const E &e = edges[i];
        if (dsu.unite(e.u, e.v)) {
            cost += e.w;
            mst.push_back(make_pair(e.u+1, e.v+1));
        }
    }
    return make_pair(cost, mst);
}

void printOut(const pair<long long, vector<pair<int,int> > >& ans) {
    string out;
    if (options[SOLUTION_OUT] == "1") {
        for (size_t i = 0; i < ans.second.size(); ++i) {
            out += "(" + to_string(ans.second[i].first) + "," + to_string(ans.second[i].second) + ") ";
        }
    } else {
        out += to_string(ans.first);
    }
    out += "\n";
    if (options[OUT_FILE].empty()) cout << out; else writeToFile(out);
}
