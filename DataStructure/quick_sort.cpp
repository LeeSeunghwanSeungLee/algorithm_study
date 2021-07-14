

void q_sort(int l, int r, int* arr){
    if(l < r){
        int i = l;
        int j = r + 1;
        int pivot = arr[i]; // make the left value to pivot

        do{
            do i++; while(pivot > arr[i] && i <= r);
            do j--; while(pivot < arr[j] && j >= l); // j 를 r + 1로 선정한 이유

            if(i < j){
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }while(i < j);

        int temp = arr[j];
        arr[j] = arr[l];
        arr[l] = temp;

        q_sort(l, j - 1, arr);
        q_sort(j + 1, r, arr);
    }
}