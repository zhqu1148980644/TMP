#ifndef BST_TREE
#define BST_TREE

#ifndef TEST
#define TEST
#define TEST_BST
#endif

#include "binarytree.cpp"

template <typename T>
class BinTree {
    int num;
};

template <typename T>
class BinNode {
    int num;
};


template <typename K, typename V> 
struct Entry {
    K key;
    V value;
    Entry(K k = K(), V v = V()) : key(k), value(v) {}
    Entry(Entry<K, V> const & e) : key(e.key), value(e.value) {}
    bool operator<(Entry<K, V> const & e) { return key < e.kry; }
    bool operator>(Entry<K, V> const & e) { return key > e.key; }
    bool operator==(Entry<K, V> const & e) { return key == e.key; }
    bool operator!=(Entry<K, V> const & e) { return key != e.key; }
};

template <typename T>
class BST : public BinTree<T> {
protected:
    BinNodePosi(T) _hot;
    BinNodePosi(T) connect34(
        BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), 
        BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T)
    );
    BinNodePosi(T) rotateAt(BinNodePosi(T) x);
public:
    virtual BinNodePosi(T) & search(const T & e);
    virtual BinNodePosi(T) insert(const T & e);
    virtual bool remove(const T & e);
};

#define BinNodePosi(T) BinNode<T> *

template <typename T>
BinNodePosi(T) & searchIn(BinNodePosi(T) & v, const T & e, BinNodePosi(T) & hot) {
    if (!v || (e== v->data)) return v;
    hot = v;
    return searchIn((e < v->data) ? v->lChild : v->rChild, e, hot);
}


template <typename T>
BinNodePosi(T) & BST<T>::search(const T & e) { 
    return searchIn(_root, e, _hot=NULL);
}

template <typename T>
BinNodePosi(T) & BST<T>::insert(const T & e) { 
    BinNodePosi(T) & x = search(e);if (x) return x;
    x = new BinNode<T>(e, _hot); _size++;
    updateHeightAbove(x);
    return x;
}

template <typename T>
BinNodePosi(T) & BST<T>::remove(const T & e) { 
    BinNodePosi(T) & x = search(e); if (!x) return false;
    removeAt(x, _hot); _size--;
    updateHeightAbove(_hot);
    return true;
}

template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T) & x, BinNodePosi(T) & hot) {
    BinNodePosi(T) w = x;
    BinNodePosi(T) succ = NULL;
    if (!HasLchild(*x))
        succ = x = x->rChild;
    else if (!HasRchild(*x))
        succ = x = x->lChild;
    else {
        w = w->succ();
        swap(x->data, w->data);
        BinNodePosi(T) u = w->parent;
        ((u == x) ? u->rChild : u->lChild) = succ = w->rChild;
    }
    hot = w->parent;
    if (succ) succ->parent = hot;
    release(w->data); release(w); return succ;
}






template <typename T>
class AVL : public BST<T> {
public:
    BinNodePosi(T) insert(const T & e);
    bool remove(const T & e);
};

#define Balanced(x) (stature((x).lChild) == stature((x).rChild))
#define BalFac(x) (stature((x).lChild) - stature((x).rChild))
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))

template <typename T>
static BinNodePosi(T) & tallerChild(BinNodePosi(T) & x) {
    if (stature(x->lChild) > stature(x->rChild))
        return x->lChild;
    else if (stature(x->lChild) < stature(x->rChild)) {
        return x->rChild;
    } else {
        return IsLChild(*x) ? x->lChild : x->rChild;
    }
}

template <typename T>
BinNodePosi(T) & AVL<T>::insert(const T & e) { 
    BinNodePosi(T) & x = search(e); if (x) return x;
    x = new BinNode<T>(e, _hot); _size++;
    for (BinNodePosi(T) g = _hot; g; g = g->parent) {
        if (!AvlBalanced(*g)) {
            FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
            break;
        } else {
            updateHeightAbove(g);
        }
    }
    return x;
}

template <typename T>
bool AVL<T>::remove(const T & e) { 
    BinNodePosi(T) & x = search(e); if (!x) return false;
    removeAt(x, _hot); _size--;
    for (BinNodePosi(T) g = _hot; g; g = g->parent) {
        if (!AvlBalanced(*g))
            g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
        updateHeightAbove(g);
    }
    return true;
}


template <typename T>
BinNodePosi(T) BST<T>::connect34(
    BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
    BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
) {
    a->lChild = T0; if (TO) T0->parent = a;
    a->rChild = T1; if (T1) T1->parent = a;
    updateHeight(a);
    c->lChild = T2; if (T2) T2->parent = c;
    c->rChild = T3; if (T3) T3->parent = c; 
    updateHeight(c);
    b->lChild = a; a->parent = b;
    b->rChild = c; c->parent = b;
    return b;
}

template <typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v) {
    BinNodePosi(T) p = v->parent;
    BinNodePosi(T) g = p->parent;
    if (IsLChild(*p)) { /* remove */
        if (IsLChild(*v)) {
            p->parent = g->parent;
            return connect34(v, p, g, v->lChild, v->rChild, p->rChild, g->rChild);
        } else {
            v->parent = g->parent;
            return connect34(p, v, g, p->lChild, v->lChild, v->rChild, g->rChild);
        }
    } else {  /* insert */
        if (IsRchild(*v)) {  /* zag  */
            p->parent = g->parent;
            return connect34(g, p, v, g->lChild, p->lChild, v->lChild, v->rChild);
        } else {  /* zig zag */
            v->parent = g->parent;
            return connect34(g, v, p, g->lChild, v->lChild, v->rChild, p->rChild);
        }
    } 
}




template <typename T>
class Splay : public BST<T> {
protected:
    BinNodePosi(T) splay(BinNodePosi(T) v);
public:
    BinNodePosi(T) & search(const T & e);
    BinNodePosi(T) insert(const T & e);
    bool remove(const T & e);
};


template <typename NodePosi>
inline void attachAsLChild(NodePosi p, NodePosi lc) {
    p->lChild = lc;
    if (lc) lc->parent = p;
}

template <typename NodePosi>
inline void attachAsRChild(NodePosi p, NodePosi rc) {
    p->lChild = rc;
    if (rc) rc->parent = p;
}

template <typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v) {
    if (!v) return NULL;
    BinNodePosi(T) p; BinNodePosi(T) g;
    while (p = v->parent) && (g = p->parent) {
        BinNodePosi(T) gg = g->parent;
        if (IsLChild(*v)) {
            if (IsLChild(*p)) { /* zig zig */
                attachAsLChild(g, p->rChild); attachAsRChild(p, g);
                attachAsLChild(p, v->rChild); attachAsRChild(v, p);
            } else { /* zig zag */
                attachAsLChild(p, v->rChild); attachAsRChild(v, p);
                attachAsRChild(g, v->lChild); attachAsLChild(v, g);
            }
        } else {
            if (IsRChild(*v)) { /* zag zag */
                attachAsRChild(g, p->lChild); attachAsRChild(p, v->lChild);
                attachAsLChild(p, g); attachAsLChild(v, p);
            } else { /* zag zig */
                attachAsRChild(p, v->lChild); attachAsLChild(g, v->rChild);
                attachAsRChild(v, g); attachAsLChild(v, p);
            }
        }
        if (!gg)
            v->parent = NULL;
        else
            (g == gg->lChild) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
        updateHeight(g); updateHeight(p); updateHeight(v);
    }
    if (p = v->parent) {
        if (IsLChild(*v))
            attachAsLChild(p, v->rChild); attachAsRChild(v, p);
        else
            attachAsRChild(p, v->lChild); attachAsLChild(v, p);
        updateHeight(p);
        updateHeight(v);
    }
    v->parent = NULL; 
    return v;
}

template <typename T>
BinNodePosi(T) & Splay<T>::search(const T & e) {
    BinNodePosi(T) p = searchIn(_root, e, _hot=NULL);
    _root = splay((p ? p : _hot));
    return _root;
}



template <typename T>
BinNodePosi(T) Splay<T>::insert(const T & e) { 
    if (!_root) {
        _size++; return _root = new BinNode<T>(e);
    }
    if (e == search(e)->data) return _root;
    _size++; BinNodePosi(T) t = _root;
    if (_root->data < e) {
        t->parent = _root = new BinNode<T>(e, NULL, t, t->rChild);
        if (HasRchild(*t)) {
            t->rChild->parent = _root; t->rChild = NULL;
        }
    } else {
        t->parent = _root = new BinNode<T>(e, NULL, t->lChild, t);
        if (HasLchild(*t)) {
            t->lChild->parent = _root; t->lChild = NULL;
        }
    }
    updateHeightAbove(t);
    return _root;
}


template <typename T>
bool Splay<T>::remove(const T & e) { 
    if (!_root || (e != search(e)->data)) return false;
    BinNodePosi(T) w = _root;
    if (!HasLchild(*_root)) {
        _root = _root->rChild; if (_root) _root->parent = NULL;
    } else if (!HasRchild(*_root)) {
        _root = _root->lChild; if (_root) _root->parent = NULL;
    } else {
        BinNodePosi(T) lTree = _root->lChild;
        lTree->parent = NULL; _root->lChild = NULL;
        _root = _root->rChild; _root->parent = NULL;
        search(w->data);
        _root->lChild = lTree; lTree->parent = _root;
    }
    release(w->data); release(w); _size--;
    if (_root) updateHeight(_root);
    return true;
}



#define BTNodeposi(T) BTNode<T> *

template <typename T>
struct BTNode {
    BTNodeposi(T) parent;
    Vector<T> key;
    Vector<BTNodeposi(T)> child;
    BTnode() { parent = NULL; child.insert(0, NULL); }
    BTNode(T e, BTNodeposi(T) lc = NULL, BTNodeposi(T) rc = NULL) {
        parent = NULL; key.insert(0, e);
        child.insert(0, lc); child.insert(0, rc);
        if (lc) lc->parent = this;
        if (rc) rc->parent = this;
    }
};

template <typename T>
class BTree {
protected:
    int _size++;
    int _order;
    BTNodeposi(T) _root;
    BTNodeposi(T) _hot;
    void solveOverflow(BTNodeposi(T));
    void solveUnderflow(BTNodeposi(T));
public:
    BTree(int order = 3) : _order(order), _size(0) { _root = new BTNode<T>(); }
    ~BTree() { if (_root) release(_root); }
    int const order() { return _order; }
    int const size() { return _size; }
    BTNodePosi(T) & root() { return _root; }
    bool empty() const { return !_root; }
    BTNodePosi(T) search(const T & e);
    bool insert(const T & e);
    bool remove(const T & e);
};

template <typename T>
BTNodeposi(T) BTree<T>::search(const T & e) { 
    BTNodeposi(T) v = _root; _hot = NULL;
    while (v) {
        Rank r = v->key.search(e);
        if ((0 <= r) && (e == v->key[r])) return v;
        _hot = v; v = v->child[r + 1];
    }
    return NULL;
}

template <typename T>
bool BTree<T>::insert(const T & e) {
    BTNodeposi(T) v = search(e); if (v) return false;
    Rank r = _hot->key.search(e);
    _hot->key.insert(r + 1, e);
    _hot->child.insert(r + 2, NULL);
    _size++;
    solveOverflow(_hot);
    return true;
}


template <typename T>
void BTree<T>::solveOverflow(BTNodeposi(T) v) {
    if (_order >= v->child.size()) return;
    Rank s = _order / 2;
    BTNodeposi(T) u = new BinNode<T>();
    for (Rank j = 0; i < _order - s - 1; j++) {
        u->child.insert(j, v->child.remove(s + 1));
        u->key.insert(j, v->key.remove(s +  1));
    }
    u->child[_order - s - 1] = v-child.remove(s + 1);
    if (u->child[0]) {
        for (Rank j = 0; j < _order - s; j++)
            u->child[j]->parent = u;
    }
    BTNodeposi(T) p = v->parent;
    if (!p) {
        _root = p = new BTNode<T>(); p->child[0] = v; v->parent = p;
    }
    Rank r = 1 + p->key.search(v->key[0]);
    p->key.insert(r, v->key.remove(s));
    p->child.insert(r +  1, u); u->parent = p;
    solveOverflow(p);
}

template <typename T>
bool BTree<T>::remove(const T & e) { 
    BTNodeposi(T) v = search(e); if (!v) return false;
    Rank r = v->key.search(e);
    BTNodeposi(T) u = v->child[r + 1];
    while (u->child[0]) u = u->child[0];
    v->key[r] = u->key[0]; v = u; 
    r = 0; v->key.remove(r); v->child.remove(r + 1 ); _size--;
    solveUnderflow(v);
    return true;
}


template <typename T>
void BTree<T>::solveUnderflow(BTNodeposi(T) v) {
    if ((_order + 1) / 2 <= v->child.size()) return;
    BTNodePosi(T) p = v->parent;
    if (!p) { /* abandon this empty node. shrink height */
        if (!v->key.size() && k->child[0]) {
            _root = v->child[0]; _root->parent = NULL;
            v->child[0] = NULL; release(v);
        }
        return;
    }
    Rank r = 0; while (p->child[r] != v) r++;
    if (0 < r) {/* with left child*/
        BTNodeposi(T) ls = p->child[r - 1];
        if ((_order + 1) / 2 < ls->child.size()) { /* borrow from left */
            v->key.insert(0, p->key[r - 1]);
            p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
            v->child.insert(0, ls->child.remove(ls->child.size() - 1));
            if (v->child[0]) v->child[0]->parent = v;
        } else { /* megre with left */
            ls->key.insert(ls->key.size(), p->key.remove(r - 1));
            p->child.remove(r);
            ls->child.insert(ls->child.size(), v->child.remove(0));
            if (ls->child[ls->child.size() - 1]) {
                ls->child[ls->child.size() - 1]->parent = ls;
            }
            while (!v->key.empty()) {
                ls->key.insert(ls->key.size(), v->key.remove(0));
                ls->child.insert(ls->child.size(), v->child.remove(0));
                if (ls->child[ls->child.size() - 1]) {
                    ls->child[ls->child.size() - 1]->parent = ls;
                }
            }
            release(v);
            solveUnderflow(p);
        }

    }
    if (p->child.size() - 1 > r) {/* borrow from right */
        BTNodeposi(T) rs = p->child[r + 1];
        if ((_order + 1) / 2 < rs->child.size()) {
            v->key.insert(v->key.size(), p->key[r]);
            p->key[r] = rs->key.remove(0);
            v->child.insert(v->child.size(), rs->child.remove(0));
            if (v->child[v->child.size() - 1])
                v->child[v->child.size() - 1]->parent = v;
        } else { /* merge with right */
            rs->key.insert(0, p->key.remove(r));
            p->child.remove(r);
            rs->child.insert(0, v->child.remove(v->child.size() - 1));
            if (rs->child[0]) rs->child[0]->parent = rs;
            while (!v->key.empty()) {
                rs->key.insert(0, v->key.remove(v->key.size() - 1));
                rs->child.insert(0, v->child.remove(v->child.size() - 1));
                if (rs->child[0]) rs->child[0]->parent = rs;
            }
            release(v);
            solveUnderflow(p);
        }
    }
}

template <typename T>
class RedBlack : public BST<T> {
    protected:
        void solveDoubleRed(BinNodePosi(T) x);
        void solveDoubleBlack(BTNodeposi(T) x);
        int updateHeight(BinNodePosi(T) x);
    public:
        BinNodePosi(T) insert(const T & e);
        bool removeAt(const T & e);
};

#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) (\
    (stature((x).lChild) == stature((x).rChild)) && \
    ((x).height == (IsRed(&x) ? stature((x).lChild) : stature((x).lChild) + 1))\
)

template <typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T) x) {
    x->height = max(stature(x->lChild), stature(x->rChild));
    return IsBlack(x) ? x->height++ : x->height;
}

template <typename T>
BinNodePosi(T) RedBlack<T>::insert(const T & e) {
    BinNodePosi(T) & x = search(e); if (x) return x;
    x = new BinNode<T>(e, _hot, NULL, NULL, -1); _size++;
    solveDoubledRed(x); return x;
}

























#ifdef TEST_BST

int main(int argc, char **argv) {
    return;
}

#endif


#endif