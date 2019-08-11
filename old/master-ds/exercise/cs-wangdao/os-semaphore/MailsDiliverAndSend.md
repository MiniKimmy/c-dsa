## Mails diliver and send

## CHINESE
送信和回信问题.
* A邮箱能装N个信，当前有x个信,甲每次收一封,回一封给乙的信箱B
* B邮箱能装M个信，当前有y个信,乙每次收一封,回一封给甲的信箱A

## hints
```
    producers and customers problem.
```

## Solution
```
semaphore amutex = 1;
semaphore bmutex = 1;
semaphore aempty = N-x;
semaphore bempty = M-y;
semaphore afull = x;
semaphore bfull = y;

/*P1 = 甲*/
P1(){
    while(true){
        P(bfull);
            P(bmutex);
                ..取信..
            V(bmutex);
        V(bempty);

        P(aempty);
            P(amutex);
                ..写信..
            V(amutex);
        V(bfull);
    }
}

/*P2 = 乙*/
P2(){
    while(true){
        P(afull);
            P(amutex);
                ..取信..
            V(amutex);
        V(aempty);

        P(bempty);
            P(bmutex);
                ..写信..
            V(bmutex);
        V(afull);
    }
}

```