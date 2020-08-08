Given a binary array data, return the minimum number of swaps required to group all 1’s present in the array together in any place in the array.

 

Example 1:

Input: [1,0,1,0,1]
Output: 1
Explanation: 
There are 3 ways to group all 1's together:
[1,1,1,0,0] using 1 swap.
[0,1,1,1,0] using 2 swaps.
[0,0,1,1,1] using 1 swap.
The minimum is 1.
Example 2:

Input: [0,0,0,1,0]
Output: 0
Explanation: 
Since there is only one 1 in the array, no swaps needed.
Example 3:

Input: [1,0,1,0,1,0,0,1,1,0,1]
Output: 3
Explanation: 
One possible solution that uses 3 swaps is [0,0,0,0,0,1,1,1,1,1,1].
 

Note:

1 <= data.length <= 10^5
0 <= data[i] <= 1

#### Solutions

1. ##### window

```c++
class Solution {
public:
    int minSwaps(vector<int>& data) {
        int num1 = 0;
        for (auto n : data) num1 += n == 1;

        int numzero = 0;
        for (int i = 0; i < num1; i++)
            numzero += data[i] == 0;
        
        int res = numzero;
        // or
        // res = min(res, numzero += !data[i] - !data[i - num1]);
        for (int i = num1; i < data.size(); i++) {
            if (data[i - num1] == 0) numzero--;
            if (data[i] == 0) numzero++;
            res = min(res, numzero);
        }

        return res;
    }
};
```