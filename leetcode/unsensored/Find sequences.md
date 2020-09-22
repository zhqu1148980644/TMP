There are two 1, two 2, ... two n in a sequence of numbers. Find if there exists any permutations such that the number of of elements between two identical number `n` equals to `n`.

For example: `n` is 4, then `41312432` satisfies the requirement.


#### Solutions

1. ##### dfs

```c++
vector<int> solve(int n) {
    vector<int> used(n + 1), res(2 * n, -1);

    function<bool(int)> find = [&](int i) {
        if (i == 2 * n) return true;
        if (res[i] != -1) return find(i + 1);

        for (int num = 1; num <= n; num++) {
            int next = i + num + 1;
            if (used[num]
                || next >= 2 * n
                || res[next] != -1) continue;
            used[num] = true;
            res[i] = res[next] = num;
            if (find(i + 1))
                return true;
            res[i] = res[next] = -1;
            used[num] = false;
        }
        return false;
    };
    find(0);
    return res;
}

int main() {
    int n; cin >> n;
    cout << solve(n) << endl;
}
```