using m_SparseGraph;

namespace dfs1
{
    class DFS
    {
        bool[] marked;   //��¼�Ƿ���ͨ
        int[] from;      //��¼��һ�����
        int start;       //���

        public class Graph : SparseGraph
        {
            public Graph() { }
            public Graph(int v = 0) : base(v) { }
        }

        /// <summary>
        /// ��ȡxml�ļ�����ͼ������ͨ
        /// </summary>
        /// <param name="xmlPath">��ȡ��ͼ���ݵ�XML�ļ�</param>
        /// <param name="start">���λ��</param>
        public DFS(string xmlPath, int start)
        {
            //������start
            if (start < 0) return;

            Graph graph = new Graph();
            GraphData.ReadXmlPath(xmlPath, graph);

            //���ն�ȡ��GraphData����
            if (start > graph.GetVerticesCount() || graph.GetVerticesCount() == 0) return;

            this.marked = new bool[graph.GetVerticesCount()];
            this.from = new int[graph.GetVerticesCount()];
            this.start = start;

            //marked��start��ͨ�Ķ���
            BondingConnect(graph, start);
        }

        /// <summary>
        /// ������start��ͨ�ĵ㣨��ȱ�����
        /// </summary>
        /// <param name="start">���</param>
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
        /// ��ȡ·��
        /// </summary>
        /// <param name="destination">�յ�</param>
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
