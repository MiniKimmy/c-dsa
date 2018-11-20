## Put and get Odd and Even

## CHINESE
三个进程P1,P2,P3互斥包含一个N（N>0）个单元的缓冲区。
* P1每次用produce()生成一个正整数并用put()送入缓冲区，
* P2每次用getodd()从缓冲区中取出1个奇数并用countodd()统计奇数个数
* P3每次用geteven()从缓冲区中取出1个偶数并用counteven()统计偶数个数

## hints
```
    smoker problem.
    09年408,PV操作
```

## Solution
```
semaphore offerOdd = 0;    //提供了奇数的个数
semaphore offerEven = 0;   //提供了偶数的个数
semaphore empty = N;       //缓冲区剩余的空位
semaphore mutex = 1;       //只许一个人进入缓冲区

P1(){
    while(true){
        int x = produce();
        P(empty);
        P(mutex);
            put();
        V(mutex);
        if(x % 2 == 0){
            V(offerEven);
        }else{
            V(offerOdd);
        }
    }
}

P2(){
    while(true){
        P(offerOdd);
            P(mutex);
                getodd();
            V(mutex);
        V(empty);
        countodd();
    }
}

P3(){
    while(true){
        P(offerEven);
            P(mutex);
                geteven();
            V(mutex);
        V(empty);
        counteven();
    }
}
```