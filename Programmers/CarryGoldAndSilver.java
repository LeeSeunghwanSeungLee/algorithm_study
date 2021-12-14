import java.util.*;

class Solution {    
    public long solution(int a, int b, int[] g, int[] s, int[] w, int[] t) {
        long answer = (long)(10e5 * 4 * 10e9);
        long start = (long)0;
        long end = (long)(10e5 * 4 * 10e9);

        while (start <= end) {
            long mid = (start + end) / 2;

            long gold_carry = 0;
            long sil_carry = 0;
            long add_carry = 0;

            for (int i = 0; i < s.length; i++) {
                long now_gold = (long)g[i];
                long now_sil = (long)s[i];
                long now_w = (long)w[i];
                long now_t = (long)t[i];

                long move_cnt = mid / (now_t * 2);
                if (mid % (now_t * 2) >= t[i]) move_cnt++; //편도로 1번더 갈 수 있다면 1회 추가
                    gold_carry += (now_gold < move_cnt* now_w) ? now_gold : move_cnt * now_w;
                    sil_carry += (now_sil < move_cnt* now_w) ? now_sil : move_cnt * now_w;
                    add_carry += (now_gold + now_sil < move_cnt* now_w) ? now_gold + now_sil : move_cnt * now_w;
                }

            if (gold_carry >= a && sil_carry >= b && add_carry >= a + b) {
                end = mid - 1;
                answer = Math.min(mid, answer);
            }
            else {
                start = mid + 1;
            }

        }

        return answer;
    }
}
