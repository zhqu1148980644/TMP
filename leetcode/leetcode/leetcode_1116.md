---
title: Print Zero Even O
date: 2021-01-04
---
Suppose you are given the following code:

```
class ZeroEvenOdd {
  public ZeroEvenOdd(int n) { ... }      // constructor
  public void zero(printNumber) { ... }  // only output 0's
  public void even(printNumber) { ... }  // only output even numbers
  public void odd(printNumber) { ... }   // only output odd numbers
}
```

The same instance of ZeroEvenOdd will be passed to three different threads:

-    Thread A will call zero() which should only output 0's.
-    Thread B will call even() which should only ouput even numbers.
-    Thread C will call odd() which should only output odd numbers.

Each of the threads is given a printNumber method to output an integer. Modify the given program to output the series 010203040506... where the length of the series must be 2n.

 

```
Example 1:

Input: n = 2
Output: "0102"
Explanation: There are three threads being fired asynchronously. One of them calls zero(), the other calls even(), and the last one calls odd(). "0102" is the correct output.

Example 2:

Input: n = 5
Output: "0102030405"
```


#### Solutions

1. ##### mutex

```cpp
class ZeroEvenOdd {
private:
    int n;
    mutex mzero;
    mutex meven;
    mutex modd;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        meven.lock();
        modd.lock();
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i++) {
            mzero.lock();
            printNumber(0);
            if (i % 2 == 1)
                modd.unlock();
            else
                meven.unlock();
        }

    }

    void even(function<void(int)> printNumber) {
        for (int i = 2; i <= n; i++) {
            if (i % 2 == 0) {
                meven.lock();
                printNumber(i);
                mzero.unlock();
            }
        }
    }

    void odd(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 1) {
                modd.lock();
                printNumber(i);
                mzero.unlock();
            }
        }
    }
};


```


2. ##### condition variable

```cpp
class ZeroEvenOdd {
private:
    int n;
    mutex mt;
    std::condition_variable cv;
    int stage = 0;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i++) {
            std::unique_lock<std::mutex> lk(mt);
            cv.wait(lk, [&](){ return stage == 0; });
            printNumber(0);
            if (i % 2 == 1)
                stage = 1;
            else
                stage = 2;
            cv.notify_all();
        }        
    }

    void even(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 0) {
                unique_lock<std::mutex> lk(mt);
                cv.wait(lk, [&](){ return stage == 2; });
                printNumber(i);
                stage = 0;
                cv.notify_all();
            }
        }
    }

    void odd(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 1) {
                unique_lock<std::mutex> lk(mt);
                cv.wait(lk, [&](){ return stage == 1; });
                printNumber(i);
                stage = 0;
                cv.notify_all();
            }
        }
    }
};
```