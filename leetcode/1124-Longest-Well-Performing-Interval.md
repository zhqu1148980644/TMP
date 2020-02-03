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

```c++
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        vector<int> sum(n + 1);
        stack<int> s; s.push(0);

        for (int i = 1; i < n + 1; i++) {
            sum[i] = sum[i - 1] + (hours[i - 1] > 8 ? 1 : -1);
            if (sum[i] < sum[s.top()])
                s.push(i);
        }

        int maxn = 0;
        for (int i = n; s.size() && i > 0; i--) {
            while (s.size() && sum[s.top()] < sum[i]) {
                maxn = max(maxn, i - s.top());
                s.pop();
            }
        }

        return maxn;
    }
};
```

3. ##### hashmap O(n)

- As prefix sums are continuous, we can fetch the segments with difference of 1 in `O(1)` time with a hashmap.

```c++
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        vector<int> sum(n + 1);
        unordered_map<int, int> m;
        m[0] = 0;

        int maxl = 0;
        for (int i = 1; i < n + 1; i++) {
            sum[i] = sum[i - 1] + (hours[i - 1] > 8 ? 1 : -1);
            if (!m.count(sum[i]))
                m[sum[i]] = i;
            if (sum[i] > 0)
                maxl = max(maxl, i);
            else if (m.count(sum[i] - 1))
                maxl = max(i - m[sum[i] - 1], maxl);
        }

        return maxl;
    }
};
```

4. ##### binary search O(nlog(n))

- Need revision.

```c++

```