import java.util.HashMap;
import java.util.Map;

class Solution {
    public int solution(String[][] relation) {
        int answer = 0;

        boolean[] ht = new boolean[(int)Math.pow(2,relation[0].length)];

        for(int i=1; i<=relation[0].length; i++) {
            //System.out.println("1이 " + i + "개");
            for(int j=1; j<Math.pow(2, relation[0].length); j++) {
                String bin = Integer.toBinaryString(j);
                for(int k=bin.length(); k<relation[0].length; k++) {
                    bin = "0"+bin;
                }
                int one_count = 0;
                for(int k=0; k<bin.length(); k++) {
                    if(bin.charAt(k) == '1') {
                        one_count++;
                        if(one_count > i) {
                            one_count = -1;
                            break;
                        }
                    }
                }
                if(one_count != i) {
                    continue;
                }

                boolean flag = true;

                for(int k=1; k<ht.length; k++) {
                    if(ht[k]) {
                        flag = false;
                        String bin2 = Integer.toBinaryString(k);
                        for(int l=bin2.length(); l<relation[0].length; l++) {
                            bin2 = "0"+bin2;
                        }
                        for(int l=0; l<bin.length(); l++) {
                            if(bin2.charAt(l) == '1' && bin.charAt(l) == '0') {
                                flag = true;
                                break;
                            }
                        }
                    }
                    if(!flag) {
                        break;
                    }
                }

                if(!flag) {
                    continue;
                }

                Map<String, String> map = new HashMap<>();
                for(int k=0; k<relation.length; k++) {
                    String add_str = "";
                    for(int l=0; l<relation[0].length; l++) {
                        if(bin.charAt(l) == '1') {
                            add_str += (relation[k][l]+"\t");
                        }
                    }
                    map.put(add_str, "hi!");
                }
                if(map.size() == relation.length) {
                    //System.out.println(bin);
                    ht[j] = true;
                    answer++;
                }
            }
        }


        return answer;
    }
}
