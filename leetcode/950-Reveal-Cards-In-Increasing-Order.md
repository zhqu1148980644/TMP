In a deck of cards, every card has a unique integer.  You can order the deck in any order you want.

Initially, all the cards start face down (unrevealed) in one deck.

Now, you do the following steps repeatedly, until all cards are revealed:

Take the top card of the deck, reveal it, and take it out of the deck.
If there are still cards in the deck, put the next top card of the deck at the bottom of the deck.
If there are still unrevealed cards, go back to step 1.  Otherwise, stop.
Return an ordering of the deck that would reveal the cards in increasing order.

The first entry in the answer is considered to be the top of the deck.

 

Example 1:

Input: [17,13,11,2,3,5,7]
Output: [2,13,3,11,5,17,7]
Explanation: 
We get the deck in the order [17,13,11,2,3,5,7] (this order doesn't matter), and reorder it.
After reordering, the deck starts as [2,13,3,11,5,17,7], where 2 is the top of the deck.
We reveal 2, and move 13 to the bottom.  The deck is now [3,11,5,17,7,13].
We reveal 3, and move 11 to the bottom.  The deck is now [5,17,7,13,11].
We reveal 5, and move 17 to the bottom.  The deck is now [7,13,11,17].
We reveal 7, and move 13 to the bottom.  The deck is now [11,17,13].
We reveal 11, and move 17 to the bottom.  The deck is now [13,17].
We reveal 13, and move 17 to the bottom.  The deck is now [17].
We reveal 17.
Since all the cards revealed are in increasing order, the answer is correct.
 

Note:

1 <= A.length <= 1000
1 <= A[i] <= 10^6
A[i] != A[j] for all i != j

#### Solutions

1. ##### math/simulation

- reference: https://leetcode-cn.com/problems/reveal-cards-in-increasing-order/solution/gong-xian-yi-ge-cde-xie-fa-ben-dan-jian-dan-jiu-xi/
- Reversing the whole process from an empty array.
    - The original order is: 
        - `pop element` from front, array size deduce by 1.
        - pop and put the new front onto the back.
    - The revesed version are:
        - pop and put the back element at the front
        - `push element` at the front, array size  increase by 1.
    - As long as the order of the appding elements are in `decreasing` order, the final array would be the result that could generate the sequence with `increasing` order.


```c++
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        deque<int> dq;
        
        sort(deck.rbegin(), deck.rend());
        for (auto n : deck) {
            if (dq.size()) {
                dq.push_front(dq.back());
                dq.pop_back();
            }
            dq.push_front(n);
        }

        return {dq.begin(), dq.end()};
    }
};
```

2. ##### math

- Put elements in increasing order and skip one empty cell at each iteration.

```c++
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        sort(deck.begin(), deck.end());
        vector<int> res(deck.size());

        int n = deck.size(), r = 0, w = 0;
        while (true) {
            res[w] = deck[r++];
            if (r >= deck.size()) break;
            int empty = 0;
            // move to the second empty space
            while (empty < 2) {
                w = (w + 1) % n;
                if (res[w] == 0)
                    empty++;
            }
        }
        return res;
    }
};
```