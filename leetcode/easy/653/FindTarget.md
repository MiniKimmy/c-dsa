## 653. Two Sum IV - Input is a BST

Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.

**Example 1:**
```
Input:
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
```
**Example 2:**
```
Input:
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False
```

## hints
```
    hashTable && pre-traverse.
    1. judge is whether this node is ok. else Add to Dictionary<int,?>
    ps: '?' type means that any type is ok, we just want mark the 'key' is whether it exists or not.

    2. why use pre-traverse? cause we had known the top section of the tree,and search deep direction.
    3. the 'key' is 'int' type, dic.Add[target - root.val], so we just check the existance of [root.val].
    Caution: BST has minor KEY, so I choose Dictionary but not int[].
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

    public void hashSearch(TreeNode root, int k, Dictionary<int, int> dic, ref bool ret){
        if(root == null){
            return ;
        }

        if(!ret){
            if(dic.ContainsKey(root.val)){
                ret = true;
                return;
            }

            dic.Add(k - root.val,1);
            hashSearch(root.left,k, dic, ref ret);
            hashSearch(root.right,k, dic, ref ret);
        }
    }

    public bool FindTarget(TreeNode root, int k) {
        Dictionary<int, int> dic = new Dictionary<int, int>();
        bool ret = false;

        hashSearch(root,k , dic, ref ret);

        return ret;
    }
}
```