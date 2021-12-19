class Solution {
    public int[] solution(int[] prices) {
        int len = prices.length;
        int[] answer = new int[len];
        int i, j;
        for (i = 0; i < len; i++) {
            for (j = i + 1; j < len; j++) {
                answer[i]++;
                if (prices[i] > prices[j])
                    break;
            }
        }
        return answer;
    }
}
// import java.util.*;

// class Solution {
//     private Stack<Node> st;
    
//     public int[] solution(int[] prices) {
//         this.st = new Stack<>();
//         int[] answer = new int[prices.length];
        
//         for (int i = 0; i < prices.length; i++) {
//             Node newNode = new Node(i, prices[i]);
            
//             while (!this.st.empty()) {
//                 Node peekNode = this.st.peek();
//                 if (peekNode.getNumber() <= newNode.getNumber()) break;
//                 this.st.pop();
//                 int time = peekNode.getInsertTime();
//                 int length = i - time;
//                 answer[time] = length;
//             }
//             this.st.push(newNode);      
//         }
        
//         while (!this.st.empty()) {
//             Node peekNode = this.st.pop();
//             int time = peekNode.getInsertTime();
//             int length = prices.length - time - 1;
//             answer[time] = length;
//         }
//         return answer;
//     }
// }

//  class Node {
//     private int insertTime;
//     private int num;
//     Node (int insertTime, int num) {
//         this.insertTime = insertTime;
//         this.num = num;
//     }


//     public int getInsertTime() {
//         return this.insertTime;
//     }

//     public int getNumber() {
//         return this.num;
//     }
// }
