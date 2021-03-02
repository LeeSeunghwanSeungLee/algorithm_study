int* sort;

void m_sort(int l, int r, int* arr){
    if(l < r){
        int mid = (l + r) >> 1;
        int i = l, j = mid + 1, k = l, u;
        m_sort(i, mid, arr);
        m_sort(mid + 1, r, arr);

        while(i <= mid && j <= r){
            if(arr[i] <= arr[j]){
                sort[k++] = arr[i++];
            }
            else{
                sort[k++] = arr[j++]
            }
        }

        if(i > mid){ // 오른쪽게 남아있는 경우
            for(u = j; u <= r; u++){
                sort[k++] = sort[u];
            }
        }
        else{ // 왼쪽이 남아있는 경우
            for (u = i; u <= mid; u++)
				sort[k++] = arr[u];
        }
        for (u = l; u <= r; u++) // 다시 배열에 대입하기
			arr[u] = sort[u];
    }
}