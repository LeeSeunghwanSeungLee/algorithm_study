#include <stdio.h>


//DP를 사용하기 위한 전역변수 배열
int arr[21] = {0,};


//함수 선언
int get_fibo(int input);
int get_fibo_2(int input);
int get_fibo_3(int input);
int get_fibo_4(int input);

int main(void){
    //input value
    int input_value;
    int output_value;
    scanf("%d",&input_value);

    output_value = get_fibo(input_value);
    printf("%d\n",output_value);
    return 0;
}

//함수 원형 선언
int get_fibo(int input){
    if(input == 0) return 0;
    if(input == 1) return 1;
    return input + get_fibo(input-1);
}
//등차수열의 합 공식 이용
int get_fibo_2(int input){
    return input *(input + 1) / 2;
}
//반복문 이용
int get_fibo_3(int input){
    int ans = 0;
    for(int i = 1; i<=input; i++){
        ans += i;
    }
    return ans;
}

//DP 이용
int get_fibo_4(int input){
    if(input = 0) return 0;
    if(input <= 2) {
        arr[input] = 1;
        return 1;
    }
    if(arr[input] != 0) return arr[input];
    arr[input] = get_fibo_4(input - 1) + get_fibo_4(input - 2);
    return arr[input];
}