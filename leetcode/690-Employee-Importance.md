You are given a data structure of employee information, which includes the employee's unique id, their importance value and their direct subordinates' id.

For example, employee 1 is the leader of employee 2, and employee 2 is the leader of employee 3. They have importance value 15, 10 and 5, respectively. Then employee 1 has a data structure like [1, 15, [2]], and employee 2 has [2, 10, [3]], and employee 3 has [3, 5, []]. Note that although employee 3 is also a subordinate of employee 1, the relationship is not direct.

Now given the employee information of a company, and an employee id, you need to return the total importance value of this employee and all their subordinates.

Example 1:

Input: [[1, 5, [2, 3]], [2, 3, []], [3, 3, []]], 1
Output: 11
Explanation:
Employee 1 has importance value 5, and he has two direct subordinates: employee 2 and employee 3. They both have importance value 3. So the total importance value of employee 1 is 5 + 3 + 3 = 11.
 

Note:

One employee has at most one direct leader and may have several subordinates.
The maximum number of employees won't exceed 2000.

#### Solutions


1. ##### dfs

```c++
/*
// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
*/

class Solution {
public:
    int sum(unordered_map<int, pair<int, vector<int> *>> & m, int id) {
        int res = m[id].first;
        for (auto oid : *(m[id].second))
            res += sum(m, oid);
        return res;
    }
    int getImportance(vector<Employee*> employees, int id) {
        unordered_map<int, pair<int, vector<int> *>> m;
        for (auto e :  employees)
            m[e->id] = {e->importance, &(e->subordinates)};

        return sum(m, id);
    }
};
```

or

```c++
class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        int res = 0;
        for (auto pe : employees)
            if (pe->id == id) {
                res += pe->importance;
                for (auto oid : pe->subordinates)
                    res += getImportance(employees, oid);
                break;
            }
        return res;
    }
};
```

2. ##### bfs

```c++
class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        unordered_map<int, pair<int, vector<int> *>> m;
        for (auto e :  employees)
            m[e->id] = {e->importance, &(e->subordinates)};

        queue<int> q; q.push(id);
        int res = 0;
        while (!q.empty()) {
            id = q.front(); q.pop();
            res += m[id].first;
            for (auto oid : *(m[id].second))
                q.push(oid);
        }

        return res;
    }
};
```