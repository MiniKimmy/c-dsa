using System;
using m_SparseGraph;

namespace m_dfs
{
    //邻接表Graph(住：导入的是该文件夹的m_SparseGraph邻接表)
    class Graph : SparseGraph
    {
        public Graph(int vertices = 0) : base(vertices){ }
    }

    class DFS
    {
        bool[] marked;
        int[] route;
        int count_route;   //路线经过的顶点个数

        public DFS(SparseGraph graph)
        {
            this.marked = new bool[graph.GetVerticesCount()];
            this.route = new int[graph.GetVerticesCount()];
            count_route = 0;
        }

        /// <summary>
        /// 检查是否连通（检验参数、直接打印）
        /// </summary>
        /// <param name="graph"></param>
        /// <param name="start">从该点开始检查</param>
        public void DFS_CheckConnected(Graph graph, int start)
        {
            if(graph == null)
            {
                throw new ArgumentNullException();
            }

            if (start < 0 || start > graph.GetVerticesCount() || graph.GetVerticesCount() == 0) return;
            CheckConnected(graph, start);
            Traverse_marked();                           //打印
            for (int i = 0; i < this.marked.Length; i++) //清零
            {
                this.marked[i] = false;
            }
        }

        /// <summary>
        /// 检查是否连通
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
        /// 查询路线（直接打印路线）
        /// </summary>
        /// <param name="start">起始点</param>
        /// <param name="end">终点</param>
        public void DFS_GetPath(Graph graph, int start, int end)
        {
            if(graph == null)
            {
                throw new ArgumentNullException();
            }

            if (start < 0 || end < 0 || start > graph.GetEdgeCount() || end > graph.GetEdgeCount() || graph.GetEdgeCount() == 0 || graph.GetEdgeCount() == 0) return;
            GetPath(graph, start, end);
            Console.WriteLine("{0} to {1} : ",start, end);
            Traverse_route();       //打印
            this.count_route = 0;   //清零
        }

        /// <summary>
        /// 查询路径
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
        /// 打印marked
        /// </summary>
        private void Traverse_marked()
        {
            for (int i = 0; i < marked.Length; i++)
            {
                Console.Write("{0} ",marked[i]);
            }
        }

        /// <summary>
        /// 打印route
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
