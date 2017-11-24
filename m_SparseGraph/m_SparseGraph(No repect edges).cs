using System;
using System.Collections.Generic;
using System.IO;

interface IGraph<out T>
{
    void AddEdge(int v, int w);
    int GetVerticesCount();
    int GetEdgeCount();
}

namespace SeparseGraph01
{
    class SeparseGraph : IGraph<SeparseGraph>
    {
        public int Edge { get; private set; }
        public int Vertices { get; set; }
        private List<List<int>> bag;
        public List<List<int>> Bag
        {
            get { return bag; }
            set
            {
                bag = value;
                for (int i = 0; i < this.Vertices; i++)
                {
                    bag.Add(new List<int>());
                }
            }
        }

        public SeparseGraph(int v = 0)
        {
            this.Vertices = v;
            this.Edge = 0;
            this.Bag = new List<List<int>>();
        }

        /// <summary>
        /// text���ݸ�ʽ:��һ���Ƕ��������ȡ���ڶ��п�ʼ����2�������KEY�������v�ұߵ�w���ո����
        /// </summary>
        /// <param name="textPath">text�ļ�·��</param>
        public void ReadTextPath(string textPath)
        {
            using (TextReader text = File.OpenText(textPath))
            {
                string line;

                //��һ�ж�ȡ�������
                if ((line = text.ReadLine()) != null)
                {
                    this.Vertices = int.Parse(line);
                    this.Bag = new List<List<int>>(this.Vertices);
                }

                //�ڶ��п�ʼ��ȡ����KEY
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
        /// ��ӱߵ����ظ���ӱ�
        /// </summary>
        /// <param name="v">��һ������</param>
        /// <param name="w">�ڶ�������</param>
        public void AddEdge(int v, int w)
        {
            if(v < this.Vertices && w < this.Vertices)
            {
                bool flag = true;
                foreach (var item in this.bag[v])
                {
                    if(item == w)
                    {
                        flag = false;
                    }
                }
                if (flag)
                {
                    this.bag[v].Insert(0, w);
                    this.Edge++;
                }
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
