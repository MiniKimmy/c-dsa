## 867.Transpose Matrix
Given a matrix A, return the transpose of A.

The transpose of a matrix is the matrix flipped over it's main diagonal, switching the row and column indices of the matrix.


Example 1:
```
Input: [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]
```
**Example 2:**
```
Input: [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]
```

**Note:**
```
    1 <= A.length <= 1000
    1 <= A[0].length <= 1000
```

## hints
```
     a[i][j] Transpose ->a[j][i]
     foreach: column
       foreach: row
```
## Solution

``` c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int** transpose(int** A, int ARowSize, int *AColSizes, int** columnSizes, int* returnSize) {
    if(A==NULL)return NULL;

    *columnSizes = (int*)malloc(sizeof(int) * (*AColSizes));
    int** ret = (int**)malloc(sizeof(int*) * (*AColSizes));

    for(int i = 0;i<ARowSize;i++){
        ret[i] = (int*)malloc(sizeof(int) * ARowSize);
        (*columnSizes)[i] = ARowSize;

        for(int j = 0;j<(*AColSizes);j++){
            ret[i][j] = A[j][i];
        }
    }

    *returnSize = *AColSizes;
    return ret;
}

```