using System.IO;
using System.Xml.Linq;
using System;
using System.Collections.Generic;

namespace dfs1
{
    class GraphData
    {
        /// <summary>
        /// ֻ��XML
        /// </summary>
        /// <param name="filename">XML·��</param>
        /// <param name="G">ͼ����</param>
        public static void ReadXmlPath(string xmlPath, dfs1.DFS.Graph G)
        {
            using (TextReader text = File.OpenText(xmlPath))
            {
                var doc = XDocument.Load(text);
                var root = doc.Root;

                //��ȡ�����ܸ���
                G.Vertices = (int)root.Element("VerticesCount");
                G.Bag = new List<List<int>>(G.Vertices);

                //�õ����С�Group�����ֵ�XElement
                var groups = root.Descendants("Group");
                foreach (var item in groups)
                {
                    int v = 0;
                    int w = 0;
                    int index = 0;
                    foreach (var item1 in item.Elements())
                    {
                        if (index == 0)
                        {
                            v = (int)item1;
                        }
                        else
                        {
                            w = (int)item1;
                        }
                        index++;
                    }
                    G.AddEdge(v, w);
                }
            }
            Console.WriteLine(G);
        }
    }
}
