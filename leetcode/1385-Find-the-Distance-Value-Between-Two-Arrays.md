Given two integer arrays arr1 and arr2, and the integer d, return the distance value between the two arrays.

The distance value is defined as the number of elements arr1[i] such that there is not any element arr2[j] where |arr1[i]-arr2[j]| <= d.

 

```
Example 1:

Input: arr1 = [4,5,8], arr2 = [10,9,1,8], d = 2
Output: 2
Explanation: 
For arr1[0]=4 we have: 
|4-10|=6 > d=2 
|4-9|=5 > d=2 
|4-1|=3 > d=2 
|4-8|=4 > d=2 
For arr1[1]=5 we have: 
|5-10|=5 > d=2 
|5-9|=4 > d=2 
|5-1|=4 > d=2 
|5-8|=3 > d=2
For arr1[2]=8 we have:
|8-10|=2 <= d=2
|8-9|=1 <= d=2
|8-1|=7 > d=2
|8-8|=0 <= d=2

Example 2:

Input: arr1 = [1,4,2,3], arr2 = [-4,-3,6,10,20,30], d = 3
Output: 2

Example 3:

Input: arr1 = [2,1,100,3], arr2 = [-5,-2,10,-3,7], d = 6
Output: 1
```

 

#### Constraints:

    1 <= arr1.length, arr2.length <= 500
    -10^3 <= arr1[i], arr2[j] <= 10^3
    0 <= d <= 100


#### Solutions

1. ##### straight forward O(n2)

```cpp
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int res = 0;
        for (auto n1 : arr1) {
            int valid = true;
            for (auto n2 : arr2)
                if (abs(n1 - n2) <= d) {
                    valid = false;
                    break;
                }
            res += valid;
        }

        return res;
    }
};
```

2. ##### binary search O(n1 * log(n2))

```cpp
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        if (!arr2.size()) return arr1.size();
        sort(arr2.begin(), arr2.end());

        int res = 0;
        for (auto n1 : arr1) {
            auto it = lower_bound(arr2.begin(), arr2.end(), n1);
            if (it == arr2.end())
                res += n1 - arr2.back() > d;
            else if (*it == n1)
                continue;
            else
                res += *it - n1 > d && (it == arr2.begin() || n1 - *--it > d);
        }

        return res;
    }
};
```