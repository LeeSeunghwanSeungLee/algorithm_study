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

char* tmp_sort;

void m_sort_char(int l, int r, char* sort_char){
    if(l < r){
        int mid = (l + r) >> 1;
        int i = l, j = mid, k = l, u;
        m_sort(l, mid, sort_char);
        m_sort(mid + 1, r, sort_char);
    }

    while(i <= mid && j <= r){
        if(sort_char[i] <= sort_char[j]){
            tmp_sort[k++] = sort_char[i++];
        }
        else{
            tmp_sort[k++] = sort_char[j++];
        }
    }
    if(i > mid){ // 오른쪽이 남아있는 경우
        for(u = j; u <= r; u++){

        }
    }
    else{ // 왼쪽이 남아있는 경우
        for(u = i; i <= mid; i++)
    }

}