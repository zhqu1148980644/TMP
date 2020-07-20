#### Given a list accounts, each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some email that is common to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.

```
Example 1:

Input: 
accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
Explanation: 
The first and third John's are the same person as they have the common email "johnsmith@mail.com".
The second John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
```

#### Note:
- The length of accounts will be in the range [1, 1000].
- The length of accounts[i] will be in the range [1, 10].
- The length of accounts[i][j] will be in the range [1, 30].


#### Solutions

- Treats emails as a graph.

1. ##### Union Find

```c++
class UnionFind {
private:
    vector<int> nodes, sizes;
public:
    UnionFind(int size) : nodes(size), sizes(size, 1){
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        while (nodes[node] != node)
            node = nodes[node] = nodes[nodes[node]];
        return node;
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1);
        int f2 = find(node2);
        if (f1 == f2)
            return false;
        else {
            if (sizes[f1] > sizes[f2])
                swap(f1, f2);
            nodes[f1] = f2;
            sizes[f2] += sizes[f1];
            return true;
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, int> email2id;
        UnionFind uf(accounts.size());
         // iterate over all emails, and connect users with same emails.
        for (int id = 0; id < accounts.size(); id++) {
            auto & acc = accounts[id];
            for (int i = 1; i < acc.size(); i++) {
                auto & e = acc[i];
                if (!email2id.count(e))
                    email2id[e] = id;
                uf.merge(email2id[e], email2id[acc[1]]);
            }
        }
        // collect emails based on email's id.
        unordered_map<int, vector<string>> users;
        for (auto & [e, id] : email2id)
            users[uf.find(id)].push_back(e);
        // reverse sort
        for (auto & [id, emails] : users)
            sort(emails.rbegin(), emails.rend());
        // build result
        vector<vector<string>> res;
        for (auto & [id, emails] : users) {
            emails.push_back(accounts[id][0]);
            reverse(emails.begin(), emails.end());
            res.push_back(move(emails));
        }

        return res;
    }
};
```


2. ##### dfs

- Build the adjacency matrix and use dfs to find all connected components.

```c++
class Solution {
public:
    unordered_map<string, vector<int>> g;
    unordered_set<string> visitede;
    vector<bool> visitedp;
    void append(vector<string> & emails, vector<vector<string>> & accounts, int curp) {
        for (int i = 1; i < accounts[curp].size(); i++) {
            auto & e = accounts[curp][i];
            if (visitede.count(e)) continue;
            emails.push_back(e);
            visitede.insert(e);
            for (auto p : g[e]) {
                if (visitedp[p]) continue;
                visitedp[p] = true;
                append(emails, accounts, p);
            }
        }
    }
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        for (int i = 0; i < accounts.size(); i++)
            for (int j = 1; j < accounts[i].size(); j++) {
                g[accounts[i][j]].push_back(i);
            }
        
        visitedp = vector<bool>(accounts.size());
        vector<vector<string>> res;
        for (int i = 0; i < accounts.size(); i++) {
            if (visitedp[i]) continue;
            vector<string> emails;
            visitedp[i] = true;
            append(emails, accounts, i);
            sort(emails.begin(), emails.end());
            res.emplace_back(emails.size() + 1);
            res.back()[0] = accounts[i][0];
            for (int i = 0; i < emails.size(); i++)
                res.back()[i + 1] = move(emails[i]);
        }

        return res;
    }
};
```

or use only one hashset

```c++
class Solution {
public:
    unordered_map<string, vector<int>> g;
    unordered_set<string> visited;
    void append(vector<string> & emails, vector<vector<string>> & accounts, int curp) {
        for (int i = 1; i < accounts[curp].size(); i++) {
            auto & e = accounts[curp][i];
            if (visited.count(e)) continue;
            emails.push_back(e);
            visited.insert(e);
            for (auto p : g[e])
                append(emails, accounts, p);
        }
    }
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        for (int i = 0; i < accounts.size(); i++)
            for (int j = 1; j < accounts[i].size(); j++) {
                g[accounts[i][j]].push_back(i);
            }
        
        vector<vector<string>> res;
        for (int i = 0; i < accounts.size(); i++) {
            vector<string> emails;
            append(emails, accounts, i);
            if (emails.empty() && accounts[i].size()) continue;
            sort(emails.rbegin(), emails.rend());
            emails.push_back(accounts[i][0]);
            reverse(emails.begin(), emails.end());
            res.push_back(move(emails));
        }

        return res;
    }
};
```

python version borrowed from the official answer.

```python
class Solution:
    def accountsMerge(self, accounts: List[List[str]]) -> List[List[str]]:
        from collections import defaultdict
        email_name = {}
        graph = defaultdict(set)
        for name, *emails in accounts:
            for email in emails:
                # link the first email to all left emails
                graph[emails[0]].add(email)
                graph[email].add(emails[0])
                email_name[email] = name

        seen, res = set(), []
        for email in  graph:
            if email in seen:
                continue
            seen.add(email)
            s = [email]
            components = []
            while s:
                email = s.pop()
                components.append(email)
                for out in graph[email]:
                    if out in seen:
                        continue
                    seen.add(out)
                    s.append(out)
            res.append([email_name[email]] + sorted(components))

        return res
```
