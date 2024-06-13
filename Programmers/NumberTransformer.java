import java.util.*;

class Solution {
    public int solution(int x, int y, int n) {
        Queue<Map.Entry<Integer, Integer>> q = new LinkedList<>();
        q.add(new AbstractMap.SimpleEntry<>(y, 0));

        while (!q.isEmpty()) {
            Map.Entry<Integer, Integer> tuple = q.poll();
            Integer num = tuple.getKey();
            Integer count = tuple.getValue();

            if (num.equals(x)) {
                return count;
            }

            if (num - n >= x) q.add(new AbstractMap.SimpleEntry<Integer, Integer>(num - n, count + 1));

            if (num % 2 == 0 && num / 2 >= x) q.add(new AbstractMap.SimpleEntry<Integer, Integer>(num / 2, count + 1));

            if (num % 3 == 0 && num / 3 >= x) q.add(new AbstractMap.SimpleEntry<Integer, Integer>(num / 3, count + 1));
        }
        
        return -1;
    }
}
