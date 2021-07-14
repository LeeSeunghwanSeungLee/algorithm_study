//시간이 없는 관계로 수도코드만 작성예정
#include <iostream>
#include <vector>
using namespace std;

long long ans(0);
long long N, B, C;
vector<long long> room_stu;

int main(void){
    cin >> N;
    for(long long i = 0; i < N; i++){
        long long temp;
        cin >> temp;
        room_stu.push_back(temp);
    }
    cin >> B >> C;

    //계산부분
    for(long long i = 0; i < N; i++){
        long long temp = room_stu[i];
        
        temp -= B;
        ans++;
        
        if(temp > 0){
            if(temp % C == 0){//나눠떨어진다면
                long long cycle = temp / C;
                for(long long j = 0; j < cycle; j++){
                    ans++;
                }
             }
            else{//나눠떨어지지 않는다면
                long long cycle = temp / C + 1;
                for(long long j = 0; j < cycle; j++){
                    ans++;
                }
        }
        }
    }
    cout << ans;
    return 0;
}
