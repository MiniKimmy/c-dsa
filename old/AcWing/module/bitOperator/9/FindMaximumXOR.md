## 421. Maximum XOR of Two Numbers in an Array
[这里](https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/)

## Solution
``` csharp
public class Solution {

    public struct Node{
        public int[] son;
    }

    public int FindMaximumXOR(int[] nums) {

        List<Node> nodes = new List<Node>();
        nodes.Add(new Node(){son = new int[2]});

        for(int i = 0;i<nums.Length;++i){
            int p = 0;
            for(int j = 30;j >= 0;--j){
                int t = nums[i] >> j & 1;
                if(nodes[p].son[t] == 0){
                    Node item = new Node(){ son = new int[2]};
                    nodes.Add(item);
                    nodes[p].son[t] = nodes.Count - 1;
                }
                p = nodes[p].son[t];
            }
        }

        int ret = 0;
        for(int i = 0;i<nums.Length;++i)
        {
            int p = 0;
            int max_xor = 0;

            for(int j = 30; j >= 0;--j)
            {
                int t = nums[i] >> j & 1;
                int _t = t == 1?0:1;
                if(nodes[p].son[_t] != 0)
                {
                    max_xor += 1 << j;
                    p = nodes[p].son[_t];
                }else{
                    p = nodes[p].son[t];
                }
            }

            ret = ret>max_xor?ret:max_xor;
        }

        return ret;
    }
}
```