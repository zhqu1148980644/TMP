#### Given an integer n, return 1 - n in lexicographical order.

For example, given 13, return: [1,10,11,12,13,2,3,4,5,6,7,8,9].

Please optimize your algorithm to use less time and space. The input size may be as large as 5,000,000.

#### Solutions

1. ##### denary tree traversal

- recursion version

```c++
class Solution {
private:
    vector<int> res;
public:
    void dfs(int start, int n) {
        if (start > n) return;
        res.push_back(start);
        start *= 10;
        for (int i = start; i < start + 10; i++)
            dfs(i, n);
    }

    vector<int> lexicalOrder(int n) {
        for (int i = 1; i <= 9; i++)
            dfs(i, n);
        return res;
    }
};
```

- stack version

```c++
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        stack<int> s;
        for (int i = 9; i >= 1; i--)
            s.push(i);

        vector<int> res(n, 0);
        int i = 0;
        while (!s.empty()) {
            auto cur = s.top(); s.pop();
            if (cur <= n) res[i++] = cur;
            cur *= 10;
            for (int num = cur + 9; num >= cur; num--)
                if (num <= n)
                    s.push(num);
        }
        return res;
    }
};
```


2. ##### iteration

```c++
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res(n, 0);
        int cur = 1;
        for (int i = 0; i < n; i++) {
            res[i] = cur;
            if (cur * 10 <= n) {
                cur *= 10;
            }
            else {
                if (cur == n) cur /= 10;
                cur += 1;
                while (cur % 10 == 0)
                    cur /= 10;
            }
        }
        return res;
    }
};
```

3. ##### Another method

- reference: https://leetcode.com/problems/lexicographical-numbers/discuss/86331/%22Merge-Sort%22-solution-(with-explanation)