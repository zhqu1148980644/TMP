---
title: Design Twitter
date: 2021-01-04
---
Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed. Your design should support the following methods:

- postTweet(userId, tweetId): Compose a new tweet.
- getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.
- follow(followerId, followeeId): Follower follows a followee.
unfollow(followerId, followeeId): Follower unfollows a followee.

```
Example:

Twitter twitter = new Twitter();

// User 1 posts a new tweet (id = 5).
twitter.postTweet(1, 5);

// User 1's news feed should return a list with 1 tweet id -> [5].
twitter.getNewsFeed(1);

// User 1 follows user 2.
twitter.follow(1, 2);

// User 2 posts a new tweet (id = 6).
twitter.postTweet(2, 6);

// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.getNewsFeed(1);

// User 1 unfollows user 2.
twitter.unfollow(1, 2);

// User 1's news feed should return a list with 1 tweet id -> [5],
// since user 1 is no longer following user 2.
twitter.getNewsFeed(1);
```

#### Solutions

1. ##### hash map with linked list

```cpp
class Twitter {
public:
    unordered_map<int, unordered_set<int>> users;
    unordered_map<int, list<pair<int, int>>> tweets;
    int time = 0;
    /** Initialize your data structure here. */
    Twitter() {

    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        tweets[userId].emplace_front(tweetId, time++);
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<list<pair<int, int>>::iterator> 
        its {tweets[userId].begin()}, ends {tweets[userId].end()};
        int i = 0;
        for (auto fe : users[userId]) {
            if (!tweets[fe].size()) continue;
            its.push_back(tweets[fe].begin());
            ends.push_back(tweets[fe].end());
        }
        // or use heap to find tweet with the minimum time if k gets bigger
        vector<int> feeds;
        while (feeds.size() < 10) {
            int maxi = -1;
            for (int i = 0; i < its.size(); i++) {
                if (its[i] == ends[i]) continue;
                if (maxi == -1 || its[maxi]->second < its[i]->second)
                    maxi = i;
            }
            if (maxi == -1) break;
            feeds.push_back(its[maxi]->first);
            its[maxi]++;
        }
        return feeds;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (followeeId != followerId)
            users[followerId].insert(followeeId);
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        users[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
```