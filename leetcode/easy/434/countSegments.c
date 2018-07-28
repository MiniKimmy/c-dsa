/*
Q434.Number of Segments in a String

Count the number of segments in a string, where a segment is defined to be a contiguous sequence of non-space characters.

Please note that the string does not contain any non-printable characters.

Example:

Input: "Hello, my name is John"
Output: 5
*/

//C
char* trimStart(char* s){
    while(*s){
        char c = *s;
        if(c != ' ')  break;
        s++;
    }
    return s;
}


int countSegments(char* s) {
    if(s == NULL) return 0;

    char* ch = trimStart(s);
    if(*ch == '\0') return 0;

    int ret = 0;
    int flag = 1;
    while(*ch){
        char c = *ch;
        if(c != ' '){
            flag = 1;
        }else if(flag == 1){
            flag = 0;
            ++ret;
        }
        ch++;
    }

    return flag==1? ret+1:ret;
}
