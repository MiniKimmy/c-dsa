/*
Q409.Longest Palindrome
Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7
Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
*/

//C

int longestPalindrome(char* s) {
    if(s == NULL) return 0;

    int* m = (int*)malloc(sizeof(int) * 255);
    for(int i = 0;i<255;i++) m[i] = 0;

    while(*s){
        char c = *s;
        ++m[c];
        s++;
    }

    int even = 0;
    int odd = 0;
    for(int i = 0; i<255;i++){
        if(m[i]==0) continue;
        else{
            if(m[i]%2!=0)odd++;
            even += m[i] / 2 * 2;
        }
    }

    return odd == 0? even:even+1;
}
