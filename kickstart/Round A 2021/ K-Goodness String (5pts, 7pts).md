Problem
Charles defines the goodness score of a string as the number of indices i such that Si≠SN−i+1 where 1≤i≤N/2 (1-indexed). For example, the string CABABC has a goodness score of 2 since S2≠S5 and S3≠S4.

Charles gave Ada a string S of length N, consisting of uppercase letters and asked her to convert it into a string with a goodness score of K. In one operation, Ada can change any character in the string to any uppercase letter. Could you help Ada find the minimum number of operations required to transform the given string into a string with goodness score equal to K?

Input
The first line of the input gives the number of test cases, T. T test cases follow.

The first line of each test case contains two integers N and K. The second line of each test case contains a string S of length N, consisting of uppercase letters.

Output
For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the minimum number of operations required to transform the given string S into a string with goodness score equal to K.

Limits
Memory limit: 1 GB.
1≤T≤100.
0≤K≤N/2.
Test Set 1
Time limit: 20 seconds.
1≤N≤100.
Test Set 2
Time limit: 40 seconds.
1≤N≤2×105 for at most 10 test cases.
For the remaining cases, 1≤N≤100.
Sample
Sample Input
save_alt
content_copy
2
5 1
ABCAA
4 2
ABAA
Sample Output
save_alt
content_copy
Case #1: 0
Case #2: 1
In Sample Case #1, the given string already has a goodness score of 1. Therefore the minimum number of operations required is 0.

In Sample Case #2, one option is to change the character at index 1 to B in order to have a goodness score of 2. Therefore, the minimum number of operations required is 1.



#### Solutions

1. ##### straight forward

```c++
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t; cin >> t;
    for (int _i = 0; _i < t; _i++) {
        string s;
        int n, k; cin >> n >> k >> s;
        int cnt = 0;
        for (int i = 0; i < n / 2; i++)
            if (s[i] != s[s.size() - i - 1])
                cnt++;
        cout << "Case #" << (_i + 1) << ": " << abs(k - cnt) << endl;
    }

}
```