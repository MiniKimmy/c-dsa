using m_SparseGraph;

namespace dfs1
{
    class DFS
    {
        bool[] marked;   //记录是否连通
        int[] from;      //记录上一个结点
        int start;       //起点

        public class Graph : SparseGraph
        {
            public Graph() { }
            public Graph(int v = 0) : base(v) { }
        }

        /// <summary>
        /// 读取xml文件生成图并绑定连通
        /// </summary>
        /// <param name="xmlPath">读取含图数据的XML文件</param>
        /// <param name="start">起点位置</param>
        public DFS(string xmlPath, int start)
        {
            //检测参数start
            if (start < 0) return;

            Graph graph = new Graph();
            GraphData.ReadXmlPath(xmlPath, graph);

            //检测刚读取的GraphData数据
            if (start > graph.GetVerticesCount() || graph.GetVerticesCount() == 0) return;

            this.marked = new bool[graph.GetVerticesCount()];
            this.from = new int[graph.GetVerticesCount()];
            this.start = start;

            //marked与start连通的顶点
            BondingConnect(graph, start);
        }

        /// <summary>
        /// 检查绑定与start连通的点（深度遍历）
        /// </summary>
        /// <param name="start">起点</param>
        private void BondingConnect(Graph graph, int start)
        {
            this.marked[start] = true;
            foreach (var item in graph.Bag[start])
            {
                if (marked[item] == false)
                {
                    this.from[item] = start;
                    BondingConnect(graph, item);
                }
            }
        }

        /// <summary>
        /// 获取路径
        /// </summary>
        /// <param name="destination">终点</param>
        /// <returns></returns>
        public string GetPath(int destination)
        {
            if (this.marked[destination] == false) return null;
            string ret = ""; 
            for (int i = destination; i!= start ; i = this.from[i])
            {
                ret += i + "<-";
            }
            ret += this.start;
            return ret;
        }
    }
}
