#### Given an integer array sorted in non-decreasing order, there is exactly one integer in the array that occurs more than 25% of the time.

Return that integer.

 

```
Example 1:

Input: arr = [1,2,2,6,6,6,6,7,10]
Output: 6
```
 

#### Constraints:

- 1 <= arr.length <= 10^4
- 0 <= arr[i] <= 10^5


#### Solutions

1. ##### one pass

```c++
int findSpecialInteger(int * arr, int arrSize) {
    int count = 1;
    for (int i = 1; i < arrSize; i++) {
        count = (arr[i] == arr[i - 1]) ? count + 1 : 1;
        if (count > arrSize / 4)
            return arr[i];
    }
    return arr[arrSize - 1];
}
```

or

```c++
class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        int exp = arr.size() / 4, len = 0;

        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] != arr[i - 1])
                len = 0;
            if (++len > exp)
                return arr[i];
        }

        return arr.back();
    }
};
```