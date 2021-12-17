class Solution {
    public long[] solution(long[] numbers) {
        long[] answer = new long[numbers.length];

            for(int i=0; i<numbers.length; i++){
                String BinaryString =  Long.toBinaryString(numbers[i]);
                if(numbers[i]%2==0){
                    answer[i] = numbers[i]+1;
                }else{
                    //홀수 가장 낮은 0을 1로 바꾸고 , 방금 바꾼것보다는 나중 위치에서 1을 0으로 바꾸기
                    int lastindex =  BinaryString.lastIndexOf("0");
                    int firstindex = BinaryString.indexOf("1",lastindex);
                    if(lastindex==-1){
                        //0이 없는경우 +1을 해주고
                        //앞의 10은 놔두고 나머지는 다 1로 해준다.
                        numbers[i]+=1;
                        BinaryString =  Long.toBinaryString(numbers[i]);
                        BinaryString = BinaryString.substring(0,2)+
                            BinaryString.substring(2,BinaryString.length()).replace("0","1");

                    }else{
                        BinaryString = BinaryString.substring(0,lastindex)+"1"+
                                       BinaryString.substring(lastindex+1,firstindex)+"0"+
                                       BinaryString.substring(firstindex+1,BinaryString.length());
                    }
                
                    answer[i] = Long.parseLong(BinaryString,2);
                }
            }
        return answer;
    }

}
