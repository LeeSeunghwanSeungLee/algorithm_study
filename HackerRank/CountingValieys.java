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
     * Complete the 'countingValleys' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER steps
     *  2. STRING path
     */

    public static int countingValleys(int steps, String path) {
    // Write your code here
        int stackCount = 0;
        boolean isDownhill = false;
        int res = 0;
        for (int i = 0; i < path.length(); i++) {
            if (path.charAt(i) == 'D') {
                stackCount--;
            } else {
                stackCount++;
            }
            
            if (stackCount < 0) isDownhill = true;
            if (stackCount == 0 && isDownhill) {
                isDownhill = false;
                res++;
            }
        }
        
        return res;
    }
}
// 단순한 스택을 활용할 수 있지만, 힙메모리를 추가하고 싶지 않아서 그냥 int 사용
// 메소드 분리를 하지 않은 이유는 딱히 없고 문제가 쉬워서..?

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int steps = Integer.parseInt(bufferedReader.readLine().trim());

        String path = bufferedReader.readLine();

        int result = Result.countingValleys(steps, path);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
