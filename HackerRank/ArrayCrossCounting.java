class Solution{
  public List<Integer> answer(List<Integer> a, List<Integer> b, int interval, 
                              int head, int step, int count) {
    List<Integer> res = new ArrayList<>();
    
    // implement
    
    int cnt = 0;
    while (cnt < count) {
      int nowIdx = head + step * cnt;
      
      res.add(getIndex(a, b, interval, nowIdx);
      
      ctn++;
    }
    return res;
  }
  private int getIndex(List<Integer> a, List<Integer> b, int interval, int index) {
    if (index >= b.size() * (1 + interval)) { // b 보다 초과했을 경우
      return a.get(index - b.size());
    }
    
    if (index <= interval) {
      return a.get(index);
    }
    
    if ((index - inverval) % (interval + 1) == 0) {
      regurn a.get(index - (index + 1) / (interval + 1));
    }
    
    return b.get((index - interval) / (index + 1));
}
0 1 2  3  4 5 6  7  8 9 10 11 12 13  
0 1 2 [0] 3 4 5 [1] 6 7 8 [2] 9 10
  i, i + interval + 1, 
  a_n = iterval + (interval + 1)* (n - 1);
  
  b가 나온 횟수 : (index + 1) / (interval + 1)
    
  
