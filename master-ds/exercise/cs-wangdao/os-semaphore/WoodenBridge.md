## Wooden bridge

## CHINESE
独木桥问题.
* 一条桥,2个村庄,1条独木桥连接两个世界.
* 每次桥只允许一边的人先走，另一边的要等
* 如果都在同一边，可以一起走
* 但由于独木桥承重有限，只允许2个人在独木桥上走

## hints
```
    1.need a loop --cause when people >= 2, it means need to waiting.
    2.use count.
    3.use double state.
```

## Solution
```
int left = 0;
int right = 0;
semaphore lmutex = 1;
semaphore rmutex = 1;
semaphore mutex = 1;
semaphore stateA = 1;
semaphore stateB = 1;

/*lmutex as VillageA*/
VillageA(){
    while(true){   //while--> if left>2, return to the queue waiting.
        P(lmutex);
        if(left == 0){
            P(stateB);
        }

        if(left < 2){
            left++;
            V(lmutex);
                ..过桥..
            P(lmutex);
                left--;
                if(left == 0){
                    V(stateB);
                }
            V(lmutex);
        }else{
            V(lmutex);
        }
    }
}

/*rmutex as VillageB*/
VillageB(){
while(true){   //while--> if right>2, return to the queue waiting.
    P(rmutex);
        if(right == 0){
            P(stateA);
        }

        if(right < 2){
            right++;
            V(rmutex);
                ..过桥..
            P(rmutex);
                right;
                if(right == 0){
                    V(stateA);
                }
            V(rmutex);
        }else{
            V(rmutex);
        }
    }
}

```