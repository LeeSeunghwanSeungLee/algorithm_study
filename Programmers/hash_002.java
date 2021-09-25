class Solution {
    public boolean solution(String[] phoneBook) {
       for(int i=0; i<phoneBook.length-1; i++) {
            for(int j=i+1; j<phoneBook.length; j++) {
                if(phoneBook[i].startsWith(phoneBook[j])) {return false;}
                if(phoneBook[j].startsWith(phoneBook[i])) {return false;}
            }
        }
        return true;
    }
}

// O(n^2) 임 굉장히 안 좋은 풀이
// comparator 를 직접만드는게 나을것같음 아래 예제 참조

// ArrayList.sort(new Comparator<Student>() {
    //    @Override
    //    public int compare(Student arg0, Student arg1) {
    //           // TODO Auto-generated method stub
    //           int age0 = arg0.getAge();
    //           int age1 = arg1.getAge();
              
    //           if(age0 == age1) return 0;
    //           else if(age0 > age1) return 1;
    //           else return -1;
    //    }
// });


