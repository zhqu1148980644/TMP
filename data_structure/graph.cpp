#ifndef GRAPH
#define GRAPH

#ifndef TEST
#define TEST
#define TEST_GRAPH
#endif

#include "stack.cpp"
#include "vector.cpp"
#include "queue.cpp"

typedef enum { UNDISCOVERED, DISCOVERED, VISITED} VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EStatus;



template <typename Tv, typename Te>
class Graph {
private:
    void reset() {
        for (int i = 0; i < n; i++) {
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) = -1;
            parent(i) = -1; priority(i) = INT_MAX;
            for (int j = 0; j < n; j++)
                if (exists(i, j)) status(i, j) = UNDETERMINED;
        }
    }
    void BFS(int, int &);
    void DFS(int, int &);
    void BCC(int, int &, Stack<int> &);
    bool TSort(int, int &, Stack<Tv> *);
    template <typename PU> void PFS(int, PU);

public:
    int n ;
    virtual int insert(Tv const &) = 0;
    virtual Tv remove(int) = 0;
    virtual Tv & vertex(int) = 0;
    virtual int inDegree(int) = 0;
    virtual int outDegree(int) = 0;
    virtual int firstNbr(int) = 0;
    virtual int nextNbr(int, int) = 0;
    virtual VStatus & status(int) = 0;
    virtual int & dTime(int) = 0;
    virtual int & fTime(int) = 0;
    virtual int & parent(int) = 0;
    virtual int & priority(int) = 0;

    int e;
    virtual bool exists(int, int) = 0;
    virtual void insert(Te const &, int, int, int) = 0;
    virtual Te remove(int, int) = 0;
    virtual EStatus & status(int, int) = 0;
    virtual Te & edge(int, int) = 0;
    virtual int & weight(int, int) = 0;

    void bfs(int);
    void dfs(int);
    void bcc(int);
    Stack<Tv> * tSort(int);
    void prim(int);
    void dijkstra(int);
    template <typename PU> void pfs(int, PU);
};



template <typename Tv>
class Vertex {
public:
    Tv data;
    int inDegree;
    int outDegree;
    VStatus status;
    int dTime;
    int fTime;
    int parent;
    int priority;

    Vertex(Tv const & d = (Tv) 0) : data(d), inDegree(0), outDegree(0), 
        status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}

};


template <typename Te>
class Edge {
public:
    Te data;
    int weight;
    EStatus status;
    Edge(Te const & d, int w) : data(d), weight(w), status(UNDISCOVERED) {}
};

template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te> {
private:
    Vector<Vertex<Tv>> V;
    Vector<Vector<Edge<Te> *>> E;

public:
    GraphMatrix() {n = e = 0;}
    virtual ~GraphMatrix() {
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                del E[j][k];
    }
    virtual Tv & vertex(int i) { return V[i].data; }
    virtual int inDegree(int i) { return V[i].inDegree; }
    virtual int outDegree(int i ) { return V[i].outDegree; }
    virtual int firstNbr(int i) { return nextNbr(i, n); }
    virtual int nextNbr(int i, int j) {
        while ((-1 < j) && (!exists(i, --j))); return j;
    }
    virtual VStatus & status(int i) { return V[i].status; }
    virtual int & dTime(int i) { return V[i].dTime; }
    virtual int & fTime(int i) { return V[i].fTime; }
    virtual int & parent(int i) { return V[i].parent; }
    virtual int & priority(int i) { return V[i].priority; }
    virtual int insert(Tv const & vertex) {
        for (int j = 0; j < n; j++) E[j].push_back(NULL);
        n++;
        E.push_back(Vector<Edge<Te> *>(n, n, (Edge<Te> *) NULL));
        return V.push_back(Vertex<Tv>(vertex));
    }
    virtual Tv remove(int i) { 
        for (int j = 0; j < n; j++)
            if (exists(i, j)) {
                delete E[i][j]; V[j].inDegree--;
            }
        E.remove(i); n--;
        for (int j = 0; j < n; j++)
            if (exists(j, i)) {
                delete E[j].remove(i); V[j].outDegree--;
            }
        Tv vBack = vertex(i); V.remove(i);

        return vBack;
    }
    virtual bool exists(int i, int j) {
        return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL; 
    }
    virtual EStatus & status(int i, int j) { return E[i][j]->status; }
    virtual Te & edge(int i, int j) { return E[i][j]->data; }
    virtual int & weight(int i, int j) { return E[i][j]->weight; }
    virtual void insert(Te const & edge, int w, int i, int j) { 
        if (exists(i, j) || (i >= n) || (j >= n)) return;
        E[i][j] = new Edge<Te>(edge, w);
        e++; V[i].outDegree++; V[j].inDegree++;
    }
    virtual Te remove(int i, int j) { 
        Te eBack = edge(i, j); delete E[i][j]; E[i][j] = NULL;
        e--; V[i].outDegree--; V[j].inDegree--;
        return eBack;
    }

};



template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) {
    reset(); int clock = 0; int v = s;
    do
        if (status(v) == UNDISCOVERED) BFS(v, clock);
    while (s != (v = (++v % n)));
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int & clock) {
    Queue<int> q;
    status(v) = DISCOVERED; q.enqueue(v);
    while (!q.empty()) {
        int v = q.dequeue(); dTime(v) = ++clock;
        for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
            if (status(u) == UNDISCOVERED) {
                status(u) = DISCOVERED; q.enqueue(u);
                status(v, u) = TREE; parent(u) = v;
            } else
                status(v, u) = CROSS;
        status(v) = VISITED;
    }
}


template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s) {
    reset(); int clock = 0; int v = s;
    do 
        if (status(v) == UNDISCOVERED) DFS(v, clock);
    while (s != (v = (++v % n)));
}

// DFS recursive
// template <typename Tv, typename Te>
// void Graph<Tv, Te>::DFS(int v, int & clock) {
//     dTime(v) = ++clock; status(v) = DISCOVERED;
//     for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
//         switch (status(u)) {
//             case UNDISCOVERED:
//                 status(v, u) = TREE; parent(u) = v; DFS(u, clock); break;
//             case DISCOVERED:
//                 status(v, u) = BACKWARD; break;
//             default:
//                 status(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; break;
//         }
//     }
//     status(v) = VISITED; fTime(v) = ++clock;
// }


template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int & clock) {
    Stack<int> s; s.push()
    while (!s.empty()) {
        int v = s.top();
        dTime(v) = ++clock; status(v) = DISCOVERED;
        for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
            switch (status(u)) {
                case UNDISCOVERED:
                    status(v, u) = TREE; parent(u) = v; s.push(u); break;
                case DISCOVERED:
                    status(v, u) = BACKWARD; break;
                default:
                    status(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; break;
            }
        }
        if (s.top() == v) {
           s.pop();
           status(v) = VISITED; fTime(v) = ++clock;
        }
    }
}



template <typename Tv, typename Te>
Stack<Tv> * Graph<Tv, Te>::tSort(int s) {
    reset()l int clock = 0; int v = s;
    Stack<Tv> * s = new Stack<Tv>;
    do {
        if (status(u) == status(v))
            if (!TSort(v, clock, s)) {
                while (!s->empty()) s->pop(); 
                break;
            }
    } while (s != (v = (++v % n)))l
    return s;
}

template <typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, int & clock, Stack<Tv> * s) {
    dTime(v) = ++clock; status(v) = DISCOVERED;
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
        switch (status(u)) {
            case UNDISCOVERED:
                parent(u) = v; status(v, u) = TREE;
                if (!TSort(u, clock, s)) return false;
                break;
            case DISCOVERED:
                status(v, u) = BACKWARD;
                return false;
            default:
                status(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED; fTime(v) = ++clock;
    s->push(vertex(v));
    return true;
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int s) {
    reset(); int clock = 0; int v = s; Stack<int> s;
    do
    {
        if (UNDISCOVERED == status(v)) {
            BCC(v, clock, s);
            s.pop();
        }
    } while (s != (v = (++v % n)));
    
}

#define hca(x) (fTime(x))
#define min(x, y) ((x) < (y) ? x : y)
template <typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int & clock, Stack<int> & s) {
    hca(v) = dTime(v) = ++clock; status(v) = DISCOVERED; s.push(v);
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
        switch (status(u)) {
            case UNDISCOVERED:
                parent(u) = v; status(v, u) = TREE; BCC(u, clock, s);
                if (hca(u) < dTime(v))
                    hca(v) = min(hca(v), hca(u))
                else {
                    while (v !+ s.pop());
                    s.push(v);
                }
                break;
            case DISCOVERED:
                status(v, u) = BACKWARD;
                if (u != parent(v)) hca(v) = min(hca(v), dTime(u));
                break;
            default:
                status(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
}
#undef hca
#undef min





template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdator) {
    reset(); int v = s;
    do
    {
        if (UNDISCOVERED == status(v))
            PFS(v, prioUpdator);
    } while (s != (v = (++v % n)));
}

template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdator) {
    priority(s) = 0; status(s) = VISITED; parent(s) = -1;
    while (1) {
        for (int w = firstNbr(s); -1 < w; w = nextNbr(s, w))
            prioUpdator(this, s, w);
        for (int shortest = INT_MAX, w = 0; w < n; w++)
            if (status(w) == UNDISCOVERED)
                if (shortest > priority(w))
                    { shortest = priority(w); s = w; }
        if (VISITED == status(v)) break;
        status(s) = VISITED; status(parent(s), s) = TREE;
    }
}




template <typename Tv, typename Te>
struct PrimPU {
    virtual void operator()(Graph<Tv, Te> * g, int uk, int v) {
        if (g->status(v) == UNDISCOVERED)
            if (g->priority(v) > g->weight(uk, v)) {
                g->priority(v) = g->weight(uk, v);
                g->parent(v) = uk;
            }
    }
};


template <typename Tv, typename Te>
struct DijkstraPU {
    virtual void operator()(Graph<Tv, Te> * g, int uk, int v) {
        if (g->status(v) == UNDISCOVERED) {
            if (g->priority(v) > g->priority(uk) + g->weight(uk, v)) {
                g->priority(v) = g->priority(uk) + g->weight(uk, v);
                g->parent(v) = uk;
            }
        }
    }
}


#ifdef TEST_GRAPH

int main(int argc, const char** argv) {
    
    return 0;
}

#endif


#endif // !1