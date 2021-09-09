def solution(progresses, speeds):
    answer = []
    time = 0
    count = 0
    
    while len(progresses) > 0:
        if (progresses[0] + time * speeds[0]) >= 100:
            progresses.pop(0)
            speeds.pop(0)
            count += 1
        else:
            if (count > 0):
                answer.append(count)
                count = 0
            time += 1
    answer.append(count)
    return answer
                
                
#소요 시간 미리 계산하기 
import math

def solution(progresses, speeds):
    progresses = [math.ceil((100 - a) / b) for a, b in zip(progresses, speeds)]
    answer = []
    day = 0
    count = 0
    
    for idx in range(len(progresses)):
        if progresses[idx] <= day:
            count += 1
        else:
            if(count != 0):
                answer.append(count)
                count = 0
            day = progresses[idx]
            count += 1
            
    answer.append(count)
    return answer
            
            
test = [95, 90, 99, 99, 80, 99]
test2 = [1, 1, 1, 1, 1, 1]

print(solution(test, test2))

'''
배운점
1. list.pop(idx) => Dynamic Array 인 관계로 O(n)
'''