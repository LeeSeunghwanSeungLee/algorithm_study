"""https://www.acmicpc.net/problem/2750"""

###버블소트###

def BubbleSort(li):
    list_length = len(li)
    #length가 4라면
    #바깥 루프는 3번 돌아야 하므로
    #range()는 0, 1, 2까지 즉 range(3)이 되야 하므로
    #range(list_length-1)이 되어야 한다.
    for i in range(list_length-1):
        #안쪽 루프는 1번당 3-> 2-> 1
        #즉 range(4 - 0 - 1) ->
        #range(4 - 1 - 1) ->
        #range(4 - 2 - 1)
        #range(list_leng - i - 1)
        for j in range(list_length-i-1):
            #만약 앞에 있는 값이 크다면 두 개를 교환
            if li[j] > li[j+1]:
                li[j], li[j+1] = li[j+1], li[j]

###선택정렬###

#맨 왼쪽부터 하나씩 최소값을 선택(selection)해 채운다
def selection_sort(li):
    for i in range(len(li)-1):
        min_idx = i
        for j in range(i+1, len(li)):
            if li[min_idx] > li[j]:
                min_idx = j
        if min_idx != i:
            li[i], li[min_idx] = li[min_idx], li[i]
    return li

###삽입정렬###
def insertion_sort(li):
    for i in range(1, len(li)):
        j = i - 1
        key = li[i]
        while li[j] > key and j >= 0:
            li[j+1] = li[j]
            j = j -1
        li[j+1] = key
    return li



###병합정렬###
# merge sort
#left와 right는 리스트임!
def merge(left, right):
    v = list()
    i = 0;
    j = 0
    while (i < len(left) and j < len(right)):
        if left[i] <= right[j]:
            v.append(left[i])
            i += 1
        else:
            v.append(right[j])
            j += 1
    if i == len(left): v = v + right[j:len(right)]
    if j == len(right): v = v + left[i:len(left)]
    return v


def merge_sort(v):
    if len(v) <= 1: return v
    m = len(v) // 2
    left = merge_sort(v[0:m])
    right = merge_sort(v[m:len(v)])
    return merge(left, right)



###퀵 정렬###
#tail recursion을 활용함
def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    lesser_arr, equal_arr, greater_arr = [], [], []
    for num in arr:
        if num < pivot:
            lesser_arr.append(num)
        elif num > pivot:
            greater_arr.append(num)
        else:
            equal_arr.append(num)
    return quick_sort(lesser_arr) + equal_arr + quick_sort(greater_arr)
