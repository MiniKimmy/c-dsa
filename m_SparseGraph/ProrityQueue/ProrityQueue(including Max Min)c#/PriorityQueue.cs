using System;

namespace m_pq
{
    class PriorityQueue<T>
        where T : class, IComparable<T>
    {
        const int QUEUE_MAXSIZE = 15;         //�������Ԫ�ظ���
        PriorityQueueType type;               //���ȶ�������
        T[] queue;                            //��������
        int count;                            //T[]�ڴ��ڵ�ʵ��Ԫ�ظ���

        /// <summary>
        /// ��ʼ��PriorityQueue
        /// </summary>
        /// <param name="type">���ȶ�������</param>
        public PriorityQueue(PriorityQueueType type)
        {
            this.type = type;
            this.count = 0;

            //��[0]�����棬��[1]��ʼ������size + 1
            this.queue = new T[QUEUE_MAXSIZE + 1];  
        }

        /// <summary>
        /// �ϸ�
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
        /// �³�
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
        /// �ж�PQ�Ƿ�����
        /// </summary>
        /// <returns></returns>
        public bool IsFull()
        {
            if (this.count == QUEUE_MAXSIZE) return true;
            else return false;
        }

        /// <summary>
        /// �ж�PQ�Ƿ�Ϊ��
        /// </summary>
        /// <returns></returns>
        public bool IsEmpty()
        {
            if (this.count == 0) return true;
            else return false;
        }

        /// <summary>
        /// ������Ԫ��
        /// </summary>
        /// <param name="item">������µ�Ԫ��</param>
        public void Insert(T item)
        {
            if (IsFull()) return;
            this.queue[++count] = item;
            Swim();
        }

        /// <summary>
        /// ɾ��PQ��RootԪ��
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
        /// ��ȡPQ��Ԫ�ظ���
        /// </summary>
        /// <returns></returns>
        public int GetSize()
        {
            return this.count;
        }

        /// <summary>
        /// ����PQ
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
