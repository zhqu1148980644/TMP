Given a list of daily temperatures T, return a list such that, for each day in the input, tells you how many days you would have to wait until a warmer temperature. If there is no future day for which this is possible, put 0 instead.

For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].

Note: The length of temperatures will be in the range [1, 30000]. Each temperature will be an integer in the range [30, 100].

#### Solutions

1. ##### monotonous decreasing stack O(n)

```c++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        stack<int> s;
        vector<int> res(T.size());
        for (int d = 0; d < T.size(); d++) {
            int t = T[d];
            while (!s.empty() && t > T[s.top()]) {
                res[s.top()] = d - s.top();
                s.pop();
            }
            s.push(d);
        }

        return res;
    }
};
```


2. ##### greedy ? O(n)

- reference: https://leetcode-cn.com/problems/daily-temperatures/solution/java-by-sdwwld/
- Scan the array backwards and reuse infos fetched before.

```c++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        vector<int> res(T.size());

        for (int i = T.size() - 1; i >= 0; i--) {
            int j = i + 1;
            while (j < T.size()) {
                if (T[j] > T[i]) {
                    res[i] = j - i;
                    break;
                }
                else if (res[j] == 0)
                    break;
                else
                    j = j + res[j];
            }
        }
        return res;
    }
};
```