using System;

namespace m_pq
{
    class PriorityQueue<T>
        where T : class, IComparable<T>
    {
        const int QUEUE_MAXSIZE = 15;         //数组最大元素个数
        PriorityQueueType type;               //优先队列类型
        T[] queue;                            //对象数组
        int count;                            //T[]内存在的实际元素个数

        /// <summary>
        /// 初始化PriorityQueue
        /// </summary>
        /// <param name="type">优先队列类型</param>
        public PriorityQueue(PriorityQueueType type)
        {
            this.type = type;
            this.count = 0;

            //第[0]个不存，从[1]开始，所以size + 1
            this.queue = new T[QUEUE_MAXSIZE + 1];  
        }

        /// <summary>
        /// 上浮
        /// </summary>
        private void Swim()
        {
            int flag = this.count;
            if (this.type == PriorityQueueType.MaxPQ)
            {
                //this.queue[flag] > this.queue[flag / 2]
                while (this.queue[flag].CompareTo(this.queue[flag / 2]) == 1 && flag / 2 != 0)
                {
                    var temp = this.queue[flag];
                    this.queue[flag] = this.queue[flag / 2];
                    this.queue[flag / 2] = temp;
                    flag = flag / 2;
                }
            }
            else
            {
                while (this.queue[flag].CompareTo(this.queue[flag / 2]) == -1 && flag / 2 != 0)
                {
                    var temp = this.queue[flag];
                    this.queue[flag] = this.queue[flag / 2];
                    this.queue[flag / 2] = temp;
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
            if (this.type == PriorityQueueType.MaxPQ)
            {
                while (flag * 2 <= this.count)
                {
                    int index = flag * 2;
                    if (index < this.count && this.queue[index].CompareTo(this.queue[index + 1]) == -1)
                    {
                        index++;
                    }

                    if (this.queue[flag].CompareTo(this.queue[index]) == -1)
                    {
                        var temp = this.queue[flag];
                        this.queue[flag] = this.queue[index];
                        this.queue[index] = temp;
                    }
                    flag = index;
                }
            }
            else
            {
                while (flag * 2 <= this.count)
                {
                    int index = flag * 2;
                    if (index < this.count && this.queue[index].CompareTo(this.queue[index + 1]) == 1)
                    {
                        index++;
                    }
                    if (this.queue[flag].CompareTo(this.queue[index]) == 1)
                    {
                        var temp = this.queue[flag];
                        this.queue[flag] = this.queue[index];
                        this.queue[index] = temp;
                    }
                    flag = index;
                }
            }
        }

        /// <summary>
        /// 判断PQ是否已满
        /// </summary>
        /// <returns></returns>
        public bool IsFull()
        {
            if (this.count == QUEUE_MAXSIZE) return true;
            else return false;
        }

        /// <summary>
        /// 判断PQ是否为空
        /// </summary>
        /// <returns></returns>
        public bool IsEmpty()
        {
            if (this.count == 0) return true;
            else return false;
        }

        /// <summary>
        /// 插入新元素
        /// </summary>
        /// <param name="item">所添加新的元素</param>
        public void Insert(T item)
        {
            if (IsFull()) return;
            this.queue[++count] = item;
            Swim();
        }

        /// <summary>
        /// 删除PQ的Root元素
        /// </summary>
        public void Delete()
        {
            if (IsEmpty()) return;
            var temp = this.queue[1];
            this.queue[1] = this.queue[count];
            this.count--;
            Sink();
        }

        /// <summary>
        /// 获取PQ的元素个数
        /// </summary>
        /// <returns></returns>
        public int GetSize()
        {
            return this.count;
        }

        /// <summary>
        /// 遍历PQ
        /// </summary>
        public override string ToString()
        {
            string ret = "-----queue----\n";
            for (int i = 1; i <= this.count; i++)
            {
                 ret += string.Format("[{0}] {1}\n", i, this.queue[i]);
            }
            return ret;
        }
    }
}
