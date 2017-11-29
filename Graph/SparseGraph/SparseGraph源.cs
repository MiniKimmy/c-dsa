using System;
using System.Collections.Generic;
using System.IO;
using System.Xml.Linq;

namespace SparseGraph
{
    public interface IGraph<out T>
    {
        void AddEdge(int v, int w);
        int GetVerticesCount();
        int GetEdgeCount();
    }

    public abstract class Graph : IGraph<Graph>
    {
        private List<List<int>> keyList;
        public int Edge { get; set; }
        public int Vertices { get; set; }
        public List<List<int>> KeyList
        {
            get{
                return keyList;
            }
            set{
                keyList = value;
                for (int i = 0; i < this.Vertices; i++){
                    this.keyList.Add(new List<int>());
                }
            }
        }

        /// <summary>
        /// ��ȡGraph�����ļ�����ͼ(Ĭ����XML�ļ���ȡ)
        /// </summary>
        public Graph(string filename,bool IsXML = true)
        {
            this.Edge = 0;
            if(IsXML == true){
                ReadXmlPath(filename);
            }
            else{
                ReadTextPath(filename);
            }
        }

        /// <summary>
        /// �ֶ���Ӷ���
        /// </summary>
        /// <param name="vertices">��Ҫ������ܸ���</param>
        public Graph(int vertices = 0)
        {
            this.Vertices = vertices;
            this.KeyList = new List<List<int>>(vertices);
            this.Edge = 0;
        }

        /// <summary>
        /// text�ļ�:��һ���Ƕ��������ȡ���ڶ��п�ʼ������2�������KEY�������v�ұߵ�w���ո����
        /// </summary>
        /// <param name="textPath">�ļ�·��</param>
        private void ReadTextPath(string textPath)
        {
            using (TextReader text = File.OpenText(textPath))
            {
                string line;

                //��һ�ж�ȡ�������
                if ((line = text.ReadLine()) != null)
                {
                    this.Vertices = int.Parse(line);
                    this.KeyList = new List<List<int>>(this.Vertices);
                }

                //����ֱ�Ӷ�ȡ����v �� w
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
        /// XML�ļ��ﺬ��VerticesCount����ǩ�ͣ���Group�� + ����ID�� X 2������ϵı�ǩ
        /// </summary>
        /// <param name="xmlPath"></param>
        public void ReadXmlPath(string xmlPath)
        {
            using (TextReader text = File.OpenText(xmlPath))
            {
                var doc = XDocument.Load(text);
                var root = doc.Root;

                //��ȡ�����ܸ���
                this.Vertices = (int)root.Element("VerticesCount");
                this.KeyList = new List<List<int>>(this.Vertices);

                //�õ����С�Group�����ֵ�XElement
                var groups = root.Descendants("Group");
                foreach (var item in groups)
                {
                    int v = 0;
                    int w = 0;
                    int index = 0;
                    foreach (var item1 in item.Elements())
                    {
                        //��ȡ��һ������KEY
                        if (index == 0){
                            v = (int)item1;
                        }
                        //��ȡ�ڶ�������KEY
                        else{
                            w = (int)item1;
                        }
                        index++;
                    }
                    this.AddEdge(v, w);//����������������
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
            if (v < this.Vertices && w < this.Vertices)
            {
                this.KeyList[v].Insert(0, w);
                this.KeyList[w].Insert(0, v);
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
                foreach (var item in this.KeyList[i])
                {
                    ret += string.Format("{0} ", item);
                }
                ret += "\n";
            }
            return ret;
        }
    }
}
