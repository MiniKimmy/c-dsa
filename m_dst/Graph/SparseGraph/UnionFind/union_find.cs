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
        /// ����p��q
        /// </summary>
        /// <param name="p">��Ҫ���ӵĵ�һ������</param>
        /// <param name="q">��Ҫ���ӵĵڶ�������</param>
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
        /// ����p��Root(���Ż����Ĳ���)
        /// </summary>
        /// <param name="p">��Ҫ���ҵĶ���</param>
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
        /// �ж�p��q�Ƿ�����
        /// </summary>
        /// <param name="p">��һ������</param>
        /// <param name="q">�ڶ�������</param>
        /// <returns></returns>
        bool IsConnected(int p ,int q)
        {
            return Find(p) == Find(q);
        }

        /// <summary>
        /// ��ȡ��ͨ��������
        /// </summary>
        /// <returns></returns>
        public int GetCount()
        {
            return this.Count;
        }
    }
}
