## Smokers issue

## CHINESE
吸烟者问题:
* 假设一个系统有3个抽烟者进程和一个供应者进程。每个抽烟者不停地卷烟并抽掉它，但是要卷起并抽掉一支烟。抽烟者需要3个材料:烟草、纸和胶水。
* 3个抽烟者中:第1个拥有烟草、第2个拥有纸、第3个拥有胶水。
* 供应者进程无限提供3种材料。每次将2种材料放在桌子上，抽烟者谁刚好缺这2种材料的可以抽烟，并给供应者一个信号告知完成。供应者就会重复动作再放2种材料到桌子上，过程一直重复。

## hints
```
    1.each group as one semaphore is done.
    2.use "Producer()" to control the whole process.
```

## Solution1
```
/* G1 means paper && glue --for SmokerA
 * G2 means tobaco && glue --for SmokerB
 * G3 means tobaco && papre --for SmokerC
 */

semaphore offerG1 = 0;
semaphore offerG2 = 0;
semaphore offerG3 = 0;
semaphore finish = 1;

Producer(){
    while(true){
        P(finish);
        int x = random() % 3;
        switch(x){
            case 0: V(offerG1); break;
            case 1: V(offerG2); break;
            case 2: V(offerG3); break;
        }
    }
}

SmokerA(){
    while(true){
        P(offerG1);
            ..smoke..
        V(finish);
    }
}

SmokerB(){
    while(true){
        P(offerG2);
            ..smoke..
        V(finish);
    }
}

SmokerC(){
    while(true){
        P(offerG3);
            ..smoke..
        V(finish);
    }
}
```

## Solution2
```
semaphore tobaco = 0;
semaphore paper = 0;
semaphore glue = 0;
semaphore finish = 1;
int x;

Producer(){
    while(true){
        P(finish);
        x = random() % 3;
        switch(x){
            case 0:
                V(paper);
                V(glue);
                break;
            case 1:
                V(tobaco);
                V(glue);
                break;
            case 2:
                V(tobaco);
                V(paper);
                break;
        }
    }
}

SmokerA(){
    while(true){
        if(x == 0){
            P(paper);
            P(glue);
                ..smoke..
            V(finish);
        }
    }
}

SmokerB(){
    while(true){
        if(x == 1){
            P(tobaco);
            P(glue);
                ..smoke..
            V(finish);
        }
    }
}

SmokerC(){
    while(true){
        if(x == 2){
            P(paper);
            P(tobaco);
                ..smoke..
            V(finish);
        }
    }
}
```

