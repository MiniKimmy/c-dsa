## Visit Museum

## CHINESE
参观博物院.
* 同一个入口出口，只允许有一个游客进出
* 一次只能有500人参观

## hints
```
    easy.
```

## Solution
```
semaphore empty = 500;
semaphore mutex = 1;   // only one in/out

Visitor(){
    P(empty);
        P(mutex);
            ..get in ..
        V(mutex);
    ..visit..
    P(mutex);
        ..get out..
    V(mutex);
    V(empty);
}
```