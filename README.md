# Algoritmos de Grafos (UFAL)

Este repositório contém a implementação dos 4 algoritmos solicitados no trabalho:

1. **Kosaraju** – Componentes Fortemente Conexas
2. **Prim** – Árvore Geradora Mínima
3. **Kruskal** – Árvore Geradora Mínima
4. **Dijkstra** – Caminho Mínimo

Cada algoritmo está em **sua própria pasta** e possui **um Makefile**, conforme as regras do trabalho.

## Estrutura do projeto

```text
.
├── kosaraju/
│   ├── kosaraju.cpp
│   └── Makefile
├── prim/
│   ├── prim.cpp
│   └── Makefile
├── kruskal/
│   ├── kruskal.cpp
│   └── Makefile
└── dijkstra/
    ├── dijkstra.cpp
    └── Makefile
```

## Requisitos

- Compilador C++ (ex.: `g++`)
- `make` ou `mingw32-make` (no Windows pode ter esse nome)

No Windows com Git Bash, se `make` não existir, tente:

```bash
mingw32-make
```

## Como compilar

Entre na pasta do algoritmo e rode o make.

### Kosaraju

```bash
cd kosaraju
make        # ou mingw32-make
```

### Prim

```bash
cd prim
make
```

### Kruskal

```bash
cd kruskal
make
```

### Dijkstra

```bash
cd dijkstra
make
```

Isso vai gerar os binários com os nomes exigidos pelo trabalho:

- `kosaraju`
- `prim`
- `kruskal`
- `dijkstra`

## Formatos e execução

### 1. Kosaraju

**Parâmetros:**

- `-h` : mostra o help
- `-o <arquivo>` : redireciona a saída
- `-f <arquivo>` : arquivo de entrada (grafo dirigido)

**Exemplo:**

```bash
./kosaraju -f arquivo-entrada.dat
```

Saída: cada componente fortemente conexa em uma linha, vértices separados por espaço.

### 2. Prim

**Parâmetros:**

- `-h`
- `-o <arquivo>`
- `-f <arquivo>`
- `-s` : mostra as arestas da AGM
- `-i <v>` : vértice inicial (se não passar, assume 1 – compatível com Bat1)

**Exemplos:**

```bash
# só custo
./prim -f arquivo-entrada.dat

# custo começando do vértice 1 e mostrando arestas
./prim -f arquivo-entrada.dat -i 1 -s
```

A saída com `-s` é no formato:

```text
(1,3) (1,4) (2,4) ...
```

### 3. Kruskal

**Parâmetros:**

- `-h`
- `-o <arquivo>`
- `-f <arquivo>`
- `-s` : mostra as arestas da AGM

**Exemplo:**

```bash
./kruskal -f arquivo-entrada.dat
./kruskal -f arquivo-entrada.dat -s
```

Também imprime as arestas como `(u,v)`, formato aceito pelo `Bat1.sh`.

### 4. Dijkstra

**Parâmetros:**

- `-h`
- `-o <arquivo>`
- `-f <arquivo>`
- `-i <v>` : vértice inicial (se não passar, assume 1 – compatível com Bat1)

**Exemplo:**

```bash
./dijkstra -f arquivo-entrada.dat -i 1
```

**Saída (formato exigido):**

```text
1:0 2:3 3:4 4:2 5:10 6:3
```

- uma linha só
- vértices separados por espaço
- se um vértice for inalcançável → `id:-1`

## Testes (Bat1)

Os códigos foram escritos para passar na bateria de testes **Bat1** da disciplina:

- `prim` e `dijkstra` assumem vértice inicial 1 quando `-i` não é informado;
- `prim` e `kruskal` imprimem arestas no formato `(u,v)` que o script consegue checar com o programa `agm`;
- `dijkstra` imprime exatamente no formato dos arquivos da pasta `sp/`.

## Limpeza

Para remover os binários gerados em cada pasta:

```bash
make clean
# ou
mingw32-make clean
```
