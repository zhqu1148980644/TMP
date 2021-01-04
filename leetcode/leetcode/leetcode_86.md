---
title: Partition List
date: 2021-01-04
---
#### Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

```
Example:

Input: head = 1->4->3->2->5->2, x = 3
Output: 1->2->2->4->3->5
```

#### Solutions

1. ##### two dummy heads

- use two dummy heads to store nodes with values smaller than x and larger than x respectively.

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode node;
struct ListNode* partition(struct ListNode* head, int x){
    node small = {0, NULL}; node large = {0, NULL};
    node * psmall = &small;
    node * plarge = &large;
    while (head) {
        if (head->val < x) {
            psmall->next = head;
            psmall = psmall->next;
        } else {
            plarge->next = head;
            plarge = plarge->next;
        }
        head = head->next;
    }
    psmall->next = large.next;
    plarge->next = NULL;
    return small.next;
}
```

```rust
// Definition for singly-linked list.
// #[derive(PartialEq, Eq, Clone, Debug)]
// pub struct ListNode {
//   pub val: i32,
//   pub next: Option<Box<ListNode>>
// }
// 
// impl ListNode {
//   #[inline]
//   fn new(val: i32) -> Self {
//     ListNode {
//       next: None,
//       val
//     }
//   }
// }


impl Solution {
    pub fn partition(mut head: Option<Box<ListNode>>, x: i32) -> Option<Box<ListNode>> {
        let (mut lt, mut gt) = (ListNode::new(-1), ListNode::new(-1));
        let (mut plt, mut pgt) = (&mut lt, &mut gt);
        while let Some(cur) = head {
            if cur.val < x {
                plt.next = Some(cur);
                plt = plt.next.as_mut().unwrap();
                head = plt.next.take();
            }
            else {
                pgt.next = Some(cur);
                pgt = pgt.next.as_mut().unwrap();
                head = pgt.next.take();
            }
        }
        plt.next = gt.next;
        lt.next
    }
}
```

2. ##### insertion

- Create a dummy head
- Whenever meets a node with value smaller than the target x, insert this node after the dummy head.