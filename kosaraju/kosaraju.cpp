#include <bits/stdc++.h>
using namespace std;

enum { OUT_FILE, IN_FILE, SOLUTION_OUT, BEGIN, END };
string options[] = {"", "", "0", "", ""};

void argParse(int argc, char* argv[]);
int  handleOption(int index, char* argv[]);
void validateOptions();
void printHelp();
void writeToFile(const string& content);

int n, m;
vector<vector<int> > g, gr;
vector<int> order;
vector<char> used;

void readFromFile();
vector<vector<int> > kosarajuAlg();
void printOut(const vector<vector<int> >& comps);

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    argParse(argc, argv);
    readFromFile();
    vector<vector<int> > comps = kosarajuAlg();
    printOut(comps);
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
}
void writeToFile(const string& content) { ofstream outFile(options[OUT_FILE]); outFile << content; }

void readFromFile() {
    ifstream in(options[IN_FILE]);
    if (!in) { cerr << "Erro ao abrir arquivo de entrada.\n"; exit(1); }
    in >> n >> m;
    g.assign(n, vector<int>()); gr.assign(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v; in >> u >> v;
        --u; --v;
        g[u].push_back(v);
        gr[v].push_back(u);
    }
}

void dfs1(int v){
    used[v] = 1;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to]) dfs1(to);
    }
    order.push_back(v);
}
void dfs2(int v, vector<int>& cur){
    used[v] = 1; cur.push_back(v);
    for (size_t i = 0; i < gr[v].size(); ++i) {
        int to = gr[v][i];
        if (!used[to]) dfs2(to, cur);
    }
}

vector<vector<int> > kosarajuAlg() {
    used.assign(n, 0); order.clear();
    for (int v = 0; v < n; v++) if (!used[v]) dfs1(v);
    used.assign(n, 0);
    vector<vector<int> > comps;
    for (int i = (int)order.size()-1; i >= 0; i--) {
        int v = order[i];
        if (!used[v]) {
            vector<int> cur; dfs2(v, cur);
            sort(cur.begin(), cur.end());
            for (size_t j = 0; j < cur.size(); ++j) cur[j] += 1;
            comps.push_back(cur);
        }
    }
    return comps;
}

void printOut(const vector<vector<int> >& comps) {
    string out;
    for (size_t i = 0; i < comps.size(); ++i) {
        const vector<int>& c = comps[i];
        for (size_t j = 0; j < c.size(); ++j) {
            out += to_string(c[j]);
            if (j + 1 < c.size()) out += " ";
        }
        out += "\n";
    }
    if (options[OUT_FILE].empty()) cout << out; else writeToFile(out);
}
