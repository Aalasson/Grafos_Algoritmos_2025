#include <bits/stdc++.h>
using namespace std;

struct Edge { int to; int w; };
enum { OUT_FILE, IN_FILE, SOLUTION_OUT, BEGIN, END };
string options[] = {"", "", "0", "", ""};

void argParse(int argc, char* argv[]);
int  handleOption(int index, char* argv[]);
void validateOptions();
void printHelp();
void writeToFile(const string& content);
bool isNumber(const string& s);

int n, m;
vector<vector<Edge>> adj;
vector<long long> distv;

void readFromFile();
void dijkstraAlg(int start);
void printOut();

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    argParse(argc, argv);
    readFromFile();

    
    int start = 1;
    if (!options[BEGIN].empty() && isNumber(options[BEGIN])) {
        start = atoi(options[BEGIN].c_str());
    }

    dijkstraAlg(start - 1);
    printOut();
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
    else if (option == "-i") { index++; options[BEGIN] = argv[index]; }
    return index;
}

void validateOptions() {
    int ok = 1;
    // agora só exigimos o arquivo
    if (options[IN_FILE].empty()) {
        cout << "Arquivo de entrada faltando.\n";
        ok = 0;
    }
    if (!ok) { printHelp(); exit(1); }
}

void printHelp() {
    const int sp1 = 16;
    cout << left << setw(sp1) << "  -h" << ": mostra o help." << '\n';
    cout << setw(sp1) << "  -o <arquivo>" << ": redireciona a saida para o ''arquivo''" << '\n';
    cout << setw(sp1) << "  -f <arquivo>" << ": indica o ''arquivo'' que contem o grafo de entrada" << '\n';
    cout << setw(sp1) << "  -i" << ": vertice inicial (padrao = 1)" << '\n';
}

bool isNumber(const string& s) {
    return !s.empty() &&
        find_if(s.begin(), s.end(),
                [](unsigned char c){ return !isdigit(c); }) == s.end();
}

void writeToFile(const string& content) {
    ofstream outFile(options[OUT_FILE]);
    outFile << content;
}

void readFromFile() {
    ifstream in(options[IN_FILE]);
    if (!in) { cerr << "Erro ao abrir arquivo de entrada.\n"; exit(1); }
    in >> n >> m;
    adj.assign(n, vector<Edge>());

    for (int i = 0; i < m; i++) {
        int u, v, w;
        in >> u >> v >> w;
        --u; --v;
        adj[u].push_back((Edge){v, w});
        adj[v].push_back((Edge){u, w});
    }
}

void dijkstraAlg(int start) {
    const long long INF = (1LL<<60);
    distv.assign(n, INF);
    vector<char> vis(n, 0);
    typedef pair<long long,int> P;
    priority_queue<P, vector<P>, greater<P> > pq;

    distv[start] = 0;
    pq.push(P(0, start));

    while (!pq.empty()) {
        P cur = pq.top(); pq.pop();
        long long d = cur.first;
        int u = cur.second;
        if (vis[u]) continue;
        vis[u] = 1;
        for (size_t i = 0; i < adj[u].size(); ++i) {
            Edge e = adj[u][i];
            if (distv[e.to] > d + e.w) {
                distv[e.to] = d + e.w;
                pq.push(P(distv[e.to], e.to));
            }
        }
    }
}

void printOut() {
    string out;
    for (int i = 0; i < n; i++) {
        long long val = distv[i];
        if (val >= (1LL<<60)/2) val = -1;
        out += to_string(i+1) + ":" + to_string(val);
        if (i + 1 < n) out += " ";
    }
    out += "\n";
    if (options[OUT_FILE].empty()) cout << out; else writeToFile(out);
}
