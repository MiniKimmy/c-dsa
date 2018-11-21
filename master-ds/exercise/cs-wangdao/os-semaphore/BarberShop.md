## Barber Shop

## CHINESE
理发师问题,
* n个椅子和1个理发椅子
* 顾客来到如果无座位则离开，有座位则等待剪发
* 理发师每次剪完1个就会叫1个人剪发

## hints
```
    1.nice semaphore "finish" as a current state.
```

## Solution
```
int chair = n + 1;   //n个等候位置和1个理发位置
semaphore mutex = 1; //保护chair变量
semaphore ready = 0; //排队等待的状态
semaphore finish = 1;//理发师的状态信息. 1表示空闲状态,0表示忙碌状态

Customer(){
    P(mutex);
        if(chair > 0){
            chair--;
            V(mutex);
            V(ready);
            P(finish);
                ..waiting..
        }else{
            V(mutex);
        }
}

Barber(){
    while(true){
        P(ready);
            ..hair cut..
        P(mutex);
            chair++;
        V(mutex);
        V(finish);
    }
}
```