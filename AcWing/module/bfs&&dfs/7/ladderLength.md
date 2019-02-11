## 127. Word Ladder
[这里](https://leetcode.com/problems/word-ladder/)

## hints
```
    bfs最短路径+hash记录
1.由于bfs不可能递归，所以要通过dis[]来记录距离
    (1).每次更新状态dis[new] = dis[cur] + weight
        * 业务上，有1个字母相同的2个单词就连边。边的weight=1
        * 根据标记走过以及相连边来更新dis[index]
    (2).默认初始化是0，利用!dis[new]来记录是否已经访问过
        * 不能使用state记录，当点的个数超过10个就是2^10以上了，x个0就是2^x大小的state
2.由于不会使用c语言实现map/dictionary，因此要考虑wordList怎么记录<string,int>
    * 利用wordList[index]来绑定dis[index].（毕竟只会访问一次）
    * 考虑到beginword会与wordList中有无重复问题，那么dis[]里默认要多增加1个空间用于作为记录的beginword的下标[wordListSize]
        * 然后若beginword与wordList中有重复的情况话，则初始dis[index] = 1
        * 这个1是因为答案需要把beginword也算进去。
```
## Solution
``` c
int getLength(char* str){
    int len = 0;
    while(str[len]){
        len++;
    }

    return len;
}

/// 检查2个单词里只有1个字母不同
bool check(char* a, char* b){
    int i = 0;
    int count = 0;
    while(a[i]){
        count += a[i] != b[i];
        ++i;
    }

    return count == 1;
}

/// 检查2个单词是否相等
bool equal(char* a, char* b){
    int i = 0;
    while(a[i]){
        if(a[i] != b[i]) return false;
        ++i;
    }

    return true;
}

/// new字符串
char* createString(char* str, int len)
{
    char* ret = (char*)malloc(sizeof(char) * (len + 1));
    for(int i = 0;i<len;++i){
        ret[i] = str[i];
    }

    ret[len] = '\0';
    return ret;
}

/// 根据val获取对应的index
int getIndex(char** str,int strSize, char* val){
    for(int i = 0;i<strSize;++i){
        if(equal(str[i],val)) return i;
    }

    return strSize;
}

int ladderLength(char* beginWord, char* endWord, char** wordList, int wordListSize) {
    int len = getLength(beginWord);
    int SIZE = 5000;

    char** sqQueue = (char**)malloc(sizeof(char*) * SIZE);
    int front = 0; int rear = 0;

    sqQueue[rear] = createString(beginWord,len);
    rear = (rear+1) % SIZE;

    int* dis = (int*)malloc(sizeof(int) * (wordListSize+1));
    for(int i = 0;i<wordListSize+1;++i){
        dis[i] = 0;
        if(i<wordListSize && equal(beginWord,wordList[i])) dis[i] = 1;
    }

    dis[wordListSize] = 1;

    while(front != rear){
        char* t = sqQueue[front];
        front = (front + 1) % SIZE;

        int index = getIndex(wordList,wordListSize,t);
        if (equal(t,endWord)) {
            free(sqQueue);
            return dis[index];
        }

        //bfs
        for(int i = 0; i<wordListSize;++i){
            if(check(t,wordList[i]) && !dis[i])
            {
                dis[i] = dis[index] + 1;
                sqQueue[rear] = createString(wordList[i],len);
                rear = (rear+1)%SIZE;
            }
        }

        free(t);
    }

    free(dis);
    free(sqQueue);
    return 0;
}
```
## hints
```
    csharp有dictionary可以用
```
## Solution
``` csharp
public class Solution {
    private bool check(string a, string b)
    {
        int n = a.Length;
        int ret = 0;
        for(int i = 0;i<n;++i){
            ret += a[i] != b[i]?1:0;
        }

        return ret == 1;
    }

    public int LadderLength(string beginWord, string endWord, IList<string> wordList) {

        Dictionary<string,int> hash = new Dictionary<string,int>();
        foreach(var item in wordList){
            hash.Add(item,0);
        }

        if(hash.ContainsKey(beginWord)){
            hash[beginWord] = 1;
        }else{
            hash.Add(beginWord,1);
        }

        Queue<string> q = new Queue<string>();
        q.Enqueue(beginWord);

        while(q.Count>0)
        {
            string t = q.Dequeue();
            if(t == endWord) return hash[t];

            for(int i = 0;i<wordList.Count;++i)
            {
                if(check(t,wordList[i]) && hash[wordList[i]] == 0)
                {
                    hash[wordList[i]] = hash[t] + 1;
                    q.Enqueue(wordList[i]);
                }
            }
        }

        return 0;
    }
}
```