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

/**
 * minikimmy-hints: <Collisions pointer> and dummy_flag (ps: two flags, helps to Judge one more situation.)
 * Last Modified time: 2018-08-05 10:05:21
 * Ending-tag : when use 'for' circle, from i=0 to i<len/2 i++
 * use tow flags --> just for incase 2 pointers couldn't return back.
 * 2 pointers run at the same time, and superise their current value to judge whether cater to the problem.
 ** And you have to use one side to judge first, ---that is unfair!! because left-pointer and right-pointer is equal,so when left-pointer got troble && right-pointer got troble at the same time , we use dummy_flag.
 * so dummy_flag is used to balance their justice. [when they got troble simultaneous], they do the same motion,and mark the dummy_flag.
 * when the next time 1 pointer got troble again, dummy_flag will let the real 'flag' updata, and dummy_flag can reset.it means real 'flag' is the best Ending-tag, so when the Ending-tag appeared, dummy_flag can leave.
 * [ps: but I'd show you a ingenious code: we can use dummy_flag to store infomation instead of 0 || 1, we can use dummy_flag to save Index.]
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
    int dummy_flag = -1;          // dummy_flag is for auxiliary. 'flag' is real flag

    //left-pointer && right-pointer are running simultaneous.
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
                dummy_flag = i;   //store 'index'   so I set dummy_flag = -1 initially.
            }else{
                flag = 1;
                dummy_flag=-1;
            }
            --j;
        }else if(s[j] == s[i+1]){
            if(dummy_flag == -1 && s[i] == s[j-1]){
                j--;
                dummy_flag = i;  //store 'index'
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

    // Judge if the sourceArray.Length is odd (char*s -- sourceArray)
    if(len%2 != 0 ) {
        if(s[len/2] == s[len/2+1]){
            return true;
        }else false ;
    }

    //else the array.Length is even.
    return dummy_flag!=-1 && len/2-1 != dummy_flag?false:true;
}
