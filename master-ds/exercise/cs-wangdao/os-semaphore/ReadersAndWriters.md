## Readers And Writers

## CHINESE
读者写者问题.

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

int rcount = 0;
semaphore mutex = 1;
semaphore rmutex = 1;
semaphore rw = 1;

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
```