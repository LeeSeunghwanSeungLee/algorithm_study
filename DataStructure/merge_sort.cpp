
int N, arr[100001];
int *arr2;


void mergesort(int left, int right){
	if(left < right){
		int mid = (left + right) >> 1;
		mergesort(left, mid);
		mergesort(mid + 1, right);

		int i = left;
		int j = mid + 1;
		int k = left;
		while( i <= mid && j <= right){
			if(arr[i] < arr[j])
				arr2[k++] = arr[i++];
			else
				arr2[k++] = arr[j++];
		}

		int tmp = (i > mid) ? j : i;
		while(k <= right) arr2[k++] = arr[tmp++];

		for(register int i = left; i <= right; i++){
			arr[i] = arr2[i];
		}
	}
}x