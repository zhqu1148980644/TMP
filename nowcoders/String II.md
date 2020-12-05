https://ac.nowcoder.com/acm/contest/9716/A

#### Solutions

1. ##### greedy O(n)

- Iterate over all 26 characters in the final subsequence.
- Prefer to operate characters with less steps(number of opeations).

```c++
class Solution {
public:
    /**
     * 
     * @param k int整型 表示最多的操作次数
     * @param s string字符串 表示一个仅包含小写字母的字符串
     * @return int整型
     */
    int string2(int k, string s) {
        vector<int> count(26);
        for (auto c : s) count[c - 'a']++;

        int res = 0;
        for (auto c = 0; c < 26; c++) {
            vector<pair<int, int>> steps;    
            int cur = count[c];
            for (auto nc = 0; nc < 26; nc++) {
                if (nc == c) continue;
                steps.emplace_back({abs(c - nc), count[nc]});
            }
            // sort steps compared to the current character in ascending order.
            sort(steps.begin(), steps.end());
            int remain = k;
            // operate till k reduce to 0.
            for (auto [step, cnt] : steps) {
                int used =  min(remain /step, cnt);
                cur += used;
                remain -= used * step;
                if (remain <= 0) break;
            }
            res = max(res, cur);
        }
        return res;
    }
};
```