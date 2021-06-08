#include<iostream>

using namespace std;



void swap(int *arr){
  int tmp;
  tmp = arr[0];
  arr[0] = arr[1];
  arr[1] = arr[2];
  arr[2] = tmp;
  return;
}

int main(void){

  int arr[3] = {0, 1, 2};

  for(int i = 0; i < 3; i++){
    cout << arr[i] << ' ';
  }

  cout << '\n';

  swap(arr);

  for(int i = 0; i < 3; i++){
    cout << arr[i] << ' ';
  }
  cout << '\n';

  return 0;
}