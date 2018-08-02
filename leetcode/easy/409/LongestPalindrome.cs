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

//C#

public class Solution {

    private void swap(char[] str, int i,int j){
        char c = str[i];
        str[i] = str[j];
        str[j] = c;
    }

    private void qSort(char[] str){
        qSortInner(str,0,str.Length-1);
    }

    private void qSortInner(char[] arr,int left,int right){
        if (left + 10 >= right) {
            insertSort(arr,left,right);
            return;
        };

        int i = left + 1;
        int j = right;
        char temp = arr[left];

        while (true) {
            while (i <= right && arr[i]<temp) ++i;
            while (j >= left + 1 && arr[j]>=temp) --j;
            if (i > j) break;
            swap(arr, i++, j--);
        }

        swap(arr, left, j);
        qSortInner(arr, left, j - 1);
        qSortInner(arr, j + 1, right);
    }

    void insertSort(char[] arr,int left, int right){
        for(int i = left;i<=right;i++){
            int pos = i;
            char temp = arr[i];
            for(int j = i-1;j>=left && arr[j] > temp ;j--){
                arr[j+1] = arr[j];
                pos = j;
            }
            if(pos != i) arr[pos] = temp;
        }
    }

    public int LongestPalindrome(string s) {
        if(s == null || s.Length == 0) return 0;
        if(s.Length==1) return 1;

        char[] c = s.ToCharArray();
        if(c.Length == 3 && (c[0]==c[2] || c[0]==c[1] || c[1]==c[2])) return 3;

        qSort(c);
        int ret,i,j;
        ret = 0;
        i = 0;
        j = 1;
        int flag = -1;
        while(j<c.Length){
            if(c[i] == c[j]){
                ret = ret + 2;
                j = j+2;
                i = i+2;
            }else{
                i = j;
                j++;
                flag = 1;
            }
        }

        return flag == 1?ret+1: i == c.Length-1? ret+1:ret;
    }
}
