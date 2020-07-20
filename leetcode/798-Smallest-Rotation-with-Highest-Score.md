 Given an array A, we may rotate it by a non-negative integer K so that the array becomes A[K], A[K+1], A{K+2], ... A[A.length - 1], A[0], A[1], ..., A[K-1].  Afterward, any entries that are less than or equal to their index are worth 1 point. 

For example, if we have [2, 4, 1, 3, 0], and we rotate by K = 2, it becomes [1, 3, 0, 2, 4].  This is worth 3 points because 1 > 0 [no points], 3 > 1 [no points], 0 <= 2 [one point], 2 <= 3 [one point], 4 <= 4 [one point].

Over all possible rotations, return the rotation index K that corresponds to the highest score we could receive.  If there are multiple answers, return the smallest such index K.

Example 1:
Input: [2, 3, 1, 4, 0]
Output: 3
Explanation:  
Scores for each K are listed below: 
K = 0,  A = [2,3,1,4,0],    score 2
K = 1,  A = [3,1,4,0,2],    score 3
K = 2,  A = [1,4,0,2,3],    score 3
K = 3,  A = [4,0,2,3,1],    score 4
K = 4,  A = [0,2,3,1,4],    score 3
So we should choose K = 3, which has the highest score.

 

Example 2:
Input: [1, 3, 0, 2, 4]
Output: 0
Explanation:  A will always have 3 points no matter how it shifts.
So we will choose the smallest K, which is 0.
Note:

A will have length at most 20000.
A[i] will be in the range [0, A.length].

#### Solutions

1. ##### math O(n)

- Borrowed from others.
- Calculate when(k steps) does each element would contribute to the decreasement of the score.
- At each step, except for the decreasing of scores based on the table calculated above, the score must be added by 1. ie: the `A[0]` moved to the back.
    - In case of `A[0] == 0`, there will no score be plused. Nevertheless, this special case would not affect our code(check comments in codes).

```
For number 1, after moved 2 steps, 1 will be at index(0)
It's clearly that the number of steps equals to `index(2) - 1 + 1`
However it works only when the current number has indexes larger than himself.

current permutaion:
index                     0 1 2 3 4 
nums:   2 3 1 4 0         2 3 1 4 0
index   0 1 2 3 4         5 6 7 8 9

For number 2, it's index is smaller than itself, it should be moved to the back of the array.
To cater for steps changing to a negative number, we use `(index(0)) + 5 - 2 + 1` for computing it's steps. This formula works like inserting a copy of the original array at the front.

```


```c++
class Solution {
public:
    int bestRotation(vector<int>& A) {
        int len = A.size();
        vector<int> deduce(len);
        // deduce[k] represents the deduced score when moved k steps.
        for (int i = 0; i < len; i++)
            --deduce[(i + len - A[i] + 1) % len];
        int inc = deduce[0], maxi = 0, maxc = deduce[0];
        // In eachstep, except for the decreasing of scores, there must be 1 score added. ie. The A[0] moved to the back.
        // (In case A[0] == 0, deduce[1] has been deduced 1 when checking the A[0], thus +1 - 1 = 0, would not interfere with the answer.
        for (int i = 1; i < len; i++) {
            inc += deduce[i] + 1;
            if (inc > maxc) {
                maxi = i;
                maxc = inc;
            }
        }
        return maxi;
    }
};
```