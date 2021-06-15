#ifndef LIST
#define LIST

#ifndef TEST
#define TEST
#define TEST_LIST
#endif

#include <algorithm>
#include <iostream>
#include <initializer_list>
#include <cstdlib>
using std::cout;
using std::endl;
using std::for_each;
using std::initializer_list;

template <typename T>
class List;

template <typename T>
class ListNode
{
        friend class List<T>;
    public:
        using pnode = ListNode<T> *;
        ListNode() : prev(nullptr), next(nullptr) {}
        ListNode(T const & e, pnode p=nullptr, pnode n=nullptr) 
            : data(e), prev(p), next(n) {}
        template <typename X>
        ListNode(X && e, pnode p=nullptr, pnode n=nullptr) 
            : data(std::forward<X>(e)), prev(p), next(n) {}
        template <typename X>
        pnode insertAsPrev(X && e);
        template <typename X>
        pnode insertAsNext(X && e);
    private:
        T data;
        pnode prev;
        pnode next;
};

template <typename T>
template <typename X>
ListNode<T> * ListNode<T>::insertAsPrev(X && e)
{
    pnode node = new ListNode<T>(std::forward<X>(e), prev, this);
    prev->next = node; prev = node;
    return node;
}

template <typename T>
template <typename X>
ListNode<T> * ListNode<T>::insertAsNext(X && e)
{
    pnode node = new ListNode<T>(std::forward<X>(e), this, next);
    next->prev = node; next = node;
    return node;
}


template <typename T>
class List
{
    public:
        typedef T value_type;
        typedef size_t size_type;
        typedef ListNode<T> * pnode;

        /**********************************************************iterator****************************************/
        struct iterator
        {
            iterator() : p(nullptr)               {}
            iterator(pnode ptr) : p(ptr)          {}
            iterator operator++(int)              { p=p->next; return p->prev; }
            iterator & operator++()               { p=p->next; return *this; }
            iterator operator--(int)              { p=p->prev; return p->next; }
            iterator & operator--()               { p=p->prev; return *this; }
            bool operator==(iterator const & i2)  { return p == i2.p; }
            bool operator!=(iterator const & i2)  { return !operator==(i2); }
            template <typename X>
            iterator & operator=(X && e)          { p->data = std::forward<X>(e); }
            T & operator*()                       { return p->data; }
            T operator*() const                   { return p->data; }
            private:
                pnode p;
        };
        iterator begin() { return iterator(first()); }
        iterator end() { return iterator(trailer); }
        /**********************************************************************************************************/

        List() { init(); }
        List(List<T> const & L, size_t r, size_t n);
        List(pnode p, size_t n);
        List(initializer_list<T> il);
        List(List<T> const & L);
        List(List<T> && L);
        List<T> & operator=(List<T> const & L);
        List<T> & operator=(List<T> && L);
        ~List();

        T & operator[](size_t r) const;
        T operator[](size_t r);
        pnode first() const                                           { return header->next; }
        pnode last() const                                            { return trailer->prev; }
        size_t size() const                                           { return _size; } 
        bool empty() const                                            { return !_size; }
        T & front()                                                   { return first()->data; } 
        T & back()                                                    { return first->data; } 
        T const & front() const                                       { return first()->data; } 
        T const & back() const                                        { return last()->data; } 
        T pop_back()                                                  { return remove(last()); } 
        T pop_front()                                                 { return remove(first()); } 
        template <typename X>
        void push_back(X && e)                                        { insertAsLast(std::forward<X>(e)); } 
        template <typename X>
        void push_front(X && e)                                       { insertAsFirst(std::forward<X>(e)); } 

        bool valid(pnode p) const                                     { return p && (header != p) && (trailer != p); }
        size_t disordered() const;
        T remove(pnode p);
        pnode find(T const & e) const                                 { return find(e, _size, trailer); }
        pnode find(T const & e, size_t n, pnode p) const;
        pnode search(T const & e) const                               { return search(e, _size, trailer); }
        pnode search(T const & e, size_t n, pnode p) const;
        pnode select_max(pnode p, size_t n);
        pnode select_max()                                            { return select_max(header->next, _size); }

        template <typename X>
        pnode insertAsFirst(X && e);
        template <typename X>
        pnode insertAsLast(X && e);
        template <typename X>
        pnode insertBefore(pnode p, X && e);
        template <typename X>
        pnode insertAfter(pnode p, X && e);
        void insertBefore(pnode p, pnode target);
        void insertAfter(pnode p, pnode target);
        size_t deduplicate();
        size_t uniquify();
        void reverse();

        void traverse( void (*)(T &));
        template <typename VST>
        void traverse(VST &);

        void unsort(pnode p, size_t n);
        void unsort()                                            { unsort(first(), _size); }
        void sort(pnode p, size_t n);
        void sort() { sort(first(), _size); }

        void show_status()                                       { pnode p = first(); while (p != trailer) {cout << p->data; p = p->next;}} 

    protected:
        void init();
        size_t clear();
        void copy_nodes(pnode, size_t);
        void merge(List<T> & L)                                  { merge(first(), _size, L.first(), L._size); }
        void merge(pnode &, size_t, pnode &, size_t);
        void merge_sort(pnode &, size_t);
        void selection_sort(pnode, size_t);
        void insertion_sort(pnode, size_t);

    private:
        size_t _size;
        pnode header;
        pnode trailer;
    
};


template <typename T>
List<T>::List(initializer_list<T> il)
{
    init();
    for (T const & i : il) insertAsLast(i);
}

template <typename T>
List<T>::List(List<T> const & L)
{
    copy_nodes(L.first(), L._size);
}

template <typename T>
List<T>::List(List<T> && L) : _size(L._size), header(L.header), trailer(L.trailer)
{
    L._size = 0;
    L.header = L.trailer = nullptr;
}

template <typename T>
List<T> & List<T>::operator=(List<T> const & L)
{
    clear();
    copy_nodes(L.first(), L._size);
    return *this;
}

template <typename T>
List<T> & List<T>::operator=(List<T> && L)
{
    ~List();
    _size = L._size;
    header = L.header; trailer = L.trailer;
    L._size = 0;
    L.header = L.trailer = nullptr;
    return *this;
}

template <typename T>
List<T>::List(List<T> const & L, size_t r, size_t n)
{
    copy_nodes(L[r], n);
}

template <typename T>
List<T>::List(pnode p, size_t n)
{
    copy_nodes(p, n);
}

template <typename T>
void List<T>::copy_nodes(pnode p, size_t n)
{
    init();
    while (n--)
    {
        insertAsLast(p->data);
        p = p->next;
    }
}

template <typename T>
List<T>::~List()
{
    clear();
    delete header; delete trailer;
}

template <typename T>
size_t List<T>::clear()
{
    size_t oldsize = _size;
    pnode node = header->next;
    while (_size--)
    {
        node = node->next;
        delete node->prev;
    }
    return oldsize;
}

template <typename T>
void List<T>::init()
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->next = trailer; header->prev = nullptr;
    trailer->prev = header, trailer->next = nullptr;
    _size = 0;
}

template <typename T>
T & List<T>::operator[](size_t r) const
{
    pnode tmp = first();
    while (0 < r--)
        tmp = tmp->next;
    return tmp->data;
}

template <typename T>
T List<T>::operator[](size_t r)
{
    pnode tmp = first();
    while (0 < r--)
        tmp = tmp->next;
    return tmp->data;
}

template <typename T>
void List<T>::unsort(pnode p, size_t n)
{
    while (n)
    {
        size_t step = std::rand() % n;
        pnode tmp = p;
        while (step) { tmp = tmp->next; --step; }
        std::swap(p->data, tmp->data);
        p = p->next;
        --n;
    }
}

template <typename T>
template <typename X>
ListNode<T> * List<T>::insertAsFirst(X && e)
{
    ++_size; return header->insertAsNext(std::forward<X>(e));
}

template <typename T>
template <typename X>
ListNode<T> * List<T>::insertAsLast(X && e)
{
    ++_size; return trailer->insertAsPrev(std::forward<X>(e));
}

template <typename T>
template <typename X>
ListNode<T> * List<T>::insertBefore(pnode p, X && e)
{
    ++_size; return p->insertAsPrev(std::forward<X>(e));
}

template <typename T>
template <typename X>
ListNode<T> * List<T>::insertAfter(pnode p, X && e)
{
    ++_size; return p->insertAsNext(std::forward<X>(e));
}

template <typename T>
void List<T>::insertBefore(pnode p, pnode target)
{
    if (p->prev == target || p == target)
        return;
    target->prev->next = target->next;
    target->next->prev = target->prev;
    p->prev->next = target; target->prev = p->prev;
    p->prev = target; target->next = p;
}

template <typename T>
void List<T>::insertAfter(pnode p, pnode target)
{
    if (p->next == target || p == target)
        return;
    target->prev->next = target->next;
    target->next->prev = target->prev;
    target->next = p->next; p->next->prev = target;
    p->next = target; target->prev = p;
}

template <typename T>
size_t List<T>::disordered() const
{
    size_t num = 0;
    pnode tmp = header->next;
    while ((tmp = tmp->next) != trailer)
        if (tmp->data < tmp->prev->data) ++num;
    return num;
}

template <typename T>
T List<T>::remove(pnode p)
{
    T e = p->data;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p; --_size;
    return e;
}

template <typename T>
void List<T>::traverse(void (*visit)(T &))
{
    for (pnode p = header->next; p != trailer; p = p->next)
        visit(p->data);
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST & visit)
{
    for (pnode p = header->next; p != trailer; p = p->next)
        visit(p->data);
}

/*          slow version. need do new and delete operation
template <typename T>
size_t List<T>::uniquify()
{
    size_t oldsize = _size;
    pnode l; r;
    for (l = header, r = header->next; r != trailer; l = r, r = r->next)
    {
        if (r->data == l->data):
        {
            remove(r);
            r = l;
        }
    }
}
*/

template <typename T>
size_t List<T>::deduplicate()
{
    if (_size < 2)
        return 0;
    size_t oldsize = _size;
    pnode p = header; size_t r = 0;
    while ( (p = p->next) != trailer )
    {
        pnode query = find(p->data, r, p);
        query ? remove(query) : r++;
    }
    return oldsize - _size;
}

template <typename T>
size_t List<T>::uniquify()
{
    size_t oldsize = _size;
    pnode left = header->next; pnode right;
    while ( (right = left->next) != trailer )
    {
        if (right->data != left->data)
            left = right;
        else
            remove(right);
    }
    return oldsize - _size;
}

template <typename T>
ListNode<T> * List<T>::find(T const & e, size_t n, pnode p) const
{
    while (n--)
        if ( (p = p->prev)->data == e ) return p;
    return nullptr;
}

template <typename T>
ListNode<T> * List<T>::search(T const & e, size_t n, pnode p) const
{
    while (n-- && (e < p->prev->data))
        p = p->prev;
    return p->prev;
}

/***************************************************************sort***************************************************/
template <typename T>
void List<T>::sort(pnode p, size_t n)
{
    merge_sort(p, n);
}
/************************************************************selection sort********************************************/
template <typename T>
ListNode<T> * List<T>::select_max(pnode p, size_t n)
{
    pnode max = p;
    while (0 < --n)
        if ( !((p = p->next)->data < max->data) ) max = p;
    return max;
}

/* slow version call new and delete operation
template <typename T>
void List<T>::selection_sort(pnode p, size_t n) // slow way
{
    pnode head = p; tail = p;
    for (size_t i = 0; i < n; ++i) tail = tail->next;
    while (1 < n)
    {
        insertBefore(tail, remove(select_max(p, n--)));// use new/delete cause low efficiency
        tail = tail->prev;
    }
}

// slow version . will break the original order.
template <typename T>
void List<T>::selection_sort(pnode p, size_t n)
{
   pnode tail = p;
   for(size_t i = 0; i < n; ++i) tail = tail->next; // tail is the last element p + n -1
   while ( 1< n)
   {
       std::swap(tail->prev->data, select_max(p, n--)->data);    // swap value  does not ensure the originla order
       tail = tail->prev;        // another way: alte
   }
}
*/

template <typename T>
void List<T>::selection_sort(pnode p, size_t n)//  [p, p + n)
{
   pnode tail = p;
   for(size_t i = 0; i < n; ++i) tail = tail->next; // tail is the last element p + n
   while ( 1 < n)
   {
       pnode max = select_max(p, n--);
       insertAfter(tail->prev, max);
       tail = max;
   }
}

/******************************************************************insertion sort*************************************/
/*  slow version. use interface which will call new and delete
template <typename T>
void List<T>::insertion_sort(pnode p, size_t n)
{
    for ( size_t i = 0; i < n; ++i)
    {
        insertAfter(search(p->data, r, p), p->data);// use interface slow
        p = p->next; remove(p->prev);
    }
}
*/

template <typename T>
void List<T>::insertion_sort(pnode p, size_t n)
{
    for ( size_t i = 0; i < n; ++i )
    {
        pnode find = search(p->data, i, p);
        p = p->next;
        insertAfter(find, p->prev);
    }
}


/****************************************************************merge sort*********************************************/
template <typename T>
void List<T>::merge(pnode & p, size_t m, pnode & q, size_t n)
{
    pnode pp = p->prev;
    while ( 0 < n )// different from the version in vector, this one doesn't require p + n =q
    {              // p + m <= q should work too
        if ( (0 < m) && (p->data <= q->data) )
        {
            if ( q == (p = p->next) ) break;
            --m;
        }
        else
        {
            insertBefore(p, (q = q->next)->prev); --n;
        }
    }
    p = pp->next;   
}

template <typename T>
void List<T>::merge_sort(pnode & p, size_t n)
{
    if (n < 2)
        return;
    size_t m = n >> 1;
    pnode mid = p;
    for (size_t i = 0; i < m; ++i)
        mid = mid->next;
    merge_sort(p, m);
    merge_sort(mid, n - m);
    merge(p, m, mid, n - m);
}
/***************************************************************************************************************************/

#ifdef TEST_LIST
int main()
{
    List<int> l = {9, 2, 5, 1, 8, 0, 4, 2, 7, 3, 7, 4};
    for_each(l.begin(), l.end(), [](int const & i) {cout << i << " ";}); cout << endl;
    l.sort();
    for_each(l.begin(), l.end(), [](int const & i) {cout << i << " ";}); cout << endl;
    l.push_back(1);
    for_each(l.begin(), l.end(), [](int const & i) {cout << i << " ";}); cout << endl;
    List<int>::pnode find = l.find(5);
    l.sort(find, 6);
    for_each(l.begin(), l.end(), [](int const & i) {cout << i << " ";}); cout << endl;
    l.insertAsFirst(7);
    l.insertAsLast(8);
    l.insertBefore(find, 5);
    l.insertAfter(find, 4);
    cout << l.size() << endl;
    cout << l.disordered() << endl;
    l.sort();
    cout << l.disordered() << endl;
    l.unsort();
    for_each(l.begin(), l.end(), [](int const & i) {cout << i << " ";}); cout << endl;
    l.sort();
    for_each(l.begin(), l.end(), [](int const & i) {cout << i << " ";}); cout << endl;
    l.unsort(find, 4);
    for_each(l.begin(), l.end(), [](int const & i) {cout << i << " ";}); cout << endl;
    l.remove(find);
    for_each(l.begin(), l.end(), [](int const & i) {cout << i << " ";}); cout << endl;
}

#endif




#endif