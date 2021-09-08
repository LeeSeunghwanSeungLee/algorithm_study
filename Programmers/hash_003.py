# # 1. dictionary 형태로 type : value 로 선언한다 O(n)
# # 2. iterator로 순회하면서 1 * (value + 1) 로 값을 돌린다
# # 3. 마지막에 1을 제거해준다(아무것도 안 입을 수는 없으니까)

# '''
#     %%key points%%
# 1. 2 dimension array to dictionary (type : num)
# 2. logical idea
# '''



def solution(clothes):
    answer = {}
    for i in clothes:
        if i[1] in answer: answer[i[1]] += 1
        else: answer[i[1]] = 1

    cnt = 1
    for i in answer.values():
        cnt *= (i+1)
    return cnt - 1


## module 이용


from collections import Counter
from functools import reduce

def solution(clothes):
    
    cnt = Counter([kind for name, kind in clothes])
    answer = reduce(lambda x, y: x*(y+1), cnt.values(), 1) - 1
    return answer
    
print(solution(TEST))