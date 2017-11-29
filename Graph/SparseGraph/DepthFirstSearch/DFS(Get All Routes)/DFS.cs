using m_SparseGraph;

namespace dfs
{
    /// <summary>
    /// ��ȡһ��ͼ + һ����㣬��ȡ�������ߵ�·��
    /// </summary>
    class DFS
    {
        bool[] marked;   //��¼�Ƿ���ͨ
        int[][] route;   //��¼��ǰ��-->�����������·��
        int[] count;     //��¼route��2ά�������ЧԪ�ظ���

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

            this.count = new int[graph.GetVerticesCount()];
            this.marked = new bool[graph.GetVerticesCount()];
            this.route = new int[graph.GetVerticesCount()][];

            //marked��start��ͨ�Ķ���
            BondingConnect(graph, start);

            //match��start��ͨ�Ķ����·��
            for (int i = 0; i < graph.GetVerticesCount(); i++)
            {
                this.route[i] = new int[graph.GetVerticesCount()];
                GetPath(graph, start, i);
            }
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
                if (marked[item] == false) BondingConnect(graph, item);
            }
        }

        /// <summary>
        /// ��¼�洢'���->�յ�'��·��
        /// </summary>
        /// <param name="start">���</param>
        /// <param name="end">�յ�</param>
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
        /// ��ȡ·��
        /// </summary>
        /// <param name="destination">�յ�</param>
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
        /// ��ȡ���յ����ߵĶ�����
        /// </summary>
        /// <param name="destination">�յ�</param>
        /// <returns></returns>
        public int GetDistance(int destination)
        {
            return this.count[destination];
        }

        /// <summary>
        /// �õ��Ƿ���start��ͨ
        /// </summary>
        /// <param name="destination">�յ�</param>
        /// <returns></returns>
        public bool IsConnect(int destination)
        {
            return this.marked[destination];
        }
    }        
}
