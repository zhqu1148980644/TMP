#### Given integers n and k, find the lexicographically k-th smallest integer in the range from 1 to n.

#### Note: 1 ≤ k ≤ n ≤ 109.

```
Example:

Input:
n: 13   k: 2

Output:
10
```

#### Explanation:
The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.

#### Solutions

1. ##### denary tree(10 child of each node)

- The k'th smallest integer in lexicographical order equals to the k'th node in preorder traversal of the denary tree.
    - Actually is the path from root to the k'th node.
- The first level has 9 node ranging from `1 to 9` and every nodes contains 10 child nodes ranging from `0 to 9`.
- To speed up the traversal process, we can just count the total number of nodes belongs to a given node(subtree), and skip to the next node in the same level if the total number of nodes is smaller than the remaining foward steps, or jump to the left most child vise versa.
- When counting the total number of subnodes within a given node(or a prefix), we must take into consideration of the maximum number provided by the problem.
    - Basically, the counting strategy is to count the number of nodes in each level. 10 * 10 * 10 ......
    - For example, we are at the node `1` and the next node is `2 `. The second level contains 10 nodes(10-20), the third level contains 100 nodes(10 + 100) ....


```c++
class Solution {
public:
    long steps(long prefix, long maximum) {
        long count = 0;
        long next_prefix = prefix + 1;
        while (prefix <= maximum) {
            count += min(maximum + 1 - prefix, next_prefix - prefix);
            prefix *= 10;
            next_prefix *= 10;
        }

        return count;
    }

    int findKthNumber(int n, int k) {
        long cur_steps = 1;
        int prefix = 1;

        while (cur_steps < k) {
            // there are next_steps number of nodes in this tree(include self)
            long next_steps = steps(prefix, n);
            // the target node must be within the current subtree, move to the left most child, increase 1 step. e.g 2 -> 20 or  42 -> 420
            if (cur_steps + next_steps > k) {
                prefix *= 10;
                cur_steps += 1;
            // else jump to the next node in the current level and emulate we have moved forward next_steps steps.
            } else {
                prefix += 1;
                cur_steps += next_steps;
            }
        }
        return prefix;
    }
};
```