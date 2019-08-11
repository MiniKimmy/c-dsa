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
        /// 读取Graph数据文件构造图(默认是XML文件读取)
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
        /// 手动添加顶点
        /// </summary>
        /// <param name="vertices">需要顶点的总个数</param>
        public Graph(int vertices = 0)
        {
            this.Vertices = vertices;
            this.KeyList = new List<List<int>>(vertices);
            this.Edge = 0;
        }

        /// <summary>
        /// text文件:第一行是顶点个数读取，第二行开始都是是2个顶点的KEY，左边是v右边的w，空格隔开
        /// </summary>
        /// <param name="textPath">文件路径</param>
        private void ReadTextPath(string textPath)
        {
            using (TextReader text = File.OpenText(textPath))
            {
                string line;

                //第一行读取顶点个数
                if ((line = text.ReadLine()) != null)
                {
                    this.Vertices = int.Parse(line);
                    this.KeyList = new List<List<int>>(this.Vertices);
                }

                //后面直接读取顶点v 和 w
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
        /// XML文件里含‘VerticesCount’标签和（‘Group’ + 【‘ID’ X 2】）组合的标签
        /// </summary>
        /// <param name="xmlPath"></param>
        public void ReadXmlPath(string xmlPath)
        {
            using (TextReader text = File.OpenText(xmlPath))
            {
                var doc = XDocument.Load(text);
                var root = doc.Root;

                //读取顶点总个数
                this.Vertices = (int)root.Element("VerticesCount");
                this.KeyList = new List<List<int>>(this.Vertices);

                //拿到所有“Group”名字的XElement
                var groups = root.Descendants("Group");
                foreach (var item in groups)
                {
                    int v = 0;
                    int w = 0;
                    int index = 0;
                    foreach (var item1 in item.Elements())
                    {
                        //读取第一个顶点KEY
                        if (index == 0){
                            v = (int)item1;
                        }
                        //读取第二个顶点KEY
                        else{
                            w = (int)item1;
                        }
                        index++;
                    }
                    this.AddEdge(v, w);//把这两个顶点连接
                }
            }
        }


        /// <summary>
        /// 添加2个顶点边
        /// </summary>
        /// <param name="v">第一个顶点</param>
        /// <param name="w">第二个顶点</param>
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
        /// 返回顶点总个数
        /// </summary>
        /// <returns></returns>
        public int GetVerticesCount()
        {
            return this.Vertices;
        }

        /// <summary>
        /// 返回边总个数
        /// </summary>
        /// <returns></returns>
        public int GetEdgeCount()
        {
            return this.Edge;
        }

        /// <summary>
        /// 遍历Graph
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
