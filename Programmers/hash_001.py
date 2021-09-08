def solution(participant, completion):
    for p in participant:
        if participant.count(p) > completion.count(p):
            return p
    answer = ''
    return answer
    
# 정확성 100 + 효율성 50 코드 => brute force 이기 때문인것으로 보임
# list 는 


def solution(participant, completion):
    participant.sort()
    completion.sort()
    for p,c in zip(participant, completion):
        if p != c:
            return p
    return participant.pop()

# sort 함수는 O(nLogn) 의 속도를 가지기 때문에 위 보다 훨씬 나을 것으로 판단됨



import collections

def solution(participant, completion):
    answer = collections.Counter(participant) - collections.Counter(completion)
    return list(answer.keys())[0] # list 형태로 빼야하기 때문임

# collections 의 Counter 는 카운터에 가장 성능이 좋은 자료구조라고 함
# 해쉬로 구성되어있어서 접근이 빠르고 items() 에서 1번째, 즉 value 값에 따라서 정렬되어있다고 함
# 따라서 뺄셈을 진행했을때 1 인 값이 정답에 남게 되고 list로 반환하면 끝임 