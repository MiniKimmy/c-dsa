## 46. 二叉搜索树的后序遍历序列
[这里](https://www.acwing.com/problem/content/44/)
输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
如果是则返回true，否则返回false。

**Note**
* 假设输入的数组的任意两个数字都互不相同。

**Example :**
```
Input:[4, 8, 6, 12, 16, 14, 10]
Output:true
Explanation:
         10
       /     \
      6       14
    /   \   /    \
   4     8 12     16
```

## hints
```
    1.后序遍历的最右边元素是root
        (1).[4, 8, 6, 12, 16, 14, /10] : 10是root
        (2).遍历一遍，[4,8,6,// 12, 16,14]，比10小是10的左孩子
        (3).然后继续切分[4,8,6] 和 [12,16,14]
            * [4,8, /6]:6是root
            * [12,16, /14]:14是root
    2.判断不能成为BST的后序，即要保证root的左右两边，左边全小于root,右边全大于root
```

## Solution
``` c
void dfs(int post[], int l, int r, int* ret){
    if(l > r || *ret == 0) return;

    int root = post[r];

    int pos = l;
    while(pos < r && post[pos] < root) pos++; //拿到右半边的第[0]个

    for(int i = pos;i<r;++i){
        if(post[i] < root ) {
            *ret = 0;
            return;
        }
    }

    dfs(post, l, pos-1, ret);  // [l,pos-1] [pos, r-1], r是root
    dfs(post, pos, r-1, ret);
}

bool verifySequenceOfBST(int sequence[], int length){
    int refRet = 1;
    dfs(sequence,0,length-1, &refRet);

    return refRet==1?true:false;
}
```

## hints
[参考这题](https://www.acwing.com/problem/content/23/)
```
ex1正确例子:
      ↓---↓
post:[4,8,6,12,16,14,10]
in:  [4,6,8,10,12,14,16]
      ↑-----↑
           root
ex2错误例子:

    ↓-↓ ↓
post:[4,11,6,12,16,14,10]
in:  [4,6,10,11,12,14,16]
     ↑----↑
         root

ex3错误例子:
      ↓---↓    ↓
post:[4,8,6,12,9,14,10]
in  :[4,6,8,9,10,12,14]
     ↑--------↑
             root

    1.利用后序遍历和中序创建二叉树的思路
        (1).后序遍历的最右边元素是root
        (2).利用hash、inorder来切分两边左右孩子
    2.判断条件:如果是正确的例子,则后序post[]左孩子的数量与inorder[]的数量要相等;
        * 如果错误的例子,post[]在左孩子数量≠中序root的左半边数组元素个数
    3.遍历post的时候找到中间的分界处，然后检查当前post左右两边的是否在root左右
        * 其实只需要检测左边或者检查右边即可。
        * 因为我们是用一个正确的inorder去检查可能错误的postOrder，所以post的一边出错必然会影响另一边也出错。
        * 简单点就是，检查post的左半边k个元素(这k个是inorder里可以计算出)，检查这k个是否都在root的左边.
    4.使用fund dfs()
        * 以前的void dfs,最后面经常
            dfs(root->left,..)
            dfs(root->right,..)
        * 改变为使用逻辑符号 || && ,直接return dfs() && dfs()
    5.修改InserSort之后就会变成O(n)的时间复杂度了.
```

## Solution2
```
/// 插入排序，为了创造中序遍历的数组.
void InsertSort(int* arr, int arrSize){
    for(int i = 1;i<arrSize;++i){
        int temp = arr[i];
        int pos = i;
        for(int j = i-1;j>=0 && arr[j] >= temp ; --j){
            arr[j+1] = arr[j];
            pos = j;
        }

        if(pos != i) arr[pos] = temp;
    }
    return;
}

/// 当字典用，根据value查index
int getIndex(int* arr,int arrSize, int val){
    for(int i = 0;i<arrSize;++i){
        if(arr[i] == val) {
             return i;
        }
    }
}

bool dfs(int* post, int* inorder, int n, int postL, int postR, int inL, int inR){
    if(postL>postR) return true;

    int root = post[postR];
    int mid = getIndex(inorder, n, root);

    int k = postL;
    while(k < postR && post[k] < root) k++; //拿到右半边的第[0]个
    if(k-postL !=  mid - inL){
         return false;
    }

    return dfs(post,inorder,n, postL, postL + mid - inL -1, inL, mid-1) && dfs(post,inorder,n, postL+ mid - inL, postR-1,mid+1,inR);
}

bool verifySequenceOfBST(int sequence[], int length){
    int* inorder = (int*)malloc(sizeof(length));
    for(int i = 0;i<length;++i){
        inorder[i] = sequence[i];
    }

    InsertSort(inorder,length);
    return dfs(sequence,inorder,length,0,length-1,0,length-1);
}
```