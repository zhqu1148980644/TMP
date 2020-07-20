We are given an array asteroids of integers representing asteroids in a row.

For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

Example 1:
Input: 
asteroids = [5, 10, -5]
Output: [5, 10]
Explanation: 
The 10 and -5 collide resulting in 10.  The 5 and 10 never collide.
Example 2:
Input: 
asteroids = [8, -8]
Output: []
Explanation: 
The 8 and -8 collide exploding each other.
Example 3:
Input: 
asteroids = [10, 2, -5]
Output: [10]
Explanation: 
The 2 and -5 collide resulting in -5.  The 10 and -5 collide resulting in 10.
Example 4:
Input: 
asteroids = [-2, -1, 1, 2]
Output: [-2, -1, 1, 2]
Explanation: 
The -2 and -1 are moving left, while the 1 and 2 are moving right.
Asteroids moving the same direction never meet, so no asteroids will meet each other.
Note:

The length of asteroids will be at most 10000.
Each asteroid will be a non-zero integer in the range [-1000, 1000]..

#### Solutions

1. ##### stack

- Use a virtual `guardian(INT_MIN)` to prevent handling the difference between `equal(both explode) and greater(only the negative asteroid would explode)`.

```c++
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> s; s.push(INT_MIN);
        for (auto n : asteroids) {
            if (n < 0) {
                while (s.top() > 0 && s.top() < -n)
                    s.pop();
                if (s.top() < 0)
                    s.push(n);
                else if (s.top() == -n)
                    s.pop();
            }
            else
                s.push(n);
        }

        vector<int> res;
        while (s.size() != 1) {
            res.push_back(s.top());
            s.pop();
        }

        return {res.rbegin(), res.rend()};
    }
};
```

More intricate solution without guardian

```c++
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> s;
        for (auto n : asteroids) {
            if (n < 0) {
                int num = 0;
                while (!s.empty() && s.top() > 0 && s.top() < -n) {
                    s.pop();
                }
                if (s.empty() || s.top() < 0)
                    s.push(n);
                else if (!s.empty() && s.top() == -n)
                    s.pop();
            }
            else
                s.push(n);
        }

        vector<int> res;
        while (!s.empty()) {
            res.push_back(s.top());
            s.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
```