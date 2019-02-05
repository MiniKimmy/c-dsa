## 83. 股票的最大利润
[这里](https://www.acwing.com/problem/content/79/)
假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖交易该股票可能获得的利润是多少？

**Example :**
```
Input:[9, 11, 8, 5, 7, 12, 16, 14]
Output:11
Explanation:在价格为5的时候买入并在价格为16时卖出，则能收获最大的利润11。
```
## hints
```
    低价买入，高价卖出
    1.按今天的价格先卖出去
        * 如果利润比上次高就记录
    2.然后,今天的价格是不是比前面的价格便宜，是就买进
```
## Solution
``` c
int maxDiff(int* nums, int numsSize) {
    if(!nums || numsSize <= 0 ) return 0;

    int maxProfit = 0;
    int buy = nums[0];

    for(int i = 1;i<numsSize;++i){
        int profit = nums[i] - buy;
        if(maxProfit < profit) maxProfit = profit;
        if(buy > nums[i]) buy = nums[i];
    }

    return maxProfit;
}
```