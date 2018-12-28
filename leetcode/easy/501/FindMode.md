## 501.Find Mode in Binary Search Tree

Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.

Assume a BST is defined as follows:
    The left subtree of a node contains only nodes with keys less than or equal to the node's key.
    The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
    Both the left and right subtrees must also be binary search trees.


```
For example:
Given BST [1,null,2,2],
   1
    \
     2
    /
   2
return [2].
```
Note: If a tree has more than one mode, you can return them in any order.

## hints
```
    1.dictionay<int,int> hash --> count each "key" the occurs times.
    2.for() find max times.
    3.for() find every "key" with max times as int[] return.
```

## Solution
``` csharp
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left;
 *     public TreeNode right;
 *     public TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public void dfs(TreeNode root,Dictionary<int,int> hash){
        if(root == null) return;
        if(hash.ContainsKey(root.val)){
            hash[root.val]++;
        }else{
            hash.Add(root.val,1);
        }

        dfs(root.left,hash);
        dfs(root.right,hash);
    }

    public int[] FindMode(TreeNode root) {
        Dictionary<int, int> hash = new Dictionary<int, int>();
        dfs(root,hash);

        int[] buffer = new int[hash.Count];
        int max = 0;

        foreach (var item in hash.Keys)
        {
                if(hash[item] > max)
                {
                    max = hash[item];
                }
        }

        int i = 0;
        foreach (var item in hash.Keys)
        {
                if(hash[item] == max)
                {
                    buffer[i++] = item;
                }
        }

        int[] ret = new int[i];
        for(int j = 0;j<i;++j){
            ret[j] = buffer[j];
        }
        return ret;
    }
}
```