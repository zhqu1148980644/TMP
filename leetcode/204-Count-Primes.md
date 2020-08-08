#### Count the number of prime numbers less than a non-negative number, n.

```
Example:

Input: 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
```

#### Solutions

1. ##### Sieve of Eratosthenes



```c++
class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) return 0;
        vector<bool> isPrime(n, true);

        for (int i = 2; i * i < n; i++) {
            // start from i * i instead of i * 2  i * 3..., because these number was marked as non-prime when visiting 2, 3 .... i - 1.
            // or add one line above. if (isprime[i])
            for (int j = i * i; j < n; j += i)
                isPrime[j] = false;

        return count(isPrime.begin() + 2, isPrime.end(), true);
    }
};
```


2. ##### euler sieve


```c++
class Solution {
public:
    int countPrimes(int n) {
        vector<int> primes(n), vis(n);
        if (n <= 2) return 0;
        vis[0] = vis[1] = 1; 
        int cnt = 0;
        for (int i = 2; i < n; i++) {
            if (!vis[i])
                primes[cnt++] = i;
            for (int j = 0; j < cnt && i * primes[j] < n; j++) {
                vis[i * primes[j]] = true;
                if (i % primes[j] == 0)
                    break;
            }
        }
        return cnt;
    }
};
```