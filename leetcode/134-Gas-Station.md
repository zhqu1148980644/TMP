#### There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1.

#### Note:

- If there exists a solution, it is guaranteed to be unique.
- Both input arrays are non-empty and have the same length.
- Each element in the input arrays is a non-negative integer.

```
Example 1:

Input: 
gas  = [1,2,3,4,5]
cost = [3,4,5,1,2]

Output: 3

Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.
Example 2:

Input: 
gas  = [2,3,4]
cost = [3,4,3]

Output: -1

Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.
```

#### Solutions

1. ##### straight forward

- The naive way is to start at every gas station, and check if we can travel around and come back to the same station.
- Suppose we start at `s[i]` and the farmost gas station we can get is `s[j]`, then start at any gas station between `s[i: j]` will not get to `s[j + 1]`.
    - When we arrived at `s[k]` with `i < k <= j` starting from `s[i]`, then the current gas tank we have will be `g[k] + left`  `left >= 0`, if we choose to start at `s[k]`, the gas tank at initial will merely be `g[k]` which is less/equal than the previous situation, how could we get to gas station farther then `s[j]`.
- So, we can choose the gas station next to the farmost gas station we can reach as the new starting station.

```c++
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // total_gas >= 0 ensures gas >= 0 during the whole trip.
        // cur_gas >= 0 ensures gas >=  0 duting the left trip starting at start.
        int total_gas, cur_gas, start;
        total_gas = cur_gas = start = 0;
        for (int i = 0; i < gas.size(); i++) {
            total_gas += gas[i] - cost[i];
            cur_gas += gas[i] - cost[i];
            if (cur_gas < 0) {
                start = i + 1;
                cur_gas = 0;
            }
        }
        return total_gas >= 0 ? start : -1;
    }
};
```

- In another perspective.
- reference: https://leetcode-cn.com/problems/gas-station/solution/shi-yong-tu-de-si-xiang-fen-xi-gai-wen-ti-by-cyayc/
- Aggregating gas unit debt(`gas[i] - cost[i]`) for every gas station, and choose the gas station next to the gas station with the lowest(negative) debt as the starting station.
    - Explanation: To ensure gas not be negative at all time, we need to move the gas ubunt debt line up, till the lowest debt(negative) increases to greater than or equal to 0. Since all debts after the pivot is higher than the pivot, which means the gas unit is aggregating after the pivot and the aggregated gas unit may be larger enough to pull up(added up in the first station) the whole line across zero.

```c++
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int mindebt = 0;
        int mindevts = -1;
        int gassum = 0;

        for (int i = 0; i < gas.size(); i++) {
            gassum += gas[i] - cost[i];
            if (gassum < mindebt) {
                mindebt = gassum;
                mindevts = i;
            }
        }
        return gassum >= 0 ? mindevts + 1 : -1;
    }
};
```
