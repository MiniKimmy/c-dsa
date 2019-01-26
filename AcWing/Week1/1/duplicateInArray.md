## 13.找出数组中重复的数字
[这里](https://www.acwing.com/problem/content/14/)
给定一个长度为 n 的整数数组 nums，数组中所有的数字都在 0~n−1
的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

**Notice:**
* 如果某些数字不在 0~n−1的范围内，
* 或数组中不包含重复数字，则返回 -1
## hints
```
    1.出现的次数映射到hash记录
    2.返回结果只需要任意一个，所以出现次数>=2就立刻返回
    3.注意判断大小0~n-1的范围才记录
```
## Solution
``` c
int duplicateInArray(int* nums, int numsSize){
    int* hash = (int*)malloc(sizeof(int) * numsSize);
    for(int i = 0;i<numsSize;++i) hash[i] = 0;

    for(int i = 0;i<numsSize;++i){
        if(nums[i]>= numsSize || nums[i] < 0) return -1;
        hash[nums[i]]++;
    }

    for(int i = 0;i<numsSize;++i){
        if(hash[i] >= 2) return i;
    }

    return -1;
}
```
## hints2
```
    1.每次交换到一个正确的位置。修改Source数组
    2.已知值域是0~n-1,思考数组映射之外，还有映射排序。坑上的编号和坑上的值相等。
    3.注意这个swap,容易写错为（这种是错误的）
            int temp = nums[i];
            nums[i] = nums[nums[i]];
            nums[nums[i]] = temp;
    4.写while的时候，可以想一个特殊例子开始写：

        (1).坑的值是例子。[0]上的4，[4]上的1; 坑上的值与坑下标不一致.
        ______________________________________________________
坑位置: 0    1    2   3   4   5   6   7
坑的值: 4   xx   xx  xx   1   ..  ..

        (2).第[0]坑上的4，与第[4]的坑，交换--把4放到第[4]上

        ______________________________________________________
坑位置: 0    1    2   3   4   5   6   7
坑的值: 1   xx   xx  xx   4   ..  ..

       (3).第[0]坑上的1，重复(2)继续交换。即 第[0]坑上的1与第[1]坑上的数继续交换
       (4).直到遇到，要交换的坑已经有对应的数，这时候就出现重复.就返回这个重复的数。

    5.关于重复的问题的思想
        * 出现2次以上。
        * 坑的数量比数的数量少[抽屉原理]。（假设一个坑只放一个数）
```
## Solution2
``` c
/*时间O(n),空间O(1)*/
int duplicateInArray(int* nums, int numsSize){

    int duplicateInArray(int *nums, int numsSize){
    for(int i = 0;i<numsSize;++i){
        if(nums[i] < 0 || nums[i] >= numsSize) return -1;
    }

    for(int i = 0;i<numsSize;++i){
        while(i != nums[i] && nums[i] != nums[nums[i]] ) {
            int temp = nums[i];
            nums[i] = nums[nums[i]];
            nums[temp] = temp;
        }
        if(i != nums[i] && nums[i] == nums[nums[i]])
            return nums[i];
    }

    return -1;
}
}
```