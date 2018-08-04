 /*
 Q680.Valid Palindrome II

 Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

Example 1:

Input: "aba"
Output: True

Example 2:

Input: "abca"
Output: True
Explanation: You could delete the character 'c'.

Note:
    The string will only contain lowercase characters a-z. The maximum length of the string is 50000.
*/

//C
bool validPalindrome(char* s) {
    if(s == NULL) return false;

    int len = 0;
    while(s[len]){
        len++;
    }

    int j = len-1;
    int flag = 0;
    int dummy_flag = -1;
    for(int i=0;i<len/2 ;i++){
        if(s[i] == s[j]) {
            --j;
            continue;
        }

        if(flag == 1) return false;
        if(i+1>=j) break;

        if(s[i] == s[j-1]){
            if(dummy_flag==-1 && s[j] == s[i+1]){
                i++;
                dummy_flag = i;
            }else{
                flag = 1;
                dummy_flag=-1;
            }
            --j;
        }else if(s[j] == s[i+1]){
            if(dummy_flag == -1 && s[i] == s[j-1]){
                j--;
                dummy_flag = i;
            }else{
                flag = 1;
                dummy_flag=-1;
            }
            i++;
        }else{
            return false;
        }
        --j;
    }

    if(len%2 != 0 ) {
        if(s[len/2] == s[len/2+1]){
            return true;
        }else false ;
    }

    return dummy_flag!=-1 && len/2-1 != dummy_flag?false:true;
}
