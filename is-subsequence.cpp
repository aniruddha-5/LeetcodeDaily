/*
Problem link: https://leetcode.com/problems/is-subsequence/description/?envType=daily-question&envId=2023-09-22
392. Is Subsequence

Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

 

Example 1:

Input: s = "abc", t = "ahbgdc"
Output: true
Example 2:

Input: s = "axc", t = "ahbgdc"
Output: false
*/

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int sl = s.length();
        int tl = t.length();
        int k=0,cnt=0;
        for(int i=0;i<sl;i++){
            for(int j=k;j<tl;j++){
                if(s[i]==t[j]){
                    k=j+1;
                    cnt++;
                    break;
                }
            }
        }
        if(cnt==sl) return true;

        return false;
    }
};