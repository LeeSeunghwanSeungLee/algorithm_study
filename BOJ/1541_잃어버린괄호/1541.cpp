#include <iostream>
#include <string>


using namespace std;

//전역변수
string formula;

int main(void){
    string temp;
    int temp_num(0);
    int ans(0);
    bool swit = false;
    //string을 입력받는다
    cin >> formula;
    formula.push_back('a');

    //반복문돌기
    for(int i = 0; i < formula.size(); i++){
           if(formula[i] == '-'){
            if(swit == true){
                temp_num = stoi(temp);
                ans -= temp_num;
                temp.clear();
            }
            else{
                temp_num = stoi(temp);
                ans += temp_num;
                temp.clear();
                swit = true;
            }
        }
        else if(formula[i] == '+'){
            if(swit == true){
                temp_num = stoi(temp);
                ans -= temp_num;
                temp.clear();
            }
            else{
                temp_num = stoi(temp);
                ans += temp_num;
                temp.clear();
            }
        }
        else if(formula[i] == 'a'){
            if(swit == false){
                temp_num = stoi(temp);
                ans += temp_num;
                temp.clear();
            }
            else{
                temp_num = stoi(temp);
                ans -= temp_num;
                temp.clear();
            }
        }

        else{
            temp.push_back(formula[i]);//숫자를 채운다
        }
    }

    cout << ans;
        
    return 0;
}