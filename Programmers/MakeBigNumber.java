class Solution {
    public String solution(String number, int k) {
        int pos = 0;

        StringBuilder answer = new StringBuilder();

        for (int left = (number.length() - k) - 1; left >= 0; left--) {
            char bigNum = '0';

            for (int i = pos; i < (number.length() - left); i++) {
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
