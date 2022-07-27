import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;

class Result {

    /*
     * Complete the 'whatFlavors' function below.
     *
     * The function accepts following parameters:
     *  1. INTEGER_ARRAY cost
     *  2. INTEGER money
     */

    public static void solve(List<Integer> arr, int money) {
        // Complete this function
        if (arr == null || arr.size() < 1) {
            System.out.println(-1 + " " + -1);
            return;
        }

        // core logic
        Map<Integer, Integer> hashMap = new HashMap<>();
        for (int i = 0; i < arr.size(); i++) {
            if (arr.get(i) < money) {
                if (hashMap.containsKey(money - arr.get(i))) {
                    int index = hashMap.get(money - arr.get(i));
                    System.out.println((index + 1) + " " + (i + 1));
                    return;
                }

                if (!hashMap.containsKey(arr.get(i))) {
                    hashMap.put(arr.get(i), i);
                }
            }
        }
    }


}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        int t = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, t).forEach(tItr -> {
            try {
                int money = Integer.parseInt(bufferedReader.readLine().trim());

                int n = Integer.parseInt(bufferedReader.readLine().trim());

                List<Integer> cost = Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                    .map(Integer::parseInt)
                    .collect(toList());

                Result.solve(cost, money);
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        bufferedReader.close();
    }
}
