Write a program that outputs the string representation of numbers from 1 to n, however:

If the number is divisible by 3, output "fizz".
If the number is divisible by 5, output "buzz".
If the number is divisible by both 3 and 5, output "fizzbuzz".
For example, for n = 15, we output: 1, 2, fizz, 4, buzz, fizz, 7, 8, fizz, buzz, 11, fizz, 13, 14, fizzbuzz.

Suppose you are given the following code:

class FizzBuzz {
  public FizzBuzz(int n) { ... }               // constructor
  public void fizz(printFizz) { ... }          // only output "fizz"
  public void buzz(printBuzz) { ... }          // only output "buzz"
  public void fizzbuzz(printFizzBuzz) { ... }  // only output "fizzbuzz"
  public void number(printNumber) { ... }      // only output the numbers
}
Implement a multithreaded version of FizzBuzz with four threads. The same instance of FizzBuzz will be passed to four different threads:

Thread A will call fizz() to check for divisibility of 3 and outputs fizz.
Thread B will call buzz() to check for divisibility of 5 and outputs buzz.
Thread C will call fizzbuzz() to check for divisibility of 3 and 5 and outputs fizzbuzz.
Thread D will call number() which should only output the numbers.

#### Solutions

1. ##### conditional variable


```c++
class FizzBuzz {
private:
    int n;
    int cur = 1;
    mutex mt;
    condition_variable cv;
public:
    FizzBuzz(int n) {
        this->n = n;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while (cur <= n) {
            unique_lock<mutex> lk(mt);
            cv.wait(lk, [&]() { return cur > n || (cur % 3 == 0 && cur % 5 != 0); });
            if (cur <= n) {
                cur++;
                printFizz();
            }
            cv.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while (cur <= n) {
            unique_lock<mutex> lk(mt);
            cv.wait(lk, [&]() { return cur > n || (cur % 3 != 0 && cur % 5 == 0); });
            if (cur <= n) {
                cur++;
                printBuzz();
            }
            cv.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while (cur <= n) {
            unique_lock<mutex> lk(mt);
            cv.wait(lk, [&]() { return cur > n || (cur % 3 == 0 && cur % 5 == 0); });
            if (cur <= n) {
                cur++;
                printFizzBuzz();
            }
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while (cur <= n) {
            unique_lock<mutex> lk(mt);
            cv.wait(lk, [&]() { return cur > n || (cur % 3 != 0 && cur % 5 != 0); });
            if (cur <= n) {
                printNumber(cur);
                cur++;
            }
            cv.notify_all();
        }
    }
};
```