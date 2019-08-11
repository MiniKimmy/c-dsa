## Bank Service

## CHINESE
* 顾客去银行办理业务，银行有n个位置
* 顾客进入银行先去取号，取号机只有一台
* 如果有位置，就去取号，然后找到位置坐下等待;如果没位置则等到有位置;
* 如果有顾客在等待，工作人员会提醒过来服务

## hints
```
    barber shop problem.
```

## Solution
```
semaphore empty = n;
semaphore mutex = 1;
semaphore service = 0;
semaphore full = 0;

Customer(){
    P(empty);
    P(mutex);
        ..取号..
    V(mutex);
    P(service);
}

Banker(){
    while(true){
        P(full);
        V(empty);
            ..服务..
        V(service);
    }
}
```