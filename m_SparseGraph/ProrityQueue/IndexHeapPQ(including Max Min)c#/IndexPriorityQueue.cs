using System;

namespace m_pq
{
    class IndexPriorityQueue<T>
        where T: class,IComparable<T>
    {
        const int QUEUE_MAXSIZE = 15; //�������Ԫ�ظ���
        IndexPQType type;             //IndexPQ����
        T[] queue;                    //Դsource[]
        int[] indexes;                //queue��index
        int[] reverse;                //indexex���෴����
        int count;                    //Ԫ���ܸ���
        int queueCount;               //T[]��Ԫ��������

        /// <summary>
        /// ��ʼ��������IndexHeap
        /// </summary>
        /// <param name="type">�����ѵ�����</param>
        /// <param name="dataNum">����ԴData[]��Ԫ�ظ���</param>
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
        /// �ϸ�
        /// </summary>
        private void Swim()
        {
            int flag = this.indexes[count];
            if (this.type == IndexPQType.IndexMaxPQ)
            {
                while (flag / 2 != 0 && this.queue[count].CompareTo(this.queue[indexes[flag / 2]]) == 1)
                {
                    //������,reverse[]
                    int temp = this.reverse[indexes[flag]];
                    this.reverse[indexes[flag]] = flag / 2;
                    this.reverse[indexes[flag / 2]] = temp;

                    //��Key,indexex[]
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
                    //������,reverse[]
                    int temp = this.reverse[indexes[flag]];
                    this.reverse[indexes[flag]] = flag / 2;
                    this.reverse[indexes[flag / 2]] = temp;

                    //��Key,indexex[]
                    temp = this.indexes[flag];
                    this.indexes[flag] = this.indexes[flag / 2];
                    this.indexes[flag / 2] = temp;
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
                        //������
                        int temp = this.reverse[mark];
                        this.reverse[mark] = this.reverse[indexes[flag]];
                        this.reverse[indexes[flag]] = temp;

                        //��data_key
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
                        //������
                        int temp = this.reverse[mark];
                        this.reverse[mark] = this.reverse[indexes[flag]];
                        this.reverse[indexes[flag]] = temp;

                        //��data_key
                        this.indexes[key] = this.indexes[flag];
                        this.indexes[flag] = mark;
                    }
                    flag = mark;
                }
            }
        }

        /// <summary>
        /// �ж��������Ƿ�Ϊ��
        /// </summary>
        public bool IsEmpey()
        {
            if (this.count == 0) return true;
            else return false;
        }

        /// <summary>
        /// �ж��������Ƿ�����
        /// </summary>
        public bool IsFull()
        {
            if (this.count == QUEUE_MAXSIZE) return true;
            else return false;
        }

        /// <summary>
        /// ������Ԫ��
        /// </summary>
        /// <param name="value">����ӵ�Ԫ�صĶ���</param>
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
        /// ɾ�������ѵ�Root
        /// </summary>
        public void Delete()
        {
            //������,��������������[1]�Ľ���
            this.reverse[indexes[count]] = 1;
            //����0�����൱�����Root������
            this.reverse[indexes[1]] = 0; //this.reverse[indexes[1]] = count;
            //��������֮��ɾ��Root
            this.queue[indexes[1]] = null;
            //��data_KEY
            this.indexes[1] = this.indexes[count];
            this.count--;
            Sink();
        }

        /// <summary>
        /// ����������
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
        /// ��ȡ��������Ԫ�ظ���
        /// </summary>
        /// <returns></returns>
        public int GetSize()
        {
            return this.count;
        }

        /// <summary>
        /// ��ȡ��ǰ�����ѵ�����
        /// </summary>
        /// <returns></returns>
        public IndexPQType GetPQType()
        {
            return this.type;
        }
    }
}
