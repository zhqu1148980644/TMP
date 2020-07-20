#### Winter is coming! Your first job during the contest is to design a standard heater with fixed warm radius to warm all the houses.

Now, you are given positions of houses and heaters on a horizontal line, find out minimum radius of heaters so that all houses could be covered by those heaters.

So, your input will be the positions of houses and heaters seperately, and your expected output will be the minimum radius standard of heaters.

#### Note:

-    Numbers of houses and heaters you are given are non-negative and will not exceed 25000.
-    Positions of houses and heaters you are given are non-negative and will not exceed 10^9.
-    As long as a house is in the heaters' warm radius range, it can be warmed.
-    All the heaters follow your radius standard and the warm radius will the same.

 

```
Example 1:

Input: [1,2,3],[2]
Output: 1
Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.

 

Example 2:

Input: [1,2,3,4],[1,4]
Output: 1
Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be warmed.
```

#### Solutions

1. ##### binary search O(2nlog(n))

- For each house find the closest neighbor heater and update the minimum radius needed to cater for this house.

```c++
class Solution {
public:
    int binary_search(vector<int> & heaters, int target) {
        int lo = 0, hi = heaters.size() - 1;
        if (target > heaters[hi])
            return hi + 1;
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            if (heaters[mid] < target)
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
    }
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int maxdis = 0;
        if (heaters.size() == 1) {
            for (auto house : houses)
                maxdis = max(abs(house - heaters[0]), maxdis);
            return maxdis;
        }

        sort(heaters.begin(), heaters.end());

        int len = heaters.size(), dis;
        for (auto & house : houses) {
            int find = binary_search(heaters, house);

            if (find >= len)
                maxdis = max(maxdis, house - heaters[len - 1]);
            else if (heaters[find] != house) {
                if (find == 0)
                    dis = heaters[0] - house;
                else
                    dis = min(heaters[find] - house, house - heaters[find - 1]);
                maxdis = max(maxdis, dis);
            }
        }

        return maxdis;

    }
};
```

or

```c++
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int maxdis = 0;
        if (heaters.size() == 1) {
            for (auto house : houses)
                maxdis = max(abs(house - heaters[0]), maxdis);
            return maxdis;
        }
        sort(heaters.begin(), heaters.end());
        int len = heaters.size(), dis = 0;
        for (auto & house : houses) {
            auto find = lower_bound(heaters.begin(), heaters.end(), house);
            if (find == heaters.end())
                maxdis = max(maxdis, house - heaters.back());
            else if (*find != house) {
                if (find == heaters.begin())
                    dis = heaters[0] - house;
                else
                    dis = min(*find - house, house - *prev(find));
                maxdis = max(dis, maxdis);
            }
        }
        return maxdis;
    }
};
```


2. ##### two pointers O(2nlog(n))

- Sort both houses and heaters.

```c++
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());

        int i = 0, h = 0;
        int maxdis = 0, lenh = houses.size(), lenhe = heaters.size();
        while (i < lenh && h < lenhe) {
            if (houses[i] <= heaters[h]) {
                int dis = min(heaters[h] - houses[i],
                              h > 0 ? houses[i] - heaters[h - 1] : INT_MAX);
                maxdis = max(maxdis, dis);
                i++;
                // skip all house with smaller absolute distance
                while (i < lenh && abs(heaters[h] - houses[i]) < dis) i++;
            }
            else
                h++;
        }
        // when i < lenh, means the last heater is smaller than last house, it has been poassed in the while loop
        if (i < lenh)
            maxdis = max(maxdis, houses[lenh - 1] - heaters[lenhe - 1]);
        return maxdis;
    }
};
```