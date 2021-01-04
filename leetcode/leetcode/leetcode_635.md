---
title: Design Log Storage Syste
date: 2021-01-04
---
You are given several logs that each log contains a unique id and timestamp. Timestamp is a string that has the following format: Year:Month:Day:Hour:Minute:Second, for example, 2017:01:01:23:59:59. All domains are zero-padded decimal numbers.

Design a log storage system to implement the following functions:

void Put(int id, string timestamp): Given a log's unique id and timestamp, store the log in your storage system.


int[] Retrieve(String start, String end, String granularity): Return the id of logs whose timestamps are within the range from start to end. Start and end all have the same format as timestamp. However, granularity means the time level for consideration. For example, start = "2017:01:01:23:59:59", end = "2017:01:02:23:59:59", granularity = "Day", it means that we need to find the logs within the range from Jan. 1st 2017 to Jan. 2nd 2017.

Example 1:
put(1, "2017:01:01:23:59:59");
put(2, "2017:01:01:22:59:59");
put(3, "2016:01:01:00:00:00");
retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Year"); // return [1,2,3], because you need to return all logs within 2016 and 2017.
retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Hour"); // return [1,2], because you need to return all logs start from 2016:01:01:01 to 2017:01:01:23, where log 3 is left outside the range.
Note:
There will be at most 300 operations of Put or Retrieve.
Year ranges from [2000,2017]. Hour ranges from [00,23].
Output for Retrieve has no order required.

#### Soltuions

1. ##### convert timestamp to int

- Note that `Month` and `day` are both 1-based, all timestamps will not be uniquely mapped to intergers if we choose to represent `M/D` with `12 x *` and `31 x *`. ie: either convert `M/D` to 0-based or plus unit by `1`(13 X *).

```cpp
class LogSystem {
public:
    map<int, int> m;
    LogSystem() {

    }
    unordered_map<string, int> gramp {{"Year", 0}, {"Month", 1}, {"Day", 2}, {"", 5},
                                      {"Hour", 3}, {"Minute", 4}, {"Second", 5}};
    const vector<int> tv {13 * 32 * 24 * 60 * 60, 32 * 24 * 60 * 60, 
                                 24 * 60 * 60, 60 * 60, 60, 1};
    int convert(string & timestamp, const string & gra = "", bool isend = false) {
        vector<int> t(6);
        sscanf(timestamp.c_str(), "%d:%d:%d:%d:%d:%d", 
            &t[0], &t[1], &t[2], &t[3], &t[4],  &t[5]);
        t[0] -= 1999;
        int maxi = gramp[gra];
        if (gra.size() && isend)
            t[maxi] += 1;
        int time = 0;
        for (int i = 0; i <= maxi; i++)
            time += t[i] * tv[i];
        return time;
    }
    void put(int id, string timestamp) {
        m[convert(timestamp)] = id;
    }
    
    vector<int> retrieve(string s, string e, string gra) {
        int st = convert(s, gra), ed = convert(e, gra, true);
        auto lo = m.lower_bound(st), hi = m.lower_bound(ed);
        vector<int> res;
        while (lo != hi) {
            res.push_back(lo->second);
            lo++;
        }
        return res;
    }
};

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem* obj = new LogSystem();
 * obj->put(id,timestamp);
 * vector<int> param_2 = obj->retrieve(s,e,gra);
 */
```