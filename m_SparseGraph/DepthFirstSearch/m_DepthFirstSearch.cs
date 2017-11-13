using System;
using m_SparseGraph;

namespace m_dfs
{
    //�ڽӱ�Graph(ס��������Ǹ��ļ��е�m_SparseGraph�ڽӱ�)
    class Graph : SparseGraph
    {
        public Graph(int vertices = 0) : base(vertices){ }
    }

    class DFS
    {
        bool[] marked;
        int[] route;
        int count_route;   //·�߾����Ķ������

        public DFS(SparseGraph graph)
        {
            this.marked = new bool[graph.GetVerticesCount()];
            this.route = new int[graph.GetVerticesCount()];
            count_route = 0;
        }

        /// <summary>
        /// ����Ƿ���ͨ�����������ֱ�Ӵ�ӡ��
        /// </summary>
        /// <param name="graph"></param>
        /// <param name="start">�Ӹõ㿪ʼ���</param>
        public void DFS_CheckConnected(Graph graph, int start)
        {
            if(graph == null)
            {
                throw new ArgumentNullException();
            }

            if (start < 0 || start > graph.GetVerticesCount() || graph.GetVerticesCount() == 0) return;
            CheckConnected(graph, start);
            Traverse_marked();                           //��ӡ
            for (int i = 0; i < this.marked.Length; i++) //����
            {
                this.marked[i] = false;
            }
        }

        /// <summary>
        /// ����Ƿ���ͨ
        /// </summary>
        private void CheckConnected(Graph graph,int start)
        {
            this.marked[start] = true;
            foreach (var item in graph.Bag[start])
            {
                if (marked[item] == false) CheckConnected(graph, item);
            }
        }

        /// <summary>
        /// ��ѯ·�ߣ�ֱ�Ӵ�ӡ·�ߣ�
        /// </summary>
        /// <param name="start">��ʼ��</param>
        /// <param name="end">�յ�</param>
        public void DFS_GetPath(Graph graph, int start, int end)
        {
            if(graph == null)
            {
                throw new ArgumentNullException();
            }

            if (start < 0 || end < 0 || start > graph.GetEdgeCount() || end > graph.GetEdgeCount() || graph.GetEdgeCount() == 0 || graph.GetEdgeCount() == 0) return;
            GetPath(graph, start, end);
            Console.WriteLine("{0} to {1} : ",start, end);
            Traverse_route();       //��ӡ
            this.count_route = 0;   //����
        }

        /// <summary>
        /// ��ѯ·��
        /// </summary>
        private void GetPath(Graph graph,int start,int end)
        {
            var Current = graph.Bag[start];
            this.route[this.count_route++] = start;

            if (start == end) return;
            else
            {
                foreach (var item in Current)
                {
                    for (int i = 0; i < this.count_route; i++)
                    {
                        if (item == this.route[i]) break;

                        if (i >= this.count_route - 1 && item != this.route[i])
                        {
                            GetPath(graph,item, end);
                            if (this.route[this.count_route - 1] == end) return;
                            else this.count_route--;
                        }
                    }
                }
            }
        }

        /// <summary>
        /// ��ӡmarked
        /// </summary>
        private void Traverse_marked()
        {
            for (int i = 0; i < marked.Length; i++)
            {
                Console.Write("{0} ",marked[i]);
            }
        }

        /// <summary>
        /// ��ӡroute
        /// </summary>
        private void Traverse_route()
        {
            for (int i = 0; i < this.count_route; i++)
            {
                Console.Write("{0} ", this.route[i]);
            }
        }
    }
}
