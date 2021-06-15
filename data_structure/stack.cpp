#ifndef STACK
#define STACK

#ifndef TEST
#define TEST
#define TEST_STACK
#endif


#include "vector.cpp"
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <string>



using std::string;


template <typename T, typename SEQUENCE=Vector<T> >
class Stack
{
    public:
        typedef T value_type;
        typedef size_t size_type;
        typedef SEQUENCE container_type;

        template <typename X>
        void push(X && e)                { _array.push_back(std::forward<X>(e)); }
        T pop()                          { return _array.pop_back(); }
        T & top()                        { return _array.back(); }            
        T const & top() const            { return _array.back(); }            
        size_t size() const              { return _array.size();  }
        bool empty() const               { return _array.empty(); }
        int find(T const & e) const      { return _array.find(e); }
    private:
        SEQUENCE _array;
};


struct Tmp
{
    Tmp() : tmp(0) {}
    size_t tmp;   
};

#ifdef TEST_STACK
int main()
{
    Stack<string> s;
    s.push("nihao");
    s.push("fine");
    cout << s.top() << endl;
    s.top() = "asdasd";
    cout << s.top() << endl;
    s.push("end");
    cout << s.size() << endl;
    cout << s.find("fine") << endl;
    cout << s.pop() << endl;
    cout << s.pop() << endl;
    cout << s.pop() << endl;
    string s1 = "dasdasd";
    cout << s1 << endl;
    s1 = "asdasda";
    cout << s1 << endl;

    Stack<Stack<Tmp>> ss;
    Stack<Tmp> st;
    ss.push(st);
}

#endif



#endif