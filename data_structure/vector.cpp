#ifndef VECTOR
#define VECTOR


#ifndef TEST
#define TEST
#define TEST_VEC
#endif


#include <iostream>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <initializer_list>
#include <string>

using std::cout;
using std::endl;
using std::initializer_list;
using std::for_each;
using std::string;



#define DEFAULT_CAPACITY 3

template <typename T>
int binary_search(T * elem, T const & e, int lo, int hi);

template <typename T>
class Vector
{
    public:
        typedef T value_type;
        typedef size_t size_type;

        /*********************************************************iterator***************************************************/
        struct iterator
        {
            iterator() : p(nullptr)               {}
            iterator(T * ptr) : p(ptr)            {}
            iterator operator++(int)              { return p++; }
            iterator & operator++()               { ++p; return *this; }
            iterator operator--(int)              { return p--; }
            iterator & operator--()               { --p; return *this; }
            bool operator==(iterator const & i2)  { return p == i2.p; }
            bool operator!=(iterator const & i2)  { return !operator==(i2); }
            template <typename X>
            iterator & operator=(X && e)          { *p = std::forward<X>(e); }
            T & operator*()                       { return *p; }
            T operator*() const                   { return *p; }
            private:
                T * p;
        };
        iterator begin() { return iterator(_elem); }
        iterator end() { return iterator(_elem + _size); }
        /*********************************************************************************************************************/

        Vector(size_t c = DEFAULT_CAPACITY, size_t s = 0, T v = T());
        Vector(T const * A, size_t lo, size_t hi)                   { copyfrom(A, lo, hi); } 
        Vector(T const * A, size_t n)                               { copyfrom(A, 0, n); }
        Vector(Vector<T> const & v, size_t lo, size_t hi)           { copyfrom(v._elem, lo, hi); }
        Vector(initializer_list<T> il)                              { copyfrom(il.begin(), 0, il.size()); }
        Vector(Vector<T> const & v)                                 { copyfrom(v._elem, 0, v._size); }
        Vector(Vector<T> && v); 
        Vector<T> & operator=(Vector<T> const & v);
        Vector<T> & operator=(Vector<T> && v);
        ~Vector()                                                   {if (_elem) delete [] _elem;}

        T & operator[](size_t r)                                    { return _elem[r]; }
        T operator[](size_t r) const                                { return _elem[r]; }
        size_t size() const                                         { return _size; }
        size_t & size()                                             { return _size; }
        bool empty() const                                          { return !_size; }
        size_t capacity()                                           { return _capacity; }
        T & front()                                                 { return _elem[0]; }
        T & back()                                                  { return _elem[_size - 1]; } 
        T const & front() const                                     { return _elem[0]; }
        T const & back() const                                      { return _elem[_size - 1]; }
        T pop_back()                                                { return remove(_size - 1); }
        T pop_front()                                               { return remove(0); }
        template <typename X>
        void push_back(X && e)                                      { insert(_size, std::forward<X>(e)); }
        template <typename X>
        void push_front(X && e)                                     { insert(0, std::forward<X>(e)); }
        
        void move_backward(size_t lo, size_t hi, size_t step = 1);
        void move_forward(size_t lo, size_t hi, size_t step = 1);
        T remove(size_t r);
        size_t remove(size_t lo, size_t hi);
        template <typename X>
        size_t insert(X && e)                                       {return insert(_size, std::forward<X>(e));}
        template <typename X>
        size_t insert(size_t r, X && e);

        int find(T const & e) const                                 {return find(e, 0, _size);}
        int find(T const & e, int lo, int hi) const;
        int search(T const & e) const                               {return 0 >= _size ? -1 : search(e, 0, _size);}
        int search(T const & e, int lo, int hi) const;
        void traverse(void (*)(T &));
        template <typename VST>
        void traverse(VST &);

        size_t max(size_t lo, size_t hi);
        size_t disordered() const;
        void sort(size_t lo, size_t hi);
        void sort()                                                 {sort(0, _size);}
        void unsort()                                               {unsort(0, _size);}
        void unsort(size_t lo, size_t hi);
        size_t deduplicate();
        size_t uniquity();

        void resize(size_t n, T const & e = T());

    protected:
        void copyfrom(T const * A, size_t lo, size_t hi);
        size_t bubble(size_t lo, size_t hi);    
        void bubble_sort(size_t lo, size_t hi);
        size_t select_max(size_t lo, size_t hi);
        void selection_sort(size_t lo, size_t hi);
        void merge(size_t lo, size_t mi, size_t hi);
        void merge_sort(size_t lo, size_t hi);
        void insertion_sort(size_t lo, size_t hi);

        void expand(size_t n = 0);
        void shrink();

    private:
        size_t _size;
        size_t _capacity;
        T * _elem;
};


template <typename T>
inline Vector<T>::Vector(size_t c, size_t s, T v) : _capacity(c) 
{ 
    _elem = new T[_capacity];
    for (_size = 0; _size < s; _elem[_size++] = v);
}

template <typename T>
void Vector<T>::copyfrom(T const * A, size_t lo, size_t hi)
{
    _size = 0;
    _elem = new T[_capacity = 2 * (hi - lo)];
    while (lo < hi)
        _elem[_size++] = A[lo++];       
}


template <typename T>
inline Vector<T>::Vector(Vector<T> && v) : _size(v._size), _capacity(v._capacity), _elem(v._elem)
{
    v._size = v._capacity = 0;
    v._elem = nullptr;
}

template <typename T>
inline Vector<T> & Vector<T>::operator=(Vector<T> const & v)
{
    if (_elem)
        delete [] _elem;
    copyfrom(v._elem, 0, v._size);
    return *this;
}

template <typename T>
inline Vector<T> & Vector<T>::operator=(Vector<T> && v)
{
    if (_elem) delete [] _elem;
    _size = v._size;
    _capacity = v._capacity;
    _elem = v._elem;
    v._size = v._capacity = 0;
    v._elem = nullptr;
    return *this;
}


/********************************************************dynamic size*************************************************/
template <typename T>
void Vector<T>::expand(size_t n)
{
    if (n > _capacity)
       _capacity = n;
    else
    {    
        if (_size < _capacity)
            return;
        if (_capacity < DEFAULT_CAPACITY)
            _capacity = DEFAULT_CAPACITY;
    }
    T * old = _elem;
    _elem = new T[_capacity <<= 1];
    for (size_t i = 0; i < _size; ++i)
        _elem[i] = std::move(old[i]);
    delete [] old;
}

template <typename T>
void Vector<T>::shrink()
{
    if (_capacity < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity) return;
    T * old = _elem;
    _elem = new T[_capacity >>= 1];
    for (size_t i = 0; i < _size; ++ i)
        _elem[i] = std::move(old[i]);
    delete [] old;
}

template <typename T>
void Vector<T>::resize(size_t n, T const & e)
{
    if (n < _size)
    {
        T * old = _elem;
        _elem = new T[n]; _size = 0; _capacity = n;
        while (_size < n)
        {
            _elem[_size] = old[_size];
            ++_size;
        }
    }
    else if (n > _size)
    {
        expand(n);
        while (n > _size)
            _elem[_size++] = e;
    }
    else
        return;    
}

/***********************************move  remove  insert****************************************************************/
template <typename T>//  move element [lo, hi) backforward x step
void Vector<T>::move_backward(size_t lo, size_t hi, size_t step)
{

    size_t end = lo;
    lo = lo - step;
    while (end < hi)
    {
        _elem[lo++] = _elem[end++];
    }
}

template <typename T>// move element [lo, hi) forward x step
void Vector<T>::move_forward(size_t lo, size_t hi, size_t step)
{
    size_t stop = lo + step - 1;
    for (size_t end = hi + step - 1; end != stop; --end)
        _elem[end] = _elem[end - step];
}

template <typename T>
template <typename X>
inline size_t Vector<T>::insert(size_t r, X && e)
{
    ++_size;
    expand();
    move_forward(r, _size, 1);
    _elem[r] = std::forward<X>(e); 
    return r;
}

template <typename T>
size_t Vector<T>::remove(size_t lo, size_t hi)
{
    if (lo == hi)
        return 0;
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

template <typename T>
inline T Vector<T>::remove(size_t r)
{
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}


template <typename T>
void Vector<T>::traverse(void (*visit)(T &))
{
    std::for_each(_elem, _elem + _size, [&visit](T & e) { visit(e); });
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST & visit)
{
    std::for_each(_elem, _elem + _size, [&visit](T & e) { visit(e); });
}

/*
tempalte <typename T>
int Vector<T>::uniquity()            // version one . slow     
{
    size_t oldsize = _size;
    size_t i = 0;
    while ( i < _size - 1)
        (_elem[i] == _elem[i + 1]) ? remove(i + 1) : ++i;
    return oldsize - _size;
}
*/

template <typename T>
size_t Vector<T>::deduplicate()
{
    size_t oldsize = _size;
    size_t i = 1;
    while (i < _size)
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    return oldsize - _size;
}

template <typename T>
size_t Vector<T>::uniquity()          // version two fast
{
    size_t oldsize = _size;
    size_t i = 0;
    size_t new_i = 0; 
    while ( ++new_i < _size)
    {
        if (_elem[i] != _elem[new_i])
            _elem[i++] = _elem[new_i];
    }
    _size = ++i;
    return new_i - i;
}

template <typename T>
size_t Vector<T>::max(size_t lo, size_t hi)
{
    if (disordered())
    {
        size_t max = 0;
        while(++lo < hi)
            if (_elem[lo] > _elem[max]) max = lo;
        return max; 
    }
    else
        return _size - 1;
}

template <typename T>
int Vector<T>::find(T const & e, int lo, int hi) const
{
    while ((lo < hi--) && (e != _elem[hi]));
    return hi;
}

template <typename T>
int Vector<T>::search(T const & e, int lo, int hi) const
{
    return binary_search(_elem, e, lo, hi);
}

/****************************************************binary search and fib search*****************************************************/
// binary_search2 and binaery_search2 will not return when mid = value;
// binary_search2 will shrink to hi - lo == 1;
// binary_search3 will shrink to hi == lo;
// best search length O(log2(n)).  average search length O(log2(n))
// binary_search2 is a little slower than binary_search3
// result may be -1. but it's ok since insert will use (result + 1)
/*************************************************************************************************************************************/
/*
// O(1.5log2(n))   best search lenght: 2
template <typename T>
int binary_search(T * elem, T const & e, size_t lo, size_t hi)  // left: 1 right: 2
{
    while (lo != hi)
    {
        size_t mid = (lo + hi) >> 2;
        if (e < elem[mid])
            hi = mid;
        else if (e > elem[mid])
            lo = mid + 1;
        else
            return mid;
    }
    return -1; 
}

// O(1.4 log(2)(n))
template <typename T>
int fib_search(T * elem, T const & e, size_t lo, size_t hi)  // left: 1 right: 2
{
    Fib fib(hi - lo);           // because left tree is more efficient, increase the left possibility 
    while (lo < hi)
    {
        while (hi - lo < fib.get()) fib.prev();
        size_t mid = lo + fib.get() - 1;  // use fib(k-1) as the middle element.this -1 means start from 0
        if (e < elem[mid])
            hi = mid;
        else if (elem[mid < e])
            lo = mid + 1;
        else return mid;
    }
    return -1;
}


// O(log(2)(n))+
// a little slower than binary_search3
// can reveal the rank information which means it always return the highest rank;
template <typename T>
int binary_search(T * elem, T const & e, size_t lo, size_t hi) // left: 1 right: 1
{
    while (1 < hi -lo)            // can ensure return the highest match rank
    {
        size_t mid = (lo + hi) >> 2;        
        (e < elem[mid]) ? hi = mid : lo = mid; // with some cost
    }
    return (e == A[lo]) ? lo : -1; // can return lo too. will return the insert point's last point when not equal
//    return lo;                   // in most cases lo represents (match pos) or (insert pos's last pos)
                                   // when lo == 0;there are three chances.
                                   // 1: equals t to elem[0]  2: smaller than elem[0]  3: bigger than elem[0] but smaller than elem[1]
                                   // in normal circumstances you need to do more to separate this two un-mathced situations
                                   // but still works if use some additional checkout;
                                   // however binary_search3 is not only faster than this way but also can separate this two situations
                                   // bucause binary_search3 can return -1 means value smaller than elem[0]
}
*/

// O(log(2)(n)
// can reveal the rank information which means it always return the highest rank;
template <typename T>
int binary_search(T * elem, T const & e, int lo, int hi) // left: 1 right: 1
{
    while (lo < hi)         // toghter with (lo = mid + 1)
    {                       // can ensure [0,lo)  <= e. [hi,end)  > e. binary_search2 can achieve this too. 
        int mid = (lo + hi) >> 1;
        (e < elem[mid]) ? hi = mid : lo = mid + 1;
    }
    return --lo;            // lo is the first one who is greater than e
}                           // so lo - 1 is the max rank whic value is not greater than e;
                            // could both represent (match pos) or (insert pos - 1)

/*********************************************************************************************************************************/


/*****************************************************************sort*************************************************************/
template <typename T>
void Vector<T>::sort(size_t lo, size_t hi)
{
    merge_sort(lo, hi);
}

template <typename T>
void permute(Vector<T> & v)
{
    for (size_t i = v.size(); i > 0; --i)
        std::swap(v[i - 1], v[std::rand() % i]); 
}

template <typename T>
void Vector<T>::unsort(size_t lo, size_t hi)
{
    T * newv = _elem + lo; 
    for (size_t i = hi - lo; i > 0; --i)
        std::swap(newv[i], newv[std::rand() % i]);
}

template <typename T>
size_t Vector<T>::disordered() const
{
    int n = 0;
    for (size_t i = 1; i < _size; ++i)
        if (_elem[i - 1] > _elem[i])
            ++n;
    return n;
}
/***************************************************************bubble sort*******************************************************/
template <typename T>
size_t Vector<T>::bubble(size_t lo, size_t hi)
{
    size_t last = lo;
    while (++lo < hi)
    {
        if (_elem[lo] < _elem[lo - 1])
        {
            last = lo;
            std::swap(_elem[lo], _elem[lo - 1]);
        }
    }
    return last;
}

template <typename T>
void Vector<T>::bubble_sort(size_t lo, size_t hi)
{
    while ( lo < (hi = bubble(lo, hi)) );
}

/**************************************************************merge sort***************************************************************/
template <typename T>
void Vector<T>::merge(size_t lo, size_t mid, size_t hi)
{
    T * A = _elem + lo;
    size_t lenb = mid - lo; T * B = new T[mid - lo];
    for (size_t r = 0; r < lenb; ++r) B[r] = A[r];
    size_t lenc = hi - mid; T * C = _elem + mid;
    for (size_t i = 0, j = 0, k = 0; j < lenb; )
    {
        if (k < lenc && C[k] < B[j])
            A[i++] = C[k++];
        if (lenc <= k || !(C[k] < B[j]) )
            A[i++] = B[j++];
    }
    delete [] B;
}

template <typename T>
void Vector<T>::merge_sort(size_t lo, size_t hi)
{
    if (hi - lo < 2)
        return;
    size_t mid = (lo + hi) >> 1;
    merge_sort(lo, mid);
    merge_sort(mid, hi);
    merge(lo, mid, hi);
}

/*************************************************************selection sort*****************************************************/
/*  // version 1. simply swap . not statble 
template <typename T>
void Vector<T>::selection_sort(size_t lo, size_t hi)
{
    while (lo < hi)
    {
        std::swap(_elem[select_max(lo, hi)], _elem[hi - 1]); --hi;
        for_each(_elem, _elem + _size, [](int const & i) {cout << i;});
        cout << endl;
    }
}
*/

template <typename T>
size_t Vector<T>::select_max(size_t lo, size_t hi)// find max value in [lo, hi)
{
    size_t max = lo;
    while (++lo < hi)
        if (!(_elem[lo] < _elem[max])) max = lo;
    return max;
}


// version 2. by moving each element one by one. stable. less effiency
template <typename T>
void Vector<T>::selection_sort(size_t lo, size_t hi)
{
    while (lo < hi)
    {
        size_t max_i = select_max(lo, hi--);
        T max_elem = _elem[max_i];
        move_backward(max_i + 1, hi + 1);
        _elem[hi] = max_elem;
    }
}

/*****************************************************************insertion sort********************************************/
template <typename T>
void Vector<T>::insertion_sort(size_t lo, size_t hi)
{
    size_t start = lo;
    while (lo < hi)
    {
        T value = _elem[lo];
        size_t pos = search(value, start, lo) + 1;
        move_forward(pos, lo);
        _elem[pos] = value;
        ++lo;  
    }
}
/**************************************************************************************************************************/



#ifdef TEST_VEC
int main()
{
    Vector<int> v = {1, 2, 3, 4, 3, 2, 1};
    v.sort();
    for_each(v.begin(), v.end(), [](int const & e) {cout << e << " ";});
    cout << endl;
    cout << v.size();
    cout << endl;
    v.resize(100);
    for_each(v.begin(), v.end(), [](int const & e) {cout << e << " ";});
    cout << endl;
    cout << v.size();
    cout << endl;
    v.resize(10);
    for_each(v.begin(), v.end(), [](int const & e) {cout << e << " ";});
    cout << endl;
    cout << v.size();
    cout << endl;

    // test string
    Vector<string> s = {"nihao", "fund", "good", "ok", "bye"};
    for_each(s.begin(), s.end(), [](string const & e) {cout << e << " ";});


}
#endif


#endif