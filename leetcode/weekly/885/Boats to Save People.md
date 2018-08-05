## Q885.Boats to Save People

The i-th person has weight people[i], and each boat can carry a maximum weight of limit.

Each boat carries at most 2 people at the same time, provided the sum of the weight of those people is at most limit.

Return the minimum number of boats to carry every given person.  (It is guaranteed each person can be carried by a boat.)



**Example 1:**
```
Input: people = [1,2], limit = 3
Output: 1
Explanation: 1 boat (1, 2)
```

**Example 2:**
```
Input: people = [3,2,2,1], limit = 3
Output: 3
Explanation: 3 boats (1, 2), (2) and (3)
```

**Example 3:**
```
Input: people = [3,5,3,4], limit = 5
Output: 4
Explanation: 4 boats (3), (3), (4), (5)
```

**Note:**<br/>
    1 <= people.length <= 50000 <br/>
    1 <= people[i] <= limit <= 30000 <br/>

## hints:
![可类比这里](../../leetcode/easy/680/): Leetcode的一道题.
```
   ------Collision-pointers------
   1.quick sort first and I'd believe the ascending order is better.

   Like:   small     ...      big
          left->              <-right

   2.left-pointer and right-pointer running at the same time
   3.let right people get on the boat first, then try to allow left people get on the boat.
   And the troble comes as follows:
        A. After the left people getting on, and if the boat is overweight, so just let right people leave alone.
        B. If the boat wasn't still full, it means this time the left person on the boat can leave althougt we dont know whether it can take one more person, it definitly can take at least the left person who have gotten on this boat.
        C. So the last problem is that, we need to mark a flag to insure the previous boat is whether still have people or not.
    4. And one more caution is that: check the boat whether still have people on the final boat.
```

## Solutions

``` csharp
#region
void swap(int* arr,int i ,int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void qSort(int* people, int left, int right)
{
    if(left >= right){
        insertSort(people,left,right);
        return ;
    }

    int i = left + 1;
    int j = right;

    while(true){
        while(i<=right && people[i] < people[left]) ++i;
        while(j>=left + 1 && people[j] >= people[left]) --j;
        if(i>j) break;
        swap(people,i,j);
        ++i;
        --j;
    }
    swap(people,left,j);

    qSort(people,left,j-1);
    qSort(people,j+1,right);
    return;
}

void insertSort(int* arr,int left,int right){
    for(int i = left;i<=right;i++){
        int pos = i;
        int temp = arr[i];
        for(int j = i-1; j>= left && arr[j] > temp;j--){
            arr[j+1] = arr[j];
            pos = j;
        }
        if(pos != i) arr[i] = temp;
    }
}
#endregion

int numRescueBoats(int* people, int peopleSize, int limit) {
    if(people == NULL || peopleSize == 0) return 0;

    qSort(people,0,peopleSize-1);
    int filter = 0;
    int ret = 0;
    int left = 0;
    int right = peopleSize-1;
    int flag = 0;

    while(left<right){
        int pre = filter;

        filter = flag ==1
            ? pre + people[left] + people[right]
            : people[left] + people[right];
        if(filter > limit){
           --right;
           ++ret;
           flag = 0;
        }else if(filter < limit){
            ++left;
            flag = 1;
            filter = pre + people[left];
        }else{
            ++left;
            --right;
            ++ret;
            flag = 0;
        }
    }

    return left==right?ret+1:ret; //watch out the final boat.
}
```
