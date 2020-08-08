Given an array A, partition it into two (contiguous) subarrays left and right so that:

Every element in left is less than or equal to every element in right.
left and right are non-empty.
left has the smallest possible size.
Return the length of left after such a partitioning.  It is guaranteed that such a partitioning exists.

 

Example 1:

Input: [5,0,3,8,6]
Output: 3
Explanation: left = [5,0,3], right = [8,6]
Example 2:

Input: [1,1,1,0,6,12]
Output: 4
Explanation: left = [1,1,1,0], right = [6,12]
 

Note:

2 <= A.length <= 30000
0 <= A[i] <= 10^6
It is guaranteed there is at least one way to partition A as described.

#### Solutions

1. ##### tree map O(nlog(n))

```c++
class Solution {
public:
    int partitionDisjoint(vector<int>& A) {
        if (!A.size()) return 0;
        multiset<int> large(A.begin(), A.end());
        int maxv = -1;
        for (int i = 0; i < A.size() - 1; i++) {
            maxv = max(maxv, A[i]);
            large.erase(large.find(A[i]));
            if (maxv <= *large.begin())
                return i + 1;
        }

        return A.size();
    }
};
```

2. ##### mono stack O(n) S(n)

```c++
class Solution {
public:
    int partitionDisjoint(vector<int>& A) {
        int n = A.size();
        stack<int> s;
        for (int i = n - 1; i >= 0; i--)
            if (s.empty() || A[i] <= A[s.top()])
                s.push(i);

        int maxv = -1;
        for (int i = 0; i < A.size() - 1; i++) {
            maxv = max(maxv, A[i]);
            if (s.top() == i) s.pop();
            if (maxv <= A[s.top()])
                return i + 1;
        }
        return A.size();
    }
};
```

3. ##### record minval for each suffix O(n) S(n)

```c++
class Solution {
public:
    int partitionDisjoint(vector<int>& A) {
        if (!A.size()) return 0;
        int n = A.size(), minv = A.back();
        vector<int> minvals(n);
        for (int i = n - 1; i >= 0; i--)
            minvals[i] = minv = min(A[i], minv);
        
        int maxv = -1;
        for (int i = 0; i < n - 1; i++) {
            maxv = max(maxv, A[i]);
            if (maxv <= minvals[i + 1])
                return i + 1;
        }
        return A.size();
    }
};
```

4. ##### one pass O(n) S(1)

```c++
class Solution {
public:
    int partitionDisjoint(vector<int>& A) {
        if (!A.size()) return 0;
        int leftmax = A[0], maxv = A[0];
        int pos = 0;
        for (int i = 1; i < A.size(); i++) {
            maxv = max(maxv, A[i]);
            if (A[i] < leftmax) {
                leftmax = maxv;
                pos = i;
            }
        }
        return pos + 1;
    }
};
```