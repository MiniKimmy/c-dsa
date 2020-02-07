using namespace std;

void selectSort(int q[], int n){
    for(int i = 0; i < n; i ++){
        int minv = i;
        for(int j = i + 1; j < n; j ++)
            if (q[minv] > q[j])
                minv = j;

        if (minv != i) 
            swap(q[minv], q[i]);
    }
}