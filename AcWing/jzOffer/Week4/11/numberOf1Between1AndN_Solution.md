## 56. 从1到n整数中1出现的次数
[这里](https://www.acwing.com/problem/content/51/)
输入一个整数n，求从1到n这n个整数的十进制表示中1出现的次数。

**Example :**
```
Input:12
Output:5
Explanation:从1到12这些整数中包含“1”的数字有1，10，11和12，其中“1”一共出现了5次。
```
## hints
```
    模拟数数字，按位数，按住一个位不动。
    * ex:13015 ；5位数
    * 变成int[]:[1,3,0,1,5]
    * 先数万位:[1 _ _ _ _]
        (1).11000~11999 -- 【千位是1】000~999   -->1000个
        (2).10000~13015 -- 【千位是0】0000~3015 -->3016个
    * 这是二分成2边，左边万位[1],右边是一个四位数[ABCD]
    * 万位固定数到的结果 = 1*1000 + ABCD+1
        (1).这个ABCD只需要看A即可，因为A是另一半的头
    * 你可能会担心:10000~13015和11000~11999是不是重复数了？
        * ex:11000在这2个范围里面
        * 就是要重复数，11000有2个1，数2遍是正常的
        * 这种思维就是，不是一次性把1个数所有位都数一遍
        * 而是按照固定某个位是1，后面位的xxx全部都成立
        * 紧接着轮到固定某个位，可能与前面的数会重复，而这个重复是正常是
        * 因为前面固定的位数过之后就不会再管前面的位，继续数后面只需要考虑当前固定的位在哪个位置得出结果即可。
```
## Solution
``` c
int* getEachBit(int n, int* outLen)
{
    int* buffer = (int*)malloc(sizeof(int) * 10);
    int index = 0;

    while(n>0){
        buffer[index++] = n % 10;
        n /= 10;
    }

    int* ret = (int*)malloc(sizeof(int) * index);
    for(int i = 0;i<index;++i){
        ret[index-i-1] = buffer[i];

    }

    *outLen = index;
    return ret;
}

int numberOf1Between1AndN_Solution(int n) {
    int left = 0; int right = 0;

    int len = 0;
    int* nums = getEachBit(n, &len);
    int count = 0;

    // 当前分界处 i
    for(int i = 0;i<len; ++i){
        for(int j = 0;j<i;++j) left = left*10 + nums[j];

        int t = 1;
        for(int j = i+1;j<len;++j) {
            right = right *10 + nums[j];
            t *= 10;
        }

        count += t*left;

        if(nums[i] == 1){
            count += right+1;
        }

        if(nums[i] > 1){
            count += t;
        }

        left = 0;
        right = 0;
    }

    free(nums);
    return count;
}
```