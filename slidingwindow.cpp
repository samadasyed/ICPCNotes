#include <bits/stdc++.h> 

using namespace std; 

int main () {

    //Sliding window, fixed size window
    class Solution {
    public:
    bool IsAnagram(string s, string t) {
        if (s.size() != t.size()) return false;

        vector<int> count(26, 0);
        for (char c : s) count[c - 'a']++;
        for (char c : t) count[c - 'a']--;

        for (int n : count) {
            if (n != 0) return false;
        }
        return true;
    }

    vector<int> findAnagrams(string s, string p) {
        int window = p.size();
        int left = 0;
        int right = window;
        vector<int> ans;

        while (right <= s.size()) {
            if (IsAnagram(s.substr(left, window), p)) {
                ans.push_back(left);
            }
            left++;
            right++;
        }
        return ans;
    }
};
    //Find all anagrams in a string 
    //Input: s = "cbaebabacd", p = "abc"
    //Output: [0,6]
    //Explanation:
    //The substring with start index = 0 is "cba", which is an anagram of "abc".
    //The substring with start index = 6 is "bac", which is an anagram of "abc".
    //////////////////////////////////////////////////////////////////



    //Sliding window with hashmap 
    class Solution {
public:
    int lengthOfLongestSubstring(string s) {
    int maxSub = 0; 
    int left = 0; 
    int right = 0; 
    unordered_map<char, int> freq; 
    if (s.length() == 0) return 0; 
    if (s.length() == 1) return 1; 

    while (right < s.length()) {
        char c = s[right]; 
        freq[c]++; 
        right++; 

        while (freq[c] > 1){
            freq[s[left]]--;
            left++; 
        }
        maxSub = max(maxSub, right-left); 
    }
    return maxSub; 
    }
};
//Longest substring without repeating characters
//Input: s = "abcabcbb"
//Output: 3
//Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.
    return 0; 
}