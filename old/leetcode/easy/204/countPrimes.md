## 204. Count Primes

Count the number of prime numbers less than a non-negative number, n.

**Example:**
```
Input: 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
```

## hints
```
    use i*i  instead of sqrt(n) !
```

## Solution
* Too Slowly. Need to refine!
``` c
bool isSusu(int n){
    //int len = sqrt(n);   //expensive
    for(int i = 2;i*i<=n;i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

int countPrimes(int n) {
    if(n<=1) return 0;

    int ret =0 ;
    for(int i = 2;i<n;i++){
        if(isSusu(i)){
            ret++;
        }
    }
    return ret;
}

```