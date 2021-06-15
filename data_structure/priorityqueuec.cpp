template <typename T>
struct PQ {
    virtual void insert(T) = 0;
    virtual T getMax() = 0;
    virtual T delMax() = 0;
};

#define lt(x, y) ((x) < (y))
#define InHeap(n, i) (((-1) < (i)) && ((1) < (n)))
#define Parent(i) ((i - 1) >> 1)
#define LastInternal(n) Parent(n - 1)
#define LChild(i) (1 + ((1) << 1))
#define RChild(i) (2 + ((1) << 1))
#define ParentValid(i) (0 < i)
#define LChildValid(n, i) InHeap(n, LChild(i))
#define RChildValid(n, i) InHeap(n, RChild(i))
#define Bigger(PQ, i, j) (lt(PQ[i], PQ[j]) ? j : i)


template <typename T>
class PQ_ComplHeap : public PQ<T>, public Vector<T> {
    protected:
        Rank percolateDown(Rank n, Rank i);
        Rank percolateUp(Rank i);
        void heapify(Rank n);
    public:
        PQ_ComplHeap() {}
        PQ_ComplHeap(T * A, Rank n) { copyFrom(A, 0, n); heapify(n); }
        void insert(T);
        T getMax();
        T delMax();
};

template <typename T>
T PQ_ComplHeap<T>::getMax() {
    return _elem[0];
}

template <typename T>
void PQ_ComplHeap<T>::insert(T e) {
    Vector<T>::insert(e);
    percolateUp(_size - 1);
}

template <typename T>
Rank PQ_ComplHeap<T>::percolateUp(Rank i) {
    T backup = _elem[i];
    while (ParentValid(i)) {
        Rank j = Parent(i);
        if (lt(backup, _elem[j])) break;
        _elem[i] = _elem[j]; i = j;
    }
    _elem[i] = backup;
    return i;
}


typedef int Rank;

template <typename T>
T PQ_ComplHeap<T>::delMax() {
    T maxElem = _elem[0]; _elem[0] = _elem[--_size];
    percolateDown(_size, 0);
    return maxElem;
}

template <typename T>
Rank ProperParent(T * pq, Rank n, Rank i) {
    if (RChildValid(n, i)) {
        return Bigger(pq, Bigger(pq, i, LChild(i)), RChild(i));
    } else {
        return Bigger(pq, i, LChild(i)));
    }
}

template <typename T>
Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i) {
    Rank j;
    while (i != (j = ProperParent(_elem, n, i)))
        swap(_elem[i], _elem[j]); i = j;
    return i;
}


template <typename T>
void PQ_ComplHeap<T>::heapify(Rank n) {
    for (int i = LastInternal(n); InHeap(n, i); i--)
        percolateDown(n, i);
}


template <typename T>
void Vector<T>::heapsort(Rank lo, Rank hi) {
    PQ_ComplHeap<T> H(_elem + lo, hi - lo);
    while (!H.empty())
        _elem[--hi] = H.delMax();
}

