## Producer and consumer issues

## CHINESE
生产者消费者问题.

## hints
```
    sync-problem.
    1.P(empty) first,then P(mutex).
        * in case dead lock.
    2."mutex" is used to protect the 'buffer'.
        * ensure only one can do the 'buffer'.
```

## tips
```
    1.write "Producer" or "Customer" first is ok
    2.semaphore mutex = 1 --> used all the time.
    3.resources"empty" use 'semaphore' but not "int empty = 1"
        * "int count = x" -> is used to counts people but not resources.
```

## Solution
```
semaphore mutex = 1;    //buffer
semaphore full = 0;
semaphore empty = 1;

Producer(){
    while(true){
        P(empty);
            P(mutex);
                ..生产..
            V(mutex);
        V(full);        //buffer++
    }
}

Customer(){
    while(true){
        P(full);
            P(mutex);
                ..消费..
            V(mutex);
        V(empty);       //buffer--
    }
}
```