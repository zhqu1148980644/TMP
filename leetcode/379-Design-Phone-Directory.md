Design a Phone Directory which supports the following operations:

 

get: Provide a number which is not assigned to anyone.
check: Check if a number is available or not.
release: Recycle or release a number.
 

Example:

// Init a phone directory containing a total of 3 numbers: 0, 1, and 2.
PhoneDirectory directory = new PhoneDirectory(3);

// It can return any available phone number. Here we assume it returns 0.
directory.get();

// Assume it returns 1.
directory.get();

// The number 2 is available, so return true.
directory.check(2);

// It returns 2, the only number that is left.
directory.get();

// The number 2 is no longer available, so return false.
directory.check(2);

// Release number 2 back to the pool.
directory.release(2);

// Number 2 is available again, return true.
directory.check(2);
 

Constraints:

1 <= maxNumbers <= 10^4
0 <= number < maxNumbers
The total number of call of the methods is between [0 - 20000]



#### Solutions

1. ##### hashmap

- reference: https://leetcode-cn.com/problems/design-phone-directory/solution/c-shuang-shu-zu-o1ti-jie-by-da-li-wang/

```c++
class PhoneDirectory {
public:
    /** Initialize your data structure here
        @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    vector<int> mem;
    vector<bool> used;
    int cur = 0;
    PhoneDirectory(int maxNumbers) : mem(maxNumbers), used(maxNumbers) {
        iota(mem.begin(), mem.end(), 0);
    }
    
    /** Provide a number which is not assigned to anyone.
        @return - Return an available number. Return -1 if none is available. */
    int get() {
        if (cur >= mem.size()) return -1;
        used[mem[cur]] = 1;
        return mem[cur++];
    }
    
    /** Check if a number is available or not. */
    bool check(int number) {
        return number < mem.size() && number >= 0 && !used[number];       
    }
    
    /** Recycle or release a number. */
    void release(int number) {
        // numbers in mem before cur would be corrupted.
        if (used[number]) {
            used[number] = false;
            mem[--cur] = number;
        }
    }
};

```