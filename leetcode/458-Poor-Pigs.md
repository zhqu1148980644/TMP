There are 1000 buckets, one and only one of them is poisonous, while the rest are filled with water. They all look identical. If a pig drinks the poison it will die within 15 minutes. What is the minimum amount of pigs you need to figure out which bucket is poisonous within one hour?

Answer this question, and write an algorithm for the general case.

 

#### General case:

If there are n buckets and a pig drinking poison will die within m minutes, how many pigs (x) you need to figure out the poisonous bucket within p minutes? There is exactly one bucket with poison.

 

#### Note:

-    A pig can be allowed to drink simultaneously on as many buckets as one would like, and the feeding takes no time.
-    After a pig has instantly finished drinking buckets, there has to be a cool down time of m minutes. During this time, only observation is allowed and no feedings at all.
-    Any given bucket can be sampled an infinite number of times (by an unlimited number of pigs).


#### Solutions

1. ##### math

- reference: the official answer.
- For simplicity, suppose `minutesToDie` is `4` and `minutesToTest` is `2` and there is only `one` pig, how many buckets can we test?
    - There are `three` possibilities: 
    - Drink the first bucket and `die in minutes 4`. The answer is bucket 1
    - Then drink the second bucket in `2` and and `die in 6`. The answer is bucket 2
    - Or this pig is `still alive`. The answer is bucket 3
- Follow the same rule, there are `(minutesToDie/minutesToTest) + 1(still alive)` states thus we can test at most this number of buckets with one pig.
- For `x` pigs, the number is `nstates**x`
- Thus in order to test n buckets, we need to ensure that `ntates**x >= n`.

```c++
class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest){
        int states = minutesToTest / minutesToDie + 1;
        return ceil(log(buckets) / log(states));
    }
};
```