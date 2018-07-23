/*
Q205.Isomorphic Strings
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

//C
bool isIsomorphic(char* s, char* t) {
    int* a1 = (int*)malloc(sizeof(int)* 255);
    int* a2 = (int*)malloc(sizeof(int)* 255);

    int i = 0;
    while(s[i]){
        char ch1 = s[i];
        char ch2 = t[i];
        if(a1[ch1] != a2[ch2]) return false;
        ++i;
        a1[ch1] = i;
        a2[ch2] = i;
    }
    return true;
}
