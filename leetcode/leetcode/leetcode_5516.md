---
title: Alert Using Same Key Card Three or More Times in a One Hour Perio
date: 2021-01-04
---
Leetcode company workers use key-cards to unlock office doors. Each time a worker uses their key-card, the security system saves the worker's name and the time when it was used. The system emits an alert if any worker uses the key-card three or more times in a one-hour period.

You are given a list of strings keyName and keyTime where [keyName[i], keyTime[i]] corresponds to a person's name and the time when their key-card was used in a single day.

Access times are given in the 24-hour time format "HH:MM", such as "23:51" and "09:49".

Return a list of unique worker names who received an alert for frequent keycard use. Sort the names in ascending order alphabetically.

Notice that "10:00" - "11:00" is considered to be within a one-hour period, while "23:51" - "00:10" is not considered to be within a one-hour period.

 

Example 1:

Input: keyName = ["daniel","daniel","daniel","luis","luis","luis","luis"], keyTime = ["10:00","10:40","11:00","09:00","11:00","13:00","15:00"]
Output: ["daniel"]
Explanation: "daniel" used the keycard 3 times in a one-hour period ("10:00","10:40", "11:00").
Example 2:

Input: keyName = ["alice","alice","alice","bob","bob","bob","bob"], keyTime = ["12:01","12:00","18:00","21:00","21:20","21:30","23:00"]
Output: ["bob"]
Explanation: "bob" used the keycard 3 times in a one-hour period ("21:00","21:20", "21:30").
Example 3:

Input: keyName = ["john","john","john"], keyTime = ["23:58","23:59","00:01"]
Output: []
Example 4:

Input: keyName = ["leslie","leslie","leslie","clare","clare","clare","clare"], keyTime = ["13:00","13:20","14:00","18:00","18:51","19:30","19:49"]
Output: ["clare","leslie"]
 

Constraints:

1 <= keyName.length, keyTime.length <= 105
keyName.length == keyTime.length
keyTime are in the format "HH:MM".
[keyName[i], keyTime[i]] is unique.
1 <= keyName[i].length <= 10
keyName[i] contains only lowercase English letters.


#### Solutions

1. ##### discretization with treemap

```cpp
class Solution {
public:
    int get_time(const string & s) {
        int h, m;
        sscanf(s.c_str(), "%d:%d", &h, &m);
        return h * 60 + m;
    }
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        unordered_map<string_view, map<int, int>> m;
        const int MAXTIME =  60 * 60;
        
        for (int i = 0; i < keyName.size(); i++) {
            auto & name = keyName[i];
            int time = get_time(keyTime[i]);
            auto & times = m[name];
            times[time]++;
            if (time + 60 + 1 < MAXTIME)
                times[time + 60 + 1]--;
        }
        
        vector<string> bad;
        for (auto & [name, times] : m) {
            int num = 0;
            for (auto [_, n] : times) {
                if ((num += n) >= 3) {
                    bad.push_back(string(name));
                    break;
                }
            }
        }

        sort(bad.begin(), bad.end());
        return bad;
    }
};
```