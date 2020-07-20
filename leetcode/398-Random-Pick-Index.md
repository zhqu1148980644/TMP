Given an array of integers with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.

Note:
The array size can be very large. Solution that uses too much extra space will not pass the judge.

Example:

int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(3);

// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(1);


#### Solutions

1. ##### Reservoir Sampling

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    ListNode * head, * cur;
    Solution(ListNode* head) {
        this->head = cur = head;
    }
    
    /** Returns a random node's value. */
    int getRandom() {
        int cnt = 2;
        cur = head->next;
        int val = head->val;
        while (cur) {
            if (rand() % cnt == 0) val = cur->val;
            cur = cur->next; cnt++;
        }
        return val;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
```

or

```c++
class Solution {
public:
    vector<int> nums;
    Solution(vector<int>& nums) : nums(nums) {
    }

    int pick(int target) {
        int cnt = 0, index = -1;
        for (int i = 0; i < nums.size(); i++)
            if (nums[i] == target) {
                cnt++;
                if (rand() % cnt == 0)
                    index = i;
            }
        return index;
    }
};
```