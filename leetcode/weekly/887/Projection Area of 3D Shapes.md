## Q887.Projection Area of 3D Shapes

On a N * N grid, we place some 1 * 1 * 1 cubes that are axis-aligned with the x, y, and z axes.
Each value v = grid[i][j] represents a tower of v cubes placed on top of grid cell (i, j).
Now we view the projection of these cubes onto the xy, yz, and zx planes.

A projection is like a shadow, that maps our 3 dimensional figure to a 2 dimensional plane.
Here, we are viewing the "shadow" when looking at the cubes from the top, the front, and the side.

Return the total area of all three projections.

**Example1:**
```
Input: [[2]]
Output: 5
```

**Example2:**
```
Input: [[1,2],[3,4]]
Output: 17
```
**Explanation:**:
Here are the three projections ("shadows") of the shape made with each axis-aligned plane.
<br/>
<img src="https://raw.githubusercontent.com/MiniKimmy/c-dsa/master/leetcode/weekly/887/shadow.png" alt="can't find pic" width="800px">
<br/>

**Example3:**
```
Input: [[1,0],[0,2]]
Output: 8
```

**Example4:**
```
Input: [[1,1,1],[1,0,1],[1,1,1]]
Output: 14
```

**Example5:**
```
Input: [[2,2,2],[2,1,2],[2,2,2]]
Output: 21
```


**Note:**
    1 <= grid.length = grid[0].length <= 50
    0 <= grid[i][j] <= 50


## hints:
```
define: row    --> i
        column --> j

 1.top view: the elements' count of every i, but careful the element is 0
 2.front view: max element in each i
 3.left view: max element in each j
```

## Solutions

``` csharp
    public class Solution {
    public int ProjectionArea(int[][] grid) {
        if(grid == null) return 0;

        int top = 0;
        int front = 0;
        int left = 0;
        int n = grid.Length;

        //top
        for (int i = 0; i < n; i++)
        {
            int temp_t_max = 0;
            for (int j = 0; j < n; j++){
                if(grid[i][j] != 0){
                    temp_t_max++;
                }
            }
            top += temp_t_max;
        }

        //front
        for (int i = 0; i < n; i++){
            int temp_f_max = grid[i][0];
            for (int j = 1; j < n; j++)
            {
               if(grid[i][j] > temp_f_max)
               {
                    temp_f_max = grid[i][j];
               }
            }
            front += temp_f_max;
        }

        //left
        for (int i = 0; i < n; i++)
        {
            int temp_l_max = grid[0][i];
            for (int j = 1; j < n; j++)
            {
                if (grid[j][i] > temp_l_max)
                {
                    temp_l_max = grid[j][i];
                }
            }
            left += temp_l_max;
        }

        return top + left + front;
    }
}
```

