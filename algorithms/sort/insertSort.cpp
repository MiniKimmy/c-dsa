using namespace std;

void insertSort(int q[], int n){
    for(int i = 1; i < n; i ++){
        int pos = i, val = q[i];
        for(int j = i - 1; j >= 0 && q[j] > val; j --) {
            q[j + 1] = q[j];
            pos = j;
        }

        if (pos != i) q[pos] = val;
    }
}