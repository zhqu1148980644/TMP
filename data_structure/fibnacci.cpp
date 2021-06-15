#include <iostream>
#include <time.h>

using namespace std;

const int MAX = 90;

// fib recursion version           time:O(2^n)  space:O(n)
long long fib3(size_t n)
{
    return (2 > n) ? (long long) n : fib3(n - 1) + fib3(n - 2); 
}

// recursion  but still from bottom to up.  time:O(n) space:O(n)
long long fib2(size_t n, long long pprev, long long prev)
{
    if (n == 1)
        return prev;
    else
        return fib2(n - 1, prev, pprev + prev);
}

// fib iteration version            time:O(n)   space:O(1)               
long long fib1(size_t n)
{
    long long pprev = 0, prev = 1;
    while(n-- > 0)
    {
        prev += pprev;
        pprev = prev - pprev;
    }
    return pprev;
}

// fib linear recursion version    time:O(n)    space:O(n)
long long fib(size_t n, long long & prev)
{
    if (n == 0)
    {
        prev = 1; return 0;
    }
    else
    {
        long long pprev;
        prev = fib(n - 1, pprev);
        return pprev + prev;
    }
}


class Fib
{
    public:
        Fib(size_t n) : _pprev(0), _prev(1) { while (_prev < n) next(); }
        int get()  { return _prev; }
        int next()
        {
            _prev += _pprev;
            _pprev = _prev - _pprev;
            return _prev;
        }
        int prev()
        { 
            _pprev = _prev - _pprev;
            _prev -= _pprev;
            return _prev;
        }
    private:
        int _pprev;
        int _prev;
};



void test()
{
    clock_t start;
    
    size_t n = 0;
    start = clock();
    while (n++ < MAX)
    {
        long long temp;
        cout << "recursion : The " << n << "'th fib num is :" << fib(n, temp) << endl; 
    }
    cout << "Total time is: " << (clock() - start) << " seconds!\n";

    n = 0;
    start = clock();
    while (n++ < MAX)
        cout << "linear iteration: The " << n << "'th fib num is :" << fib1(n) << endl; 
    cout << "Total time is: " << (clock() - start) << " seconds!\n";

    n = 0;
    start = clock();
    while (n++ < MAX)
        cout << "recursion linear: The " << n << "'th fib num is :" << fib2(n, 0, 1) << endl; 
    cout << "Total time is: " << (clock() - start) << " seconds!\n";


    n = 0;
    start = clock();
    while (n++ < MAX)
        cout << "recursion slow: The " << n << "'th fib num is :" << fib3(n) << endl; 
    cout << "Total time is: " << (clock() - start) << " seconds!\n";
}

int main()
{
    test();
}