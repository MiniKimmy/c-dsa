/*
Q389.Find the Difference

Given two strings s and t which consist of only lowercase letters.

String t is generated by random shuffling string s and then add one more letter at a random position.

Find the letter that was added in t.

Example:

Input:
s = "abcd"
t = "abcde"

Output:
e

Explanation:
'e' is the letter that was added.

 */

//C
char findTheDifference(char* s, char* t) {
    int* m = (int*)malloc(sizeof(int) *255);
    int* n = (int*)malloc(sizeof(int) *255);
    for(int i =0;i<255;i++){
        m[i] = 0;
        n[i] = 0;
    }

    while(*s){
        char a = *s;
        char b = *t;
        m[a] = m[a] + 1;
        n[b] = n[b] +1;
        s++;
        t++;
    }

    n[*t]++;
    for(int i =0;i<255;i++){
        if(m[i] != n[i]){
         return (char)i;
        }
    }
    return 0;
}
