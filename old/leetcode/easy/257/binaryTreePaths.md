## 257.Binary Tree Paths

Given a binary tree, return all root-to-leaf paths.

Note: A leaf is a node with no children.

**Example:**
```
Input:
   1
 /   \
2     3
 \
  5
Output: ["1->2->5", "1->3"]
Explanation: All root-to-leaf paths are: 1->2->5, 1->3
```

## hints
```
    I string problems
        1.char* intParse(int n)  --toString()
        2.new String()
        3.allocate():
        4.contact String: s=s1+s2
    II. dfs
        1.局部item as bufferStr
        2.Add(item)
```

## Solution
``` c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

char* toString(int n){
    if(n == 0){
        char* ret = (char*)malloc(sizeof(char*) * 2);
        ret[0] = '0';
        ret[1] = '\0';
        return ret;
    }

    int* buffer = (int*)malloc(sizeof(int) * 10);
    int index = 0;
    int abs = n < 0? -n:n;

    while(abs>0){
        int a = abs%10;
        buffer[index++] = a;
        abs = abs / 10;
    }

    if(n<0) index++;
    char* ret = (char*)malloc(sizeof(char) * (index+1));

    for(int i = index - 1;i>=0;--i){
        ret[index-i-1] = buffer[i] + '0';
    }

    if(n<0) ret[0] = '-';
    ret[index] = '\0';

    free(buffer);
    return ret;
}

void allocate(char** str, int* maxLen){
    *maxLen = *maxLen * 2;

    char* temp = *str;
    *str = (char*)malloc(sizeof(char) * (*maxLen));
    for(int i = 0;i<(*maxLen);++i){
        *str[i] = temp[i];
    }

    *str[*maxLen - 1] = '\0';
    free(temp);
    return;
}

char** binaryTreePaths(struct TreeNode* root, int* returnSize) {
    if(root == NULL) return NULL;

    int maxLen = 1000;
    char* str = (char*)malloc(sizeof(char) * maxLen);
    char** result = (char**)malloc(sizeof(char*) * maxLen);
    int count = 0;

    dfs(root, str, &maxLen,0,&result,&count);

    *returnSize=count;
    return result;
}

void dfs(struct TreeNode* root, char* str, int* maxLength, int index, char*** result,int* count){
    if(root == NULL) return;

    if(*maxLength < index + 10) {
        allocate(&str, maxLength);
    }

    char* val = toString(root->val);
    char* p = val;
    while(*p){
        str[index++] = (*p);
        p++;
    }
    free(val);

    if(root->left != NULL || root->right != NULL){
        str[index++] = '-';
        str[index++] = '>';
    }else{
        char* item = (char*)malloc(sizeof(char) * (index+1) );
        item[index] = '\0';
        for(int i = 0;i<index;++i){
            item[i] = str[i];
        }

        (*result)[(*count)] = item;
        *count = *count + 1;
        return;
    }

    dfs(root->left, str, maxLength, index, result, count);
    dfs(root->right, str, maxLength, index, result, count);
}
```