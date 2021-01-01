Suppose you have a long flowerbed in which some of the plots are planted and some are not. However, flowers cannot be planted in adjacent plots - they would compete for water and both would die.

Given a flowerbed (represented as an array containing 0 and 1, where 0 means empty and 1 means not empty), and a number n, return if n new flowers can be planted in it without violating the no-adjacent-flowers rule.

Example 1:
Input: flowerbed = [1,0,0,0,1], n = 1
Output: True
Example 2:
Input: flowerbed = [1,0,0,0,1], n = 2
Output: False
Note:
The input array won't violate no-adjacent-flowers rule.
The input array size is in the range of [1, 20000].
n is a non-negative integer which won't exceed the input array size.

##### Solutions


1. ##### straight forward

- Two cases need to be taken care of specifically:
    - `0000***`
    - `***0000`

```c++
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        if (!flowerbed.size()) return false;

        int i = flowerbed[0] == 0 ? -1 : 0, j;
        for (j = 0; j < flowerbed.size() && n > 0; j++)
            if (flowerbed[j] == 1) {
                if (j - i > 1)
                    n -= (j - i - 1) / 2;
                i = j + 1;
            }
        if (flowerbed.back() == 0)
            n -= (j - i) / 2;

        return n <= 0;
    }
};
```


or count the number of `0`

```c++
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        flowerbed.push_back(0); flowerbed.push_back(1);
        int len = flowerbed[0] == 0 ? 1 : 0;
        
        for (auto num : flowerbed) {
            if (num == 1) {
                if (len > 2)
                    n -= (len - 1) / 2;
                len = 0;
            }
            else
                len++;
            if (n <= 0) break;
        }
        
        return n <= 0;
    }
};
```


```rust
impl Solution {
    pub fn can_place_flowers(mut nums: Vec<i32>, mut n: i32) -> bool {
        nums.push(0); nums.push(1);        
        let mut zero = if nums[0] == 0  {1} else {0};
        for i in 0..nums.len() {
            if nums[i] == 1 {
                n -= (zero - 1) / 2;
                zero = 0;
            } else {
                zero += 1;
            }
            if n <= 0 {
                break;
            }
        }
        n <= 0
    }
}
```