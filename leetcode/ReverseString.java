class Solution {
    public void reverseString(char[] s) {
        int mid = s.length / 2;
        for (int i = 0; i < mid; i++) {
            swapCharacter(s, i, s.length - i - 1);
        }
    }
    
    private void swapCharacter(char[] array, int index_a, int index_b) {
        if (index_a == index_b) {
            return;
        }

        char temp = array[index_a];
        array[index_a] = array[index_b];
        array[index_b] = temp;
    }
}
