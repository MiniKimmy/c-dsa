/*
Q387.First Unique Character in a String
Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.

Note: You may assume the string contain only lowercase letters. */

//C
int getLen(char* s)
{
    int len = 0;
    while(*s){
        len++;
        s++;
    }
    return len;
}

int firstUniqChar(char* s) {
    if(s == NULL) return -1;

    int len = getLen(s);
    int* m =(int*)malloc(sizeof(int) * 255);
    for (int i = 0; i < 255; i++) m[i] = 0;

    int ret = -1;
    int front = 0;
    int rear = 0;
    int* queue = (int*)malloc(sizeof(int)* len);

    for(int i = 0; i< len;i++){
        queue[rear++] = (int)(s[i]);
        if(m[s[i]] == 0){
            m[s[i]] = 1;
            if(ret == -1) ret = i;
        }else if(m[s[i]] == 1){
           m[s[i]] = 2;
           while(m[queue[front]] == 2 && front < rear - 1){
               front++;
           }
           ret = front == rear-1 ? -1 : front;
        }
    }

    return ret;
}
