    Note: This is a companion problem to the System Design problem: Design TinyURL.

TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.

Design the encode and decode methods for the TinyURL service. There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.


#### Solutions

1. ##### random string key

```c++
#include <experimental/random>
class Solution {
private:
    unordered_map<string, string> m;
    string keystr = "1234567890qwertyuiopasdfghjklzxcvbnmQWEASDZXCVFRTGBNHYUJMKIOPL@";
public:
    string randkey() {
        string key;
        for (int i = 0; i < 6; i++) {
            key.push_back(keystr[std::experimental::randint(0, (int)keystr.size() - 1)]);
        }
        return key;
    }
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string k;
        while (m.count(k = randkey()));
        m[k] = longUrl;
        return "http://tinyurl.com/" + k;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return m[shortUrl.substr(19)];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
```