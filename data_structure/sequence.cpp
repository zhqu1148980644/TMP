#include <cstring>
using namespace std;

int bf_search(char * P, char * T) {
    int m = strlen(T);
    int n = strlen(P);
    int i = 0, j = 0;
    while ((i != m) && (j != n)) {
        if (T[i] == P[j]) {
            ++i; ++j;
        } else {
            i -= j - 1;
            j = 0;
        }
    }
    return i - j;
}



int * build_next(char * P) {
    int n = strlen(P);
    int * N = new int[n];
    int j = 0, t = N[0] = -1;
    while (j != n - 1) {
        if ((t < 0) || (P[j] == P[t])) {
            ++j; ++t;
            N[j] = (P[j] != P[t]) ? t : N[t];
        } else
            t = N[t];
    }
    return N;
}

int kmp(char * P, char * T) {
    int m = strlen(T);
    int n = strlen(P);
    int * N = build_next(P);
    int i = 0, j = 0;
    while ((i != m) && (j != n)) {
        if ((j < 0) || (T[i] == P[j])) {
            ++i; ++j;
        } else {
            j = N[i];
        }
    }
    delete [] N;
    return i - j;
}


#define __max(x, y) ((x) > (y) ? (x) : (y))

int * buildBC(char * P) {

}

int * buildGS(char * P) {

}

int bm(char * P, char * T) {
    int * bc = buildBC(P); int * gs = buildGS(P);
    size_t i = 0;
    while (strlen(T) >= i + strlen(P)) {
        int j = strlen(P) - 1;
        while (P[j] == T[i + j])
            if (0 > --j) break;
        if (0 > j) break;
        else i += __max(gs[j], j - bc[T[i + j]]);
    }
    delete [] gs; delete [] bc;
    return i;
}


#define M 97
#define R 10
#define DIGIT(S, i) ((S)[i] - '0')
typedef __int64 HashCode;

bool check1by1(char * P, char * T, size_t i);
HashCode prepareDm(size_t m);
void updateHash(HashCode & hashT, char * T, size_t m, size_t k, HashCode Dm);

int match(char * P, char * T) {
    size_t m = strlen(P), n = strlen(T);
    HashCode Dm = prepareDm(m), hashP = 0, hashT = 0;
    for (size_t i = 0; i < m; i++) {
        hashP = (hashP * R + DIGIT(P, i)) % M;
        hashT = (hashT * R + DIGIT(T, i)) % M;
    }
    for (size_t k = 0; ;) {
        if (hashT == hashP)
            if (check1by1(P, T, k)) return k;
        if (++k > n - m) return k;
        else updateHash(hashT, T, m, k, Dm);
    }
}

template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) {
    if (hi - lo < 2) return;
    Rank mi = partition(lo, hi - 1);
    quickSort(lo, mi);
    quickSort(mi + 1, hi);
}


template <typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {
    swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);
    T pivot = _elem[lo];
    while (lo < hi) {
        while (lo < hi)
            if (pivot < _elem[hi]) hi--;
            else {
                _elem[lo++] = _elem[hi];
                break;
            }
        while (lo < hi)
            if (pivot > _elem[lo]) lo++;
            else {
                _elem[hi--] = _elem[lo];
                break;
            }
    }
    _elem[lo] = pivot;
    return lo;
}



template <typename T>
T MedianCandidate(Vector<T> A) {
    int num = 0;
    T med;
    for (size_t i = 0; i < A.size(); ++i) {
        if (num == 0) {
            med = A[i]; c = 1;
        } else {
            (A[i] == med) ? num++ : num--;
        }
    }
    return med;
}

template <typename T>
bool checkMedian(Vector<T> A, T med) {
    int num = 0;
    for (size_t i = 0; i < A.size(); ++i)
        if (A[i] == med) ++num;
    return 2 * num  > A.size();
}

template <typename T>
T trivialMedian(Vector<T> & S1, int lo1, int n1, Vector<T> & S2, int lo2, int n2) {
    int hi1 = lo1 + n1;
    int hi2 = lo2 + n2;
    Vector<T> S;
    while ((lo < hi1) && (lo2 < hi2)) {
        while ((lo1 < hi1) && (S1[lo1] < S2[lo2])) S.insert(S1[lo1++]);
        while ((lo1 < hi1) && (S1[lo2] < S2[lo1])) S.insert(S2[lo2++]);
    }
    while (lo1 < hi1) S.insert(S1[lo1++]);
    while (lo2 < hi2) S.insert(S2[lo2++]);
    return S[(n1 + n2) / 2];
}

template <typename T>
T median(Vector<T> & S1, int lo1, Vector<T> & S2, int lo2, int n) {
    if (n < 3) return trivialMedian(S1, lo1, n, S2, lo2, n);
    int mi1 = lo1 + n / 2, mi2 = lo2 + (n - 1) / 2;
    if (S1[mi1] < S2[mi2])
        return median(S1, mi1, S2, lo2, (n - 1) / 2);
    else if (S1[mi1] > S2[mi2])
        return median(S2, mi2, S1, lo1, (n - 1) / 2);
    if (S1[mi1] == S2[mi2]) return S1[mi1];
}

template <typename T>
T median(Vector<T> &  S1, int lo1, int n1, Vector<t>& S2, int lo2, int n2) {
    if (n1 > n2) return median(S2, lo2, lo1, S1, lo1, n1);
    if (n2 < 6)
        return trivialMedian(S1, lo1, n1, S2, lo2, n2);
    int mi1 =lo + n1 / 2;
    int mi2a = lo + (n2 - 1) / 2;
    int mi2b = lo2 + n2 - 1 - n1 / 2;
    if (S1[mi1] > S2[mi2b])
        return median(S1, lo1, n1 / 2 + 1, S2, mi2a, n2 - (n1 - 1) / 2);
    else if (S1[mi1] < S2[mi2b])
        return median(S1, m1, (n1 + 1) / 2, S2, lo2, n2 - n1 / 2);
    return median(S1, lo1, n1, S2, mi2a, n2 - (n1 - 1) / 2 * 2);
}
