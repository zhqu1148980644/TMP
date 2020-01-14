#### Suppose we have a class

```
public class Foo {
  public void first() { print("first"); }
  public void second() { print("second"); }
  public void third() { print("third"); }
}
```

The same instance of Foo will be passed to three different threads. Thread A will call first(), thread B will call second(), and thread C will call third(). Design a mechanism and modify the program to ensure that second() is executed after first(), and third() is executed after second().

 

```
Example 1:

Input: [1,2,3]
Output: "firstsecondthird"
Explanation: There are three threads being fired asynchronously. The input [1,2,3] means thread A calls first(), thread B calls second(), and thread C calls third(). "firstsecondthird" is the correct output.

Example 2:

Input: [1,3,2]
Output: "firstsecondthird"
Explanation: The input [1,3,2] means thread A calls first(), thread B calls third(), and thread C calls second(). "firstsecondthird" is the correct output.
```

 

#### Note:

- We do not know how the threads will be scheduled in the operating system, even though the numbers in the input seems to imply the ordering. The input format you see is mainly to ensure our tests' comprehensiveness.

#### Solutions

1. ##### python

- `threading.Lock()`
- `acquire()`
- `release()`

```python
class Foo:
    def __init__(self):
        self.l2 = threading.Lock()
        self.l2.acquire()
        self.l3 = threading.Lock()
        self.l3.acquire()


    def first(self, printFirst: 'Callable[[], None]') -> None:

        # printFirst() outputs "first". Do not change or remove this line.
        printFirst()
        self.l2.release()


    def second(self, printSecond: 'Callable[[], None]') -> None:
        self.l2.acquire()
        # printSecond() outputs "second". Do not change or remove this line.
        printSecond()
        self.l3.release()


    def third(self, printThird: 'Callable[[], None]') -> None:
        self.l3.acquire()
        # printThird() outputs "third". Do not change or remove this line.
        printThird()

```

- `threading.Semaphore`
- `release()`

```python
class Foo:
    def __init__(self):
        self.s2 = threading.Semaphore(0)
        self.s3 = threading.Semaphore(0)

    def first(self, printFirst: 'Callable[[], None]') -> None:
        
        # printFirst() outputs "first". Do not change or remove this line.
        printFirst()
        self.s2.release()


    def second(self, printSecond: 'Callable[[], None]') -> None:
        self.s2.acquire()
        # printSecond() outputs "second". Do not change or remove this line.
        printSecond()
        self.s3.release()

    def third(self, printThird: 'Callable[[], None]') -> None:
        self.s3.acquire()
        # printThird() outputs "third". Do not change or remove this line.
        printThird()
        
```

- `threading.Event()`
- `wait()`
- `set()`

```python
class Foo:
    def __init__(self):
        self.e2 = threading.Event()
        self.e3 = threading.Event()


    def first(self, printFirst: 'Callable[[], None]') -> None:

        # printFirst() outputs "first". Do not change or remove this line.
        printFirst()
        self.e2.set()


    def second(self, printSecond: 'Callable[[], None]') -> None:
        self.e2.wait()
        # printSecond() outputs "second". Do not change or remove this line.
        printSecond()
        self.e3.set()


    def third(self, printThird: 'Callable[[], None]') -> None:
        self.e3.wait()
        # printThird() outputs "third". Do not change or remove this line.
        printThird()
```

- `queue.Queue`
- `put()`
- `get()`

```python
class Foo:
    def __init__(self):
        import queue
        self.q2 = queue.Queue(1)
        self.q3 = queue.Queue(1)


    def first(self, printFirst: 'Callable[[], None]') -> None:

        # printFirst() outputs "first". Do not change or remove this line.
        printFirst()
        self.q2.put(1)


    def second(self, printSecond: 'Callable[[], None]') -> None:
        self.q2.get()
        # printSecond() outputs "second". Do not change or remove this line.
        printSecond()
        self.q3.put(1)


    def third(self, printThird: 'Callable[[], None]') -> None:
        self.q3.get()
        # printThird() outputs "third". Do not change or remove this line.
        printThird()
```


2. ##### c++

- `mutex`
- `lock()`
- `unlock()`

```c++
class Foo {
public:
    mutex t2;
    mutex t3;

    Foo() {
        t2.lock();
        t3.lock();
    }

    void first(function<void()> printFirst) {

        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        t2.unlock();
    }

    void second(function<void()> printSecond) {
        t2.lock();
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        t3.unlock();
    }

    void third(function<void()> printThird) {
        t3.lock();
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};
```