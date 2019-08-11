## Readers And Writers

## CHINESE
读者写者问题. 多人读，1人写。没有人中途离开队伍。
* 读者优先 : 读者在排队的都进入，直到无读者才给写者进
* 公平原则 : 按照排队顺序
* 写者优先 : 写者在排队的其他人都排在后面.

## Solution1
```
/*Readers first*/

int rcount = 0;
semaphore rmutex = 1;
semaphore rw = 1;

Reader(){
    P(rmutex);
    if(rcount == 0) {
        P(rw);
    }
    rcount++;
    V(rmutex);
        ..reading..
    P(rmutex);
        rcount--;
        if(rcount == 0){
            V(rw);
        }
    V(rmutex);
}

Writer(){
    P(rw);
        ..write..
    V(rw);
}
```

## Solution2
```
/*equality solution */

int rcount = 0;        // 读者数量
semaphore rmutex = 1;  // 保护rcount
semaphore mutex = 1;   // 排在前面的人
semaphore rw = 1;      // 能否可进行写操作.

Reader(){
    P(mutex);
        P(rmutex);
        if(rcount == 0) {
            P(rw);
        }
        rcount++;
        V(rmutex);
    V(mutex);
        ..reading..
    P(rmutex);
        rcount--;
        if(rcount == 0){
            V(rw);
        }
    V(rmutex);
}

Writer(){
    P(mutex);
        P(rw);
            ..write..
        V(rw);
    V(mutex);
}
```

## Solution3
```
/*writer first */
int rcount = 0;         //读者人数
int wcount = 0;         //写者人数
semaphore rmutex = 1;   //保护rcount
semaphore wmutex = 1;   //保护wcount
semaphore mutex = 1;    //排队
semaphore canWrite = 1; //写者权限
semaphore canRead = 1;  //读者权限

Reader(){
    P(rmutex);
        if(rcount == 0){
            P(canRead);
        }
        rcount++;
    V(rmutex);
        ..reading..
    P(rmutex);
        rcount--;
        if(rcount == 0){
            V(canRead);
        }
    V(rmutex);
}

Writer(){
    P(mutex);
        P(wmutex);
            if(wcount == 0){
                P(canRead);
            }
            wcount++;
        V(wmutex);
    V(mutex);

        P(canWrite);
            ..write..
        V(canWrite);

    P(wmutex);
        wcount--;
        if(wcount == 0){
            V(canRead);
        }
    V(wmutex);
}


/* [old version -- may be can not work]
int rcount = 0;
int wcount = 0;
semaphore mutex = 1;   //排在队伍的前面
semaphore rmutex = 1;
semaphore wmutex = 1;
semaphore rw = 1;      //写者权限
semaphore rr = 1;      //读者权限

Reader(){
    P(wmutex);
    if(wcount > 0) {
    P(mutex);
        P(rmutex);
            if(rcount == 0) {
                P(rw);
            }
            rcount++;
        V(rmutex);
    V(mutex);
    V(wmutex);

        ..reading..

    P(rmutex);
        rcount--;
        if(rcount == 0){
            V(rw);
        }
    V(rmutex);

    }
    else{
        V(wmutex);
    }
}

Writer(){
    P(mutex);
        P(wmutex);
            if(wcount == 0) {
            P(rr);
        }
        wcount++;
        V(wmutex);
    V(mutex);

        P(rw);
            ..write..
        V(rw);

    P(wmutex);
        wcount--;
            if(wcount == 0) {
            V(rr);
        }
    V(wmutex);
}
*/
```