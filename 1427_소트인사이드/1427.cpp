#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

//전역변수
int input_Number;
vector<int> arr_Number; // 자리수 정렬



int main(void){
    
    cin >> input_Number;
    int cnt = 0; // 1의 자리부터
    while (input_Number > 0){ // 숫자로 가져오기
        cnt++;
        int temp = input_Number % 10;
        arr_Number.push_back(temp);
        input_Number/=10;
    }
    
    sort(arr_Number.begin(), arr_Number.end(), greater<int>());
    
    for(int i = 0; i < cnt; i++){
        cout << arr_Number[i];
    }
    
    
    return 0;
}