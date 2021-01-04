---
title: Candy
date: 2021-01-04
---
#### There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

- Each child must have at least one candy.
- Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?

```
Example 1:

Input: [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
Example 2:

Input: [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
             The third child gets 1 candy because it satisfies the above two conditions.
```


#### Solutions

1. ##### two pass

- The first time, scanning from the start to the end, update `candies[i]` to `candies[i - 1] + 1` if `ratings[i] > ratings[i - 1]`. All child will have more candies if their ratings is higher than her left neighbor child.
- The second time, scanning from the end to the start, ensuring the same rule for their right neighbor child.(Only update candies if the required candies are larger than what they already have.)
- Proof of correctness ?

```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        int sumc = 0;
        vector<int> candies(ratings.size(), 1);
        for (int i = 1; i < ratings.size(); i++)
            if (ratings[i] > ratings[i - 1])
                candies[i] = candies[i - 1] + 1;

        sumc += candies[ratings.size() - 1];
        for (int i = ratings.size() - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1])
                candies[i] = max(candies[i], candies[i + 1] + 1);
            sumc += candies[i];
        }

        return sumc;
    }
};
```

2. #####

- reference: https://leetcode.com/problems/candy/discuss/161652/One-pass-O(n)-with-O(1)-space-shortest-solution-easy-to-understand
- The key point: Instead of counting the number of slopes and calculate the sum candies in the `future` like the standard answer did, this method will count the candies whenever meets a increasing rating or a decreasing rating.
    - For an increasing sequence, start from the first child with 1 candy, increase the required number of candies by 1 and add this child's candies into the final sum when passing the increasing sequence. After assined candies for the peak child, we can ensure that any child before the peak kid has been given the right number of candies. Though this peak child's number of candies may be `wrong`, we will fix it later.
    - For a decreasing sequence, since the number of candies for first child of the decreasing sequence has been assigned(In prious increasing sequence, or implicitly assigned by the initial `s`), we will start from the second child with candies 1, and increase candies whenever meets a decreasing rating and plus them into the sum count.
        - For example,  `1 2 3 2 1 0`. we will assign them with candies `1 2 3 1 2 3`, though the decreasing part should be `reversed` as higer rating will get higher candies(reversed: 1 2 3 3 2 1), the sum of the decreasing part will be the `same`. Untill now, every child has been assigned the right number of candies `except for the peak child`. Thus, we increase the number of candies for the peak child by 1 whenever the decreased part is longer then the increase part. There are 2 increased children and three decreased children, thus we assign `one more` candies for the peak child.
- The final assignment of candies for every child can also be fetched in the same way.
    - If the final assignment of candies are need the two pass method should be more proper.


```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        int inc = 1, dec = 1, s = 1;
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1]) {
                // if the previous child is a valley, we reset every thing.
                if (i > 1 && ratings[i - 1] < ratings[i - 2])
                    inc = 1;
                s += ++inc;
                dec = 1;
            }
            else if (ratings[i] < ratings[i - 1]) {
                s += dec++;
                if (dec > inc)
                    s++;
                // can not reset `inc` here. inc needs to be compared with dec
            }
            else {
                s++;
                inc = dec = 1;
            }
        }
        return s;
    }
};
```

