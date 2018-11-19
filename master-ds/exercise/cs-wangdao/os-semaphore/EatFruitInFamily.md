## Eat fruit in family

## CHINESE
吃水果问题.

## hints
```
    sync-problem.
    1.only one "plate",but Father and Mon as producers compete each others.
```

## Solution
```
semaphore apple = 0;
semaphore orange = 0;
semaphore empty = 1;  // plate size

Father(){
    while(true){
        P(empty);
            ..put apple..
        V(apple);
    }
}

Mon(){
    while(true){
        P(empty);
            ..put orange..
        V(orange);
    }
}

Son(){
    while(true){
        P(apple);
            ..eat apple..
        V(empty);
    }
}

Daughter(){
    while(true){
        P(orange);
            ..eat orange..
        V(empty);
    }
}
```