Given a date, return the corresponding day of the week for that date.

The input is given as three integers representing the day, month and year respectively.

Return the answer as one of the following values {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}.

 

Example 1:

Input: day = 31, month = 8, year = 2019
Output: "Saturday"
Example 2:

Input: day = 18, month = 7, year = 1999
Output: "Sunday"
Example 3:

Input: day = 15, month = 8, year = 1993
Output: "Sunday"
 

Constraints:

The given dates are valid dates between the years 1971 and 2100.

#### Solutions

1. ##### api

```python
class Solution:
    def dayOfTheWeek(self, day: int, month: int, year: int) -> str:
        import datetime
        return datetime.date(year, month, day).strftime("%A")
```

2. ##### straight forward O(year - 1971)

- reference: https://leetcode-cn.com/problems/day-of-the-week/solution/c-fei-mo-fa-jie-fa-by-daxianwa/
- Count the number of days after 1971.1.1(friday).
- Then the answer is `day % 7` + friday.

```c++
class Solution {
public:
    int days_after_197111(int year, int month, int day) {
        vector<int> months {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        // remove the first day 19970101
        int res = (year - 1971) * 365 + day - 1;
        for (int i = 1; i < month; i++)
            res += months[i];
        // add one day for each rune year
        for (int y = 1971; y <= year; y++) {
            if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
                if (y < year || (month > 2))
                    res++;
        }

        return res;
    }

    string dayOfTheWeek(int day, int month, int year) {
        vector<string> weeks = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        int days = days_after_197111(year, month, day);
        return weeks[(4 + days) % 7];
    }
};
```

3. ##### math O(1)

- Kim larsen calculation formula