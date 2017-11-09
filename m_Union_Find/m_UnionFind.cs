using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Unionfind01
{
    class UnionFind
    {
        private int Count { get; set; }
        public int[] Parent { get; private set; }
        public int[] Size { get; private set; }

        public UnionFind(int n)
        {
            this.Count = n;
            this.Parent = new int[n];
            this.Size = new int[n];
            for (int i = 0; i < n; i++)
            {
                this.Parent[i] = i;
                this.Size[i] = 1;
            }
        }

        /// <summary>
        /// 连接p和q
        /// </summary>
        /// <param name="p">需要连接的第一个顶点</param>
        /// <param name="q">需要连接的第二个顶点</param>
        public void WeightQuickUnion(int p,int q)
        {
            int pRoot = Find(p);
            int qRoot = Find(q);
            if (pRoot == qRoot) return;
            if(this.Size[pRoot] < this.Size[qRoot])
            {
                this.Parent[p] = qRoot;
                this.Size[qRoot] += this.Size[pRoot];
            }
            else
            {
                this.Parent[q] = pRoot;
                this.Size[pRoot] += this.Size[qRoot];
            }
            this.Count--;
        }

        /// <summary>
        /// 查找p的Root(并优化树的层数)
        /// </summary>
        /// <param name="p">需要查找的顶点</param>
        /// <returns></returns>
        private int Find(int p)
        {
            while(p != this.Parent[p])
            {
                this.Parent[p] = this.Parent[this.Parent[p]];
                p = this.Parent[p];
            }
            return p;
        }

        /// <summary>
        /// 判断p和q是否连接
        /// </summary>
        /// <param name="p">第一个顶点</param>
        /// <param name="q">第二个顶点</param>
        /// <returns></returns>
        bool IsConnected(int p ,int q)
        {
            return Find(p) == Find(q);
        }

        /// <summary>
        /// 获取连通分量总数
        /// </summary>
        /// <returns></returns>
        public int GetCount()
        {
            return this.Count;
        }
    }
}
