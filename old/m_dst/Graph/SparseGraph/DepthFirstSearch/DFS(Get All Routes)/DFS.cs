using m_SparseGraph;

namespace dfs
{
    /// <summary>
    /// 读取一次图 + 一个起点，获取所有能走的路线
    /// </summary>
    class DFS
    {
        bool[] marked;   //记录是否连通
        int[][] route;   //记录当前点-->其他点的所有路线
        int[] count;     //记录route第2维数组的有效元素个数

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

            this.count = new int[graph.GetVerticesCount()];
            this.marked = new bool[graph.GetVerticesCount()];
            this.route = new int[graph.GetVerticesCount()][];

            //marked与start连通的顶点
            BondingConnect(graph, start);

            //match与start连通的顶点的路线
            for (int i = 0; i < graph.GetVerticesCount(); i++)
            {
                this.route[i] = new int[graph.GetVerticesCount()];
                GetPath(graph, start, i);
            }
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
                if (marked[item] == false) BondingConnect(graph, item);
            }
        }

        /// <summary>
        /// 记录存储'起点->终点'的路线
        /// </summary>
        /// <param name="start">起点</param>
        /// <param name="end">终点</param>
        private void GetPath(Graph graph, int start, int end)
        {
            var Current = graph.Bag[start];
            this.route[end][count[end]++] = start;

            if (start == end) return;
            else
            {
                foreach (var item in Current)
                {
                    for (int i = 0; i < this.count[end]; i++)
                    {
                        if (item == this.route[end][i]) break;

                        if (i >= count[end] - 1 && item != this.route[end][i])
                        {
                            GetPath(graph, item, end);
                            if (this.route[end][count[end] - 1] == end) return;
                            else count[end]--;
                        }
                    }
                }
            }
        }

        /// <summary>
        /// 获取路线
        /// </summary>
        /// <param name="destination">终点</param>
        /// <returns></returns>
        public int[] GetRoute(int destination)
        {
            int[] ret = new int[count[destination]];
            for (int i = 0; i < this.count[destination]; i++)
            {
                ret[i] = this.route[destination][i];
            }
            return ret;
        }

        /// <summary>
        /// 获取到终点所走的顶点数
        /// </summary>
        /// <param name="destination">终点</param>
        /// <returns></returns>
        public int GetDistance(int destination)
        {
            return this.count[destination];
        }

        /// <summary>
        /// 该点是否与start连通
        /// </summary>
        /// <param name="destination">终点</param>
        /// <returns></returns>
        public bool IsConnect(int destination)
        {
            return this.marked[destination];
        }
    }        
}
