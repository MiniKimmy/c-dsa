## 292. Nim Game

You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner. You will take the first turn to remove the stones.
<br />
Both of you are very clever and have optimal strategies for the game. Write a function to determine whether you can win the game given the number of stones in the heap.

**Example:**
```
Input: 4
Output: false
Explanation: If there are 4 stones in the heap, then you will never win the game;
             No matter 1, 2, or 3 stones you remove, the last stone will always be
             removed by your friend.
```

## hints
```
n
1(me)
2(me)
3(me)
4 (you)                     5(me)
4mod3 = 1 div3  =1  add=2   5mod3 = 2 div 1  add=3
4mod2 = 0 div2  =2  add=2   5mod2 = 1 div 2  add=3

6(me)                       7(me)
6mod3 = 0 div3 = 2  add=2   7mod3 = 1 div3 = 2  add=3
6mod2 = 0 div2 = 3  add=3   7mod2 = 1 div2 = 1  =2

8(you)
8mod3 = 2 div3 = 2  add=4(1)
8mod2 = 0 div2 = 4  add=4(1)

9(me)
10(me)
11(me)
12(you)

so n= 4,8,12... You win!
```

## Solution
``` c
bool canWinNim(int n) {
    return n%4 ==0?false:true;

    /* Time Limit.
    long* dp = (long*)malloc(sizeof(long)*(n+1));
    dp[1] = 0;
    dp[2] = 0;
    dp[3] = 0;
    for(long i = 4;i<=n;++i){
        long a = i%3;
        long b = i/3;
        long step1 = a+b>3?(a+b)%3:a+b;
        a=i%2;
        b=i/2;
        long step2 = a+b>3? (a+b)%3:a+b;
        dp[i] = dp[i-step1]==0&&dp[i-step2]==0&&dp[i-1]==0?1:0;
    }
    return dp[n] ==0?true:false;
    */
}
```