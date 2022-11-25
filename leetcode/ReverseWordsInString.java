class Solution {
    public String reverseWords(String s) {
        
        char[] str = s.toCharArray();
        int count = 0;

        for(int i = 0; i < s.length(); i++){            
            count++;
            if(str[i] == ' '){
                reverse(str, i-count+1, i-1);
                count = 0;
            }
            
            if(i == s.length()- 1){
                reverse(str, i-count+1, i);
                count = 0;
            }
        }
        
        return new String(str);
        
    }
    
    private void reverse(char[] str, int i, int j) {
        while(i < j){
            char tmp = str[i];
            str[i] = str[j];
            str[j] = tmp;
            i++;
            j--;
        }
    }        
}
