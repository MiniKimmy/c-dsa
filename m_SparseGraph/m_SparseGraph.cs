using System;
using System.Collections.Generic;
using System.IO;

interface IGraph<out T>
{
    void CreateGraph(string filename);
    void AddEdge(int v, int w);
    int GetVerticesCount();
    int GetEdgeCount();
}

namespace m_Graph01
{
    abstract class AdjacencyList_Graph : IGraph<AdjacencyList_Graph>
    {
        private List<List<int>> bag;
        public int Edge { get ; set; }
        public int Vertices { get; set; }
        public List<List<int>> Bag
        {
            get
            {
                return bag;
            }
            set
            {
                bag = value;
                for (int i = 0; i < this.Vertices; i++)
                {
                    this.bag.Add(new List<int>());
                }
            }

        }

        public AdjacencyList_Graph(int vertices = 0)
        {
            this.Vertices = vertices;
            this.Bag = new List<List<int>>(vertices);
            this.Edge = 0;
        }

        /// <summary>
        /// ͨ���ļ���ȡGraph
        /// �ļ����ݸ�ʽ:����һ���Ƕ��������ȡ�������ź���ֱ���2�������KEY�������v�ұߵ�w���ո����
        /// </summary>
        /// <param name="filename">�ļ�·��</param>
        public void CreateGraph(string filename)
        {
            using (TextReader text = File.OpenText(filename))
            {
                string line;

                //��һ�ж�ȡ�������
                if ((line = text.ReadLine()) != null)
                {
                    this.Vertices = int.Parse(line);
                    this.Bag = new List<List<int>>(this.Vertices);
                }
                while ((line = text.ReadLine()) != null)
                {
                    string[] str = line.Split(' ');
                    if (str.Length == 2)
                    {
                        AddEdge(int.Parse(str[0]), int.Parse(str[1]));
                    }
                }
            }
        }

        /// <summary>
        /// ���2�������
        /// </summary>
        /// <param name="v">��һ������</param>
        /// <param name="w">�ڶ�������</param>
        public void AddEdge(int v, int w)
        {
            if(v < this.Vertices && w < this.Vertices)
            {
                this.Bag[v].Insert(0, w);
                this.Bag[w].Insert(0, v);
                this.Edge++;
            }
        }

        /// <summary>
        /// ���ض����ܸ���
        /// </summary>
        /// <returns></returns>
        public int GetVerticesCount()
        {
            return this.Vertices;
        }

        /// <summary>
        /// ���ر��ܸ���
        /// </summary>
        /// <returns></returns>
        public int GetEdgeCount()
        {
            return this.Edge;
        }

        /// <summary>
        /// ����Graph
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            String ret = this.Vertices + " Vertices, " + this.Edge + " Edge\n";
            for (int i = 0; i < this.Vertices; i++)
            {
                ret += string.Format("{0} : ", i);
                foreach (var item in this.Bag[i])
                {
                    ret += string.Format("{0} ", item);
                }
                ret += "\n";
            }
            return ret;
        }
    }
}
