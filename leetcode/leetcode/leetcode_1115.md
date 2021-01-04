---
title:  Print FooBar Alternately
date: 2021-01-04
---
Suppose you are given the following code:

```cpp
class FooBar {
  public void foo() {
    for (int i = 0; i < n; i++) {
      print("foo");
    }
  }

  public void bar() {
    for (int i = 0; i < n; i++) {
      print("bar");
    }
  }
}
```

The same instance of FooBar will be passed to two different threads. Thread A will call foo() while thread B will call bar(). Modify the given program to output "foobar" n times.

 
```
Example 1:

Input: n = 1
Output: "foobar"
Explanation: There are two threads being fired asynchronously. One of them calls foo(), while the other calls bar(). "foobar" is being output 1 time.

Example 2:

Input: n = 2
Output: "foobarfoobar"
Explanation: "foobar" is being output 2 times.
```


#### Solutions

1. ##### mutex

```cpp
class FooBar {
private:
    int n;
    mutex mfoo, mbar;

public:
    FooBar(int n) {
        this->n = n;
        mbar.lock();
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            mfoo.lock();
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            mbar.unlock();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            mbar.lock();
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            mfoo.unlock();
        }
    }
};
```

2. ##### conditional varibale

```cpp
class FooBar {
private:
    int n;
    condition_variable cv;
    mutex mt;
    bool isfoo = true;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lk(mt);
            cv.wait(lk, [this]() { return isfoo; });
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            isfoo = false;
            cv.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lk(mt);
            cv.wait(lk, [this]() { return !isfoo; });
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            isfoo = true;
            cv.notify_one();
        }
    }
};
```