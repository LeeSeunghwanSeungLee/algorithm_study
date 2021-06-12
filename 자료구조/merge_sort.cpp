
int N,arr[1000001];
int *arr2;



void partition(int left,int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2; 
		partition(left, mid);
		partition(mid + 1, right);
		

		int mid = (left + right) / 2;

		int i = left;
		int j = mid + 1;
		int k = left;
		while (i <= mid && j <= right)
		{
			if (arr[i] <= arr[j]) 
				arr2[k++] = arr[i++]; 
			else
				arr2[k++] = arr[j++];
		}

		int tmp = i>mid ? j : i;
		
		while(k<=right) arr2[k++] = arr[tmp++];

		for (int i=left;i<=right;i++) arr[i] = arr2[i];
	}
}
