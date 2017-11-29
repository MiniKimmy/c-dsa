using System;
using System.Collections.Generic;

namespace bfs1
{
    class BFS
    {
        bool[] marked;  //记录是否与start连通
        int[] from;     //记录上一个经过的顶点KEY
        int start;      //起点

        //不重写,默认直接base
        private class MyGraph : SparseGraph.Graph 
        {
            public MyGraph(string filename, bool IsXML = true) : base(filename, IsXML){}
        }

        public BFS(string xmlPath,int start)
        {
            //检查start起点
            if(start < 0){
                Console.WriteLine("start不可以为负数");
                return;
            }

            //根据XML文件生成图（MyGraph即默认构造的图）
            MyGraph graph = new MyGraph(xmlPath);

            //再次检查图的数据
            if (start > graph.GetVerticesCount() 
                || graph.GetVerticesCount() == 0 
                || graph.GetEdgeCount() == 0) return;

            this.start = start;
            this.marked = new bool[graph.GetVerticesCount()];
            this.from = new int[graph.GetVerticesCount()];

            //起点自身和自身连通
            this.marked[start] = true;

            //初始值的from[]全部设置为-1，即标记未找到最近的上一个顶点
            for (int i = 0; i < graph.GetVerticesCount(); i++){
                this.from[i] = -1;
            }

            //绑定图中与start连通的marked[]和from[]
            BondingConnect_bfs(graph);

            //起点的from[start]即自身(先绑定其他最后再绑定自身)
            this.from[start] = start;
        }

        /// <summary>
        /// 绑定路线
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
        /// 获取路径,返回Stack<int>
        /// </summary>
        /// <param name="destination">终点的KEY</param>
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
