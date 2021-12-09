class Solution {
    public String solution(String number, int k) {
        int pos = 0;

        StringBuilder answer = new StringBuilder();

        for (int boundary = k; boundary < number.length(); boundary++) {
            char bigNum = '0';

            for (int i = pos; i <= boundary; i++) {
                if (bigNum < number.charAt(i)) {
                    bigNum = number.charAt(i);
                    pos = i + 1;
                }
                if (bigNum == '9') break;
            }

            answer.append(bigNum);
        }

        return answer.toString();
    }
}
