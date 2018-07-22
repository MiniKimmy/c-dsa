/*
205.Questions
Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

Example 1:

Input: s = "egg", t = "add"
Output: true

Example 2:

Input: s = "foo", t = "bar"
Output: false

Example 3:

Input: s = "paper", t = "title"
Output: true

Note:
You may assume both s and t have the same length.
Seen this question in a real interview before?

    Difficulty:Easy
    Total Accepted:146.8K
    Total Submissions:417.7K
    Contributor:LeetCode

    Subscribe to see which companies asked this question.
    Related Topics


    Similar Questions
    Word Pattern
*/

//C#
public class Solution {
    public bool IsIsomorphic(string s, string t) {

        Dictionary<char, List<int>> d1 = new Dictionary<char, List<int>>();
        Dictionary<char, List<int>> d2 = new Dictionary<char, List<int>>();

        for(int i =0;i<s.Length;i++){
            if(d1.ContainsKey(s[i]) == false){
                d1.Add(s[i], new List<int>() {
                    i
                });
            }else{
                d1[s[i]].Add(i);
            }

            if(d2.ContainsKey(t[i]) == false){
                d2.Add(t[i], new List<int>() {
                    i
                });
            }else{
                d2[t[i]].Add(i);
            }

            if(d1[s[i]].Count != d2[t[i]].Count) return false;
            else {
                List<int> s1 = d1[s[i]];
                List<int> t2 = d2[t[i]];
                for(int j=0;j<s1.Count;j++){
                    if(s1[j] != t2[j]) return false;
                }
            }
        }
        return true;
    }
}
