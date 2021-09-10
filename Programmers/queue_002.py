def solution(priorities, location):
    answer = 0
    from collections import deque
    
    d = deque([v, i] for i, v in enumerate(priorities))
    
    while len(d):
        item = d.popleft()
        if d and max(d)[0] > item[0]:
            d.append(item)
        else:
            answer += 1
            if item[1] == location:
                break
            
    return answer

## 배운점
## tuple or array 에 max 를 넣으면 0 번 인덱스를 기준으로 최댓값을 
## max(list, key = lambda x : x[1]) 을 이용하면 예상대로 진행할수도 있음
## deque 는 더블 링크드 리스트로 구성되어있다고 보면됨


## 또다른 답

def solution(priorities, location):
    queue = [(i, p) for i, p in enumerate(priorities)]
    answer = 0
    while True:
        curr = queue.pop(0)
        if any(curr[1] < q[1] for q in queue):
            queue.append(curr)
        else:
            answer += 1
            if curr[0] == location:
                break;
    return answer
            