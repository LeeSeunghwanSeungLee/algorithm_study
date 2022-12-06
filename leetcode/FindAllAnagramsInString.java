class Solution {
    public List<Integer> findAnagrams(String s, String p) {
        ArrayList<Integer> result = new ArrayList<Integer>();
        // solution
        if (s.length() < p.length()) {
            return result;
        }

        int[] hash = new int[128];
        char[] t = s.toCharArray(), q = p.toCharArray();
        for (char c : q) { // O(n)
            System.out.println((int)c);
            hash[c]++;
        }
        
        int start = 0, end = 0, count = p.length(), lenS = s.length(), lenP = p.length();
        while (end < lenS) {
            if (hash[t[end]] >= 1) {
                count--;
            }

            hash[t[end]]--;
            end++;
            if (count == 0) {
                result.add(start);
            }
            
            if (end - start == lenP) {
                if (hash[t[start]] >= 0) {count++;}
                hash[t[start]]++;
                start++;
            }
        }
        return result;
    }
}
