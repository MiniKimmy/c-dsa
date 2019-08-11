/*
Q744.Find Smallest Letter Greater Than Targer

Given a list of sorted characters letters containing only lowercase letters, and given a target letter target, find the smallest element in the list that is larger than the given target.

Letters also wrap around. For example, if the target is target = 'z' and letters = ['a', 'b'], the answer is 'a'.

Examples:

Input:
letters = ["c", "f", "j"]
target = "a"
Output: "c"

Input:
letters = ["c", "f", "j"]
target = "c"
Output: "f"

Input:
letters = ["c", "f", "j"]
target = "d"
Output: "f"

Input:
letters = ["c", "f", "j"]
target = "g"
Output: "j"

Input:
letters = ["c", "f", "j"]
target = "j"
Output: "c"

Input:
letters = ["c", "f", "j"]
target = "k"
Output: "c"

Note:

    letters has a length in range [2, 10000].
    letters consists of lowercase letters, and contains at least 2 unique letters.
    target is a lowercase letter.

 */

//C
void insertSort(int* arr,int size){
    for(int i = 1;i<size;i++){
        int k = i;
        int temp = arr[i];
        for(int j = i-1;j>=0 && temp<arr[j];j--){
            arr[j+1] = arr[j];
            k = j;
        }
        if(k != i) arr[k] = temp;
    }
}

char nextGreatestLetter(char* letters, int lettersSize, char target) {
    if(target == '\0' || letters == NULL ) return '\0';

    int* m = (int*)malloc(sizeof(int) * 255);
    for(int i=0;i<255;i++){
        m[i] = 0;
    }

    int* n = (int*)malloc(sizeof(int) * 26);
    int j = 0;

    //while(*letters){  //must use 'lettersSize'--> letters[n] not set'\0' at the end of this array {' ',' ',...,'\0'} !!!

    for(int i = 0;i<lettersSize;i++){
        char c = letters[i];
        if(0 == m[c]){
            m[c] = 1;
            n[j++] = c;
        }
    }

    insertSort(n,j);
    for(int i = 0;i<j;i++){
        if(n[i] > target){
            return n[i];
        }
    }

    return n[0];
}
