On a single threaded CPU, we execute some functions.  Each function has a unique id between 0 and N-1.

We store logs in timestamp order that describe when a function is entered or exited.

Each log is a string with this format: "{function_id}:{"start" | "end"}:{timestamp}".  For example, "0:start:3" means the function with id 0 started at the beginning of timestamp 3.  "1:end:2" means the function with id 1 ended at the end of timestamp 2.

A function's exclusive time is the number of units of time spent in this function.  Note that this does not include any recursive calls to child functions.

The CPU is single threaded which means that only one function is being executed at a given time unit.

Return the exclusive time of each function, sorted by their function id.

 

Example 1:



Input:
n = 2
logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
Output: [3, 4]
Explanation:
Function 0 starts at the beginning of time 0, then it executes 2 units of time and reaches the end of time 1.
Now function 1 starts at the beginning of time 2, executes 4 units of time and ends at time 5.
Function 0 is running again at the beginning of time 6, and also ends at the end of time 6, thus executing for 1 unit of time. 
So function 0 spends 2 + 1 = 3 units of total time executing, and function 1 spends 4 units of total time executing.
 

Note:

1 <= n <= 100
Two functions won't start or end at the same time.
Functions will always log when they exit.

#### Solutions

1. ##### stack

```c++
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        stack<pair<int, int>> s;
        vector<int> res(n);
        int id, t, prev = 0;
        for (auto & log : logs) {
            bool istart = log.find("start") != -1;
            sscanf(log.c_str(), istart ? "%d:start:%d" : "%d:end:%d", &id, &t);
            
            if (!s.empty()) {
                auto & [preid, prelen] = s.top();
                prelen += t - prev + (!istart);
                if (!istart && preid == id) {
                    res[preid] += prelen;
                    s.pop();
                }
            }
            if (istart) s.emplace(id, 0);
            prev = istart ? t : t + 1;
        }

        return res;
    }
};
```

or

```c++
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        stack<int> s;
        vector<int> res(n);
        int id, t, prev = 0;
        for (auto & log : logs) {
            bool istart = log.find("start") != -1;
            sscanf(log.c_str(), istart ? "%d:start:%d" : "%d:end:%d", &id, &t);
            
            if (!s.empty()) {
                auto & preid = s.top();
                res[preid] += t - prev + (!istart);
                // case when 0:start:0 0:start:10 0:end:12, the second run should not pop out the first run
                if (!istart && preid == id)
                    s.pop();
            }
            if (istart) s.push(id);
            // prev is the first occupied time.
            prev = istart ? t : t + 1;
        }

        return res;
    }
};
```