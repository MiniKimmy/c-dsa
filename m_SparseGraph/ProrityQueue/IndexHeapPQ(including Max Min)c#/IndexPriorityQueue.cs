using System;

namespace m_pq
{
    class IndexPriorityQueue<T>
        where T: class,IComparable<T>
    {
        const int QUEUE_MAXSIZE = 15; //数组最大元素个数
        IndexPQType type;             //IndexPQ类型
        T[] queue;                    //源source[]
        int[] indexes;                //queue的index
        int[] reverse;                //indexex的相反数组
        int count;                    //元素总个数
        int queueCount;               //T[]的元素最大个数

        /// <summary>
        /// 初始化索引堆IndexHeap
        /// </summary>
        /// <param name="type">索引堆的类型</param>
        /// <param name="dataNum">传入源Data[]的元素个数</param>
        public IndexPriorityQueue(IndexPQType type,int? dataNum = null)
        {
            this.type = type;
            this.count = 0;
            this.indexes = new int[QUEUE_MAXSIZE + 1];
            this.reverse = new int[QUEUE_MAXSIZE + 1];
            this.queueCount = dataNum ?? QUEUE_MAXSIZE;
            this.queue = new T[this.queueCount + 1];
        }

        /// <summary>
        /// 上浮
        /// </summary>
        private void Swim()
        {
            int flag = this.indexes[count];
            if (this.type == IndexPQType.IndexMaxPQ)
            {
                while (flag / 2 != 0 && this.queue[count].CompareTo(this.queue[indexes[flag / 2]]) == 1)
                {
                    //换排名,reverse[]
                    int temp = this.reverse[indexes[flag]];
                    this.reverse[indexes[flag]] = flag / 2;
                    this.reverse[indexes[flag / 2]] = temp;

                    //换Key,indexex[]
                    temp = this.indexes[flag];
                    this.indexes[flag] = this.indexes[flag / 2];
                    this.indexes[flag / 2] = temp;
                    flag = flag / 2;
                }
            }
            else
            {
                while (flag / 2 != 0 &&
                    this.queue[count].CompareTo(this.queue[indexes[flag / 2]]) == -1)
                {
                    //换排名,reverse[]
                    int temp = this.reverse[indexes[flag]];
                    this.reverse[indexes[flag]] = flag / 2;
                    this.reverse[indexes[flag / 2]] = temp;

                    //换Key,indexex[]
                    temp = this.indexes[flag];
                    this.indexes[flag] = this.indexes[flag / 2];
                    this.indexes[flag / 2] = temp;
                    flag = flag / 2;
                }
            }
        }

        /// <summary>
        /// 下沉
        /// </summary>
        private void Sink()
        {
            int flag = 1;
            if (this.type == IndexPQType.IndexMaxPQ)
            {
                while (flag * 2 <= this.count)
                {
                    int key = flag * 2;
                    int mark = this.indexes[key];
                    var max_value = this.queue[mark];

                    if (key < this.count &&
                        max_value.CompareTo(this.queue[indexes[key + 1]]) == -1)
                    {
                        key++;
                        mark = this.indexes[key];
                        max_value = this.queue[mark];
                    }

                    if (this.queue[indexes[flag]].CompareTo(max_value) == -1)
                    {
                        //换排名
                        int temp = this.reverse[mark];
                        this.reverse[mark] = this.reverse[indexes[flag]];
                        this.reverse[indexes[flag]] = temp;

                        //换data_key
                        this.indexes[key] = this.indexes[flag];
                        this.indexes[flag] = mark;
                    }
                    flag = mark;
                }
            }
            else
            {
                while (flag * 2 <= this.count)
                {
                    int key = flag * 2;
                    int mark = this.indexes[key];
                    var max_value = this.queue[mark];

                    if (key < this.count &&
                        max_value.CompareTo(this.queue[indexes[key + 1]]) == 1)
                    {
                        key++;
                        mark = this.indexes[key];
                        max_value = this.queue[mark];
                    }

                    if (this.queue[indexes[flag]].CompareTo(max_value) == 1)
                    {
                        //换排名
                        int temp = this.reverse[mark];
                        this.reverse[mark] = this.reverse[indexes[flag]];
                        this.reverse[indexes[flag]] = temp;

                        //换data_key
                        this.indexes[key] = this.indexes[flag];
                        this.indexes[flag] = mark;
                    }
                    flag = mark;
                }
            }
        }

        /// <summary>
        /// 判断索引堆是否为空
        /// </summary>
        public bool IsEmpey()
        {
            if (this.count == 0) return true;
            else return false;
        }

        /// <summary>
        /// 判断索引堆是否已满
        /// </summary>
        public bool IsFull()
        {
            if (this.count == QUEUE_MAXSIZE) return true;
            else return false;
        }

        /// <summary>
        /// 插入新元素
        /// </summary>
        /// <param name="value">所添加的元素的对象</param>
        public void Insert(T value)
        {
            if (this.IsFull()) return;

            this.count++;
            this.queue[count] = value;
            this.indexes[count] = count;
            this.reverse[count] = count;
            Swim();
        }

        /// <summary>
        /// 删除索引堆的Root
        /// </summary>
        public void Delete()
        {
            //换排名,最后的排名和排名[1]的交换
            this.reverse[indexes[count]] = 1;
            //等于0即可相当于清除Root的排名
            this.reverse[indexes[1]] = 0; //this.reverse[indexes[1]] = count;
            //交换排名之后删除Root
            this.queue[indexes[1]] = null;
            //换data_KEY
            this.indexes[1] = this.indexes[count];
            this.count--;
            Sink();
        }

        /// <summary>
        /// 遍历索引堆
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            string ret = "----data-----\n";
            for (int i = 1; i <= this.queueCount; i++){
                if(this.queue[i] != null){
                    ret += string.Format("[{0}] = {1}\n", i, this.queue[i]);
                }
            }

            ret += "----indexes-----\n";
            for (int i = 1; i <= this.count; i++){
                ret += string.Format("[{0}] = {1}\n", i, this.indexes[i]);
            }

            ret += "----reverse-----\n";
            for (int i = 1; i <= QUEUE_MAXSIZE; i++){
               if(this.reverse[i] != 0){
                    ret += string.Format("[{0}] = {1}\n", i, this.reverse[i]);
               }
            }
            return ret;
        }

        /// <summary>
        /// 获取索引堆内元素个数
        /// </summary>
        /// <returns></returns>
        public int GetSize()
        {
            return this.count;
        }

        /// <summary>
        /// 获取当前索引堆的类型
        /// </summary>
        /// <returns></returns>
        public IndexPQType GetPQType()
        {
            return this.type;
        }
    }
}
