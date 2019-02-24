
## hints
```
qSort将相同的数字放在一堆
```
## Solution
``` c
void swap(int* arr,int i,int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void qSort(int* arr, int l, int r)
{
    if(l >= r) return;

    int i = l+1;
    int j = r;
    int temp = arr[l];
    while(true)
    {
        while(i <= r && arr[i] <= temp) i++;
        while(j >= l+1 && arr[j] > temp) j--;
        if(i>j) break;
        swap(arr,i,j);
        ++i;
        --j;
    }

    swap(arr,l,j);
    qSort(arr,l,j-1);
    qSort(arr,j+1,r);
}

int singleNumber(int* nums, int numsSize) {
    qSort(nums,0,numsSize-1);

    int val = nums[0];
    int st = 0;
    for(int i = 0;i<numsSize-1;++i){
        if(nums[i] == nums[i+1]){
            i++;
        }
        else return nums[i];
    }

    return nums[numsSize-1];
}
```
## hints2
```
异或找不同
1.异或
    * 0不变，1相反
    * 相同就是0，不同就是1
ex:1 2 2 4 4
    2^2 = 0;
    4^4 = 0;
    0^1 = 1;
-->1^2^2^4^4 = 1;
```
## Solution2
``` csharp
public class Solution {
    public int SingleNumber(int[] nums) {
        int n = nums.Length;
        for(int i = 1;i<n;++i){
            nums[0] = nums[0] ^ nums[i];
        }

        return nums[0];
    }
}
```