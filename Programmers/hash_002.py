def solution(phone_book):
    phone_book.sort()
    phone_book.sort(key = len)
    
    answer = True
    
    while True : 
        prefix = phone_book[0]
        phone_book = phone_book[1:]
        for phone in phone_book : 
            if prefix == phone[:len(prefix)] : 
                answer = False
                break;
        if len(phone_book) == 1 :
            break;

    return answer


## 시관초과 => 아마도 정렬이 2번이 들어갔다는점과 비교분석이 n^2 라는 것이 단점으로 작용했을 것으로 보임


def solution(phone_book):
    
    answer = True
    
    phone_book.sort()
    
    for i in range(len(phone_book)-1):
        if len(phone_book[i]) < len(phone_book[i+1]):
            if phone_book[i + 1][:len(phone_book[i])] == phone_book[i]:
                answer = False
                break
    return answer
    
    
def solution(phoneBook):
    phoneBook = sorted(phoneBook)
    #phoneBook.sort() 

    for p1, p2 in zip(phoneBook, phoneBook[1:]):
        if p2.startswith(p1):
            return False
    return True
    
# nLog(n) sort
# offset start
# compare start
# startwith method