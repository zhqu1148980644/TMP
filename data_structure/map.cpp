

#include "list.cpp"

#define QlistNodePosi(T) QuadlistNode<T> *

template <typename T>
struct QuadlistNode {
    T entry;
    QlistNodePosi(T) pred; QlistNodePosi(T) succ;
    QlistNodePosi(T) above; QlistNodePosi(T) below;
    QlistNodePosi(
        T e = T(), 
        QlistNodePosi(T) p = NULL, QlistNodePosi(T) s = NULL, 
        QlistNodePosi(T) a = NULL, QlistNodePosi(T) b = NULL, 
    ) : entry(e), pred(p), succ(s), above(a), below(b) {}
    QlistNodePosi(T) insertAsSuccAbove(T const & e, QlistNodePosi(T) b = NULL);
};


template <typename T>
class Quadlist {
    private:
        int _size;
        QlistNodePosi(T) header;
        QlistNodePosi(T) trailer;
    protected:
        void init();
        int clear();
    public:
        Quadlist() { init(); }
        ~Quadlist() { clear(); delete header; delete trailer; }

        Rank size() const { return _size; }
        bool empty() const { return _size <= 0; }
        QlistNodePosi(T) first() const { return header->succ; }
        QlistNodePosi(T) last() const { return trailer->pred; }
        QlistNodePosi(T) insertAfterAbove(
            T const & e, 
            QlistNodePosi(T) p, 
            QlistNodePosi(T) b=NULL
        );
        T remove(QlistNodePosi(T) p);
        bool valid(QlistNodePosi(T) p) { return p && (trailer != p) && (header != p); }
        void traverse(void (*) (T&));
        template <typename> void traverse(VST &);
};

template <typename T>
void Quadlist<T>::init() { 
    header = new QuadlistNode<T>;
    trailer = new QuadlistNode<T>;
    header->succ = trailer; header->pred = NULL;
    trailer->pred = header; trailer->succ = NULL;
    header->above = trailer->above = NULL;
    header->below = trailer->below = NULL;
    _size = 0;
}





template <typename K, typename V>
struct Dictionary {
    virtual int size() const = 0;
    virtual bool put(K, V) = 0;
    virtual V * get(K k) = 0;
    virtual bool remove(k k) = 0;
};


template <typename K, typename V>
class SkipList : public  Dictionary<K, V>, public List<Quadlist<Entry<K, V>> *> {
    protected:
        bool SkipList(
            ListNode<Quadlist<Entry<K, V>> *> * & qlist,
            QuadlistNode<Entry<K, V>> * & p,
            K & k
        );
    public:
        int size() const { return empty() ? 0 : last()->data->size(); }
        int level() { return List::size(); }
        bool put(K, V);
        V * get(K k);
        bool remove(K k);
};



template <typename K, typename V>
V * SkipList<K, V>::get(K k) {
    if (empty()) return NULL;
    ListNode<Quadlist<Entry<K, V>> *> * qlist = first();
    QuadlistNode<Entry<K, V>> * p = qlist->data->first();
    return skipSearch(qlist, p, k) ? &(p->entry.value) : NULL;
}


class Bitmap {

};

#define lazilyRemoved(x) (lazyRmoval->test(x))
#define markAsRemoved(x) (lazyRmoval->set(x))
#define clearRemoved(x) (lazyRmoval->clear(x))
template <typename K, typename V>
class Hashtable : public Dictionary<K, V> {
    private:
        Entry<K, V> ** ht;
        int M;
        int N;
        Bitmap * lazyRmoval;
    protected:
        int probe4Hit(const K & k);
        int probe4Free(const K & K);
        void rehash();
    public:
        Hashtable(int c = 5);
        ~Hashtable();
        int size() const { return N; }
        bool put(K, V);
        V * get(K);
        bool remove(K);
};

template <typename K, typename V>
Hashtable<K, V>::Hashtable(int c) {
    M = primeNLT(c, 1048576, 'prime.txt');
    N = 0;
    ht = new Entry<K, V>*[M];
    memset(ht, 0, sizeof(Entry<K, V>*) * M);
    lazyRmoval = new Bitmap(M);
}

int primeNLT(int c, int n, char * file) {
    Bitmap B(file, n);
    while (c < n) {
        if (B.test(c)) c++;
        else return c;
    }
    return c;
}

template <typename K, typename V>
Hashtable<K, V>::~Hashtable() {
    for (int i = 0; i < M; i++)
        if (ht[i]) release(ht[i]);
    release(ht);
    release(lazyRmoval);
}

template <typename K, typename V>
V * Hashtable<K, V>::get(K k) {
    int r = probe4Hit(k); return ht[r] ? &(ht[r]->value) : NULL;
}

template <typename K, typename V>
int Hashtable<K, V>::probe4Hit(const K & k) {
    int r = hashCode(k) % M;
    while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazilyRemoved(r)))
        r = (r + 1) % M;
    return r;
}

template <typename K, typename V>
bool Hashtable<K, V>::remove(K k) {
    release(ht[r]); ht[r] = NULL; markAsRemoved(r); N--; return true;
}

template <typename K, typename V>
bool Hashtable<K, V>::put(K k, V v) {
    if (ht[probe4Hit(k)]) return false;
    int r = probe4Free(k);
    ht[r] = new Entry<K, V>(k, v); ++N;
    if (N * 2 > M) rehash();
    return true;
}


template <typename K, typename V>
int Hashtable<K, V>::probe4Free(const K & k) {
    int r = hashCode(k) % M;
    while (ht[r]) r = (r + 1) % M;
    clearRemoved(r);
    return r;
}

template <typename K, typename V>
void Hashtable<K, V>::rehash() {
    int old_capacity = M;
    Entry<K, V> ** old_ht = ht;
    M = primeNLT(2 * M, 1048576, 'prime.txt');
    N = 0; ht = new Entry<K, V> * [M]; memset(ht, 0, sizeof(Entry<K, V>*) * M);
    release(lazyRmoval);
    lazyRmoval = new Bitmap(M);
    for (int i = 0; i < old_capacity; i++)
        if (old_ht[i])
            put(old_ht[i]->key, old_ht[i]->value);
    release(old_ht);
}











