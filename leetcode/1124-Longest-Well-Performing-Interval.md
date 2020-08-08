We are given hours, a list of the number of hours worked per day for a given employee.

A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.

A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.

Return the length of the longest well-performing interval.



```
Example 1:

Input: hours = [9,9,6,0,6,6,9]
Output: 3
Explanation: The longest well-performing interval is [9,9,6].
```



#### Constraints:

-    1 <= hours.length <= 10000
-    0 <= hours[i] <= 16


#### Solutions

1. ##### prefix sum  O(n2)

```c++
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size(), res = 0;
        vector<int> sum(n + 1, 0);
        for (int j = 1; j < n + 1; j++) {
            sum[j] = sum[j - 1] + (hours[j - 1] > 8 ? 1 : -1);
            int max = 0;
            for (int i = 0; i < j; i++) {
                if (sum[j] - sum[i] > 0) {
                    max = j - i;
                    break;
                }
            }
            if (max > res)
                res = max;
        }
        return res;
    }
};
```

2. ##### prefix sum with momo stack O(n)

- Use monotonically decreasing stack.
- The problem is converted to find the maximum difference between two numbers(ordered) in prefix sum array.
- Thus the left point of such segement must be under(equal) the zero level, we use monotonically decreasing stack to record the position of these left points.
    - for example: `9 9 6 0 6 6 9  ->  0 1 2 1 0 -1 -2 -1`
    - Segments with maximum difference must start at these positions:
        - `0 5 6` with monotonically decreasing prefix sum: `0 -1 -2`.
- This method is the same as that of `problem 962`

```c++
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        vector<int> sum(n + 1);
        stack<int> s; s.push(0);
        
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + (hours[i - 1] > 8 ? 1 : -1);
            if (sum[i] < sum[s.top()])
                s.push(i);
        }

        int res = 0;
        for (int i = n; s.size() && i > 0; i--) {
            while (s.size() && sum[s.top()] < sum[i]) {
                res = max(res, i - s.top());
                s.pop();
            }
        }

        return res;
    }
};
```

3. ##### greedy with hashmap O(n)

- use hash map to record the `first` shown index of each prefix sum.
- For a negative prefix `sum[i]`, we only need to check the distance between `sum[i]` and `sum[i] - 1`, this is due to the fact that `sum[i] - 1` must occur before `sum[i] - 2/3/4/5...`. ie: when the first time `sum[i] - 2` shows up, it's left element must be `sum[i] - 1`.

```c++
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        vector<int> sum(n + 1);
        unordered_map<int, int> m;
        m[0] = 0;

        int res = 0;
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + (hours[i - 1] > 8 ? 1 : -1);
            if (!m.count(sum[i]))
                m[sum[i]] = i;
            if (sum[i] > 0)
                res = max(res, i);
            else if (m.count(sum[i] - 1))
                res = max(i - m[sum[i] - 1], res);
        }

        return res;
    }
};
```

4. ##### binary search O(nlog(n))

- Need revision.

```c++

```