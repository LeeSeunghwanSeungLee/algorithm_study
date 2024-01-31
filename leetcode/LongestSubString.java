/* https://leetcode.com/problems/longest-substring-without-repeating-characters/submissions/1161942611/ */
class Solution {
    public int lengthOfLongestSubstring(String s) {
        Set<Character>set=new HashSet<>();
        int maxLength=0;
        int left=0;
        for(int right=0;right<s.length();right++){
           
            if (!set.contains(s.charAt(right))) { // 존재하지 않는 경우
                System.out.println("존재 x -> " + left + " - " + right);
                set.add(s.charAt(right));
                maxLength=Math.max(maxLength,right-left+1);
                
            } else { // 동일한 것을 만난 경우
                while (s.charAt(left) != s.charAt(right)) {
                    set.remove(s.charAt(left));
                    left++;
                }
                set.remove(s.charAt(left));
                left++;
                System.out.println("존재 o 지움 -> " + left + " - " + right);
                set.add(s.charAt(right));
            }
            
        }
        return maxLength;
    }
}
