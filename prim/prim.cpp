#include <bits/stdc++.h>
using namespace std;

struct Edge { int to; int w; };

// índices das opções
enum { OUT_FILE, IN_FILE, SOLUTION_OUT, BEGIN, END };
string options[] = {"", "", "0", "", ""};

void argParse(int argc, char* argv[]);
int  handleOption(int index, char* argv[]);
void validateOptions();
void printHelp();
void writeToFile(const string& content);
bool isNumber(const string& s);

vector< vector<Edge> > adj;
int n, m;

void readFromFile();
pair<long long, vector< pair<int,int> > > primAlg(int start);
void printOut(const pair<long long, vector< pair<int,int> > >& ans);

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    argParse(argc, argv);
    readFromFile();

    // se não vier -i, usa 1
    int start = 1;
    if (!options[BEGIN].empty() && isNumber(options[BEGIN])) {
        start = atoi(options[BEGIN].c_str());
    }

    pair<long long, vector< pair<int,int> > > ans = primAlg(start - 1);
    printOut(ans);
    return 0;
}

void argParse(int argc, char* argv[]) {
    if (argc == 1) {
        cout << "Argumentos faltando.\n";
        printHelp();
        exit(1);
    }
    for (int i = 1; i < argc; i++)
        i = handleOption(i, argv);
    validateOptions();
}

int handleOption(int index, char* argv[]) {
    string option = argv[index];
    if (option == "-h") {
        printHelp();
        exit(0);
    } else if (option == "-o") {
        index++;
        options[OUT_FILE] = argv[index];
    } else if (option == "-f") {
        index++;
        options[IN_FILE] = argv[index];
    } else if (option == "-s") {
        options[SOLUTION_OUT] = "1";
    } else if (option == "-i") {
        index++;
        options[BEGIN] = argv[index];
    }
    return index;
}

void validateOptions() {
    int ok = 1;
    if (options[IN_FILE].empty()) {
        cout << "Arquivo de entrada faltando.\n";
        ok = 0;
    }
    if (!ok) {
        printHelp();
        exit(1);
    }
}

void printHelp() {
    const int sp1 = 16;
    cout << left << setw(sp1) << "  -h" << ": mostra o help." << '\n';
    cout << setw(sp1) << "  -o <arquivo>" << ": redireciona a saida para o 'arquivo'" << '\n';
    cout << setw(sp1) << "  -f <arquivo>" << ": indica o 'arquivo' que contem o grafo de entrada" << '\n';
    cout << setw(sp1) << "  -s" << ": mostra a solucao" << '\n';
    cout << setw(sp1) << "  -i" << ": vertice inicial (padrao = 1)" << '\n';
}

bool isNumber(const string& s) {
    if (s.empty()) return false;
    for (size_t i = 0; i < s.size(); i++) {
        if (!isdigit((unsigned char)s[i])) return false;
    }
    return true;
}

void writeToFile(const string& content) {
    ofstream outFile(options[OUT_FILE].c_str());
    outFile << content;
}

void readFromFile() {
    ifstream in(options[IN_FILE].c_str());
    if (!in) {
        cerr << "Erro ao abrir arquivo de entrada.\n";
        exit(1);
    }
    in >> n >> m;
    adj.assign(n, vector<Edge>());
    for (int i = 0; i < m; i++) {
        int u, v, w;
        in >> u >> v >> w;
        u--; v--;
        Edge e1; e1.to = v; e1.w = w;
        Edge e2; e2.to = u; e2.w = w;
        adj[u].push_back(e1);
        adj[v].push_back(e2);
    }
}

pair<long long, vector< pair<int,int> > > primAlg(int start) {
    vector<char> vis(n, 0);
    vector<int> parent(n, -1), key(n, INT_MAX);

    typedef pair<int,int> T; // (peso, vertice)
    priority_queue< T, vector<T>, greater<T> > pq;

    key[start] = 0;
    pq.push(T(0, start));

    long long cost = 0;
    vector< pair<int,int> > edges;

    while (!pq.empty()) {
        T cur = pq.top(); pq.pop();
        int w = cur.first;
        int u = cur.second;

        if (vis[u]) continue;

        vis[u] = 1;
        cost += w;

        if (parent[u] != -1) {
            edges.push_back( make_pair(parent[u] + 1, u + 1) );
        }

        for (size_t i = 0; i < adj[u].size(); i++) {
            Edge e = adj[u][i];
            if (!vis[e.to] && e.w < key[e.to]) {
                key[e.to] = e.w;
                parent[e.to] = u;
                pq.push(T(e.w, e.to));
            }
        }
    }

    return make_pair(cost, edges);
}

void printOut(const pair<long long, vector< pair<int,int> > >& ans) {
    string out;
    if (options[SOLUTION_OUT] == "1") {
        for (size_t i = 0; i < ans.second.size(); ++i) {
            out += "(";
            out += to_string(ans.second[i].first);
            out += ",";
            out += to_string(ans.second[i].second);
            out += ") ";
        }
    } else {
        out += to_string(ans.first);
    }
    out += "\n";

    if (options[OUT_FILE].empty())
        cout << out;
    else
        writeToFile(out);
}
