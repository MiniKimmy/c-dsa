using System;
using System.Collections.Generic;

namespace bfs1
{
    class BFS
    {
        bool[] marked;  //��¼�Ƿ���start��ͨ
        int[] from;     //��¼��һ�������Ķ���KEY
        int start;      //���

        //����д,Ĭ��ֱ��base
        private class MyGraph : SparseGraph.Graph 
        {
            public MyGraph(string filename, bool IsXML = true) : base(filename, IsXML){}
        }

        public BFS(string xmlPath,int start)
        {
            //���start���
            if(start < 0){
                Console.WriteLine("start������Ϊ����");
                return;
            }

            //����XML�ļ�����ͼ��MyGraph��Ĭ�Ϲ����ͼ��
            MyGraph graph = new MyGraph(xmlPath);

            //�ٴμ��ͼ������
            if (start > graph.GetVerticesCount() 
                || graph.GetVerticesCount() == 0 
                || graph.GetEdgeCount() == 0) return;

            this.start = start;
            this.marked = new bool[graph.GetVerticesCount()];
            this.from = new int[graph.GetVerticesCount()];

            //��������������ͨ
            this.marked[start] = true;

            //��ʼֵ��from[]ȫ������Ϊ-1�������δ�ҵ��������һ������
            for (int i = 0; i < graph.GetVerticesCount(); i++){
                this.from[i] = -1;
            }

            //��ͼ����start��ͨ��marked[]��from[]
            BondingConnect_bfs(graph);

            //����from[start]������(�Ȱ���������ٰ�����)
            this.from[start] = start;
        }

        /// <summary>
        /// ��·��
        /// </summary>
        private void BondingConnect_bfs(MyGraph graph)
        {
            Queue<int> Q = new Queue<int>();
            Q.Enqueue(this.start);
            while(Q.Count != 0)
            {
                int key = Q.Dequeue();
                var nodes = graph.KeyList[key];
                foreach (var item in nodes)
                {
                    if(this.from[item] == -1 && item != this.start)
                    {
                        Q.Enqueue(item);
                        this.from[item] = key;
                        this.marked[item] = true;
                    }
                }
            }
        }

        /// <summary>
        /// ��ȡ·��,����Stack<int>
        /// </summary>
        /// <param name="destination">�յ��KEY</param>
        /// <returns></returns>
        public Stack<int> GetPath(int destination)
        {
            if (this.marked[destination] == false) return null;

            Stack<int> ret = new Stack<int>();
            for (int i = destination; i != this.start; i = this.from[i])
            {
                ret.Push(i);
            }
            ret.Push(this.start);
            return ret;
        }
    }
}
