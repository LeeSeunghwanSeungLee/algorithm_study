import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;


public class List {
    public static void main(String[] args){
       System.out.println("Array List Test start");
       arrayListTest();
    }

    /**
    * ArrayList
    */
    private static void arrayListTest(){
        
        ArrayList<Integer> arrList = new ArrayList<Integer>();

        // add Method
        arrList.add(120);
        arrList.add(340);
        arrList.add(330);
        arrList.add(320);
        arrList.add(40);
        arrList.add(30);
        arrList.add(20);
        arrList.add(140);
        arrList.add(130);


        // print
        System.out.println("=====초기 버전입니다 =====");
        for(int i = 0; i < arrList.size(); i++)
            System.out.println(arrList.get(i));

        // remove
        arrList.remove(0);

        // Iterator
        System.out.println("=====삭제 버전입니다 =====");
        for(Integer elem : arrList)
            System.out.println(elem);

        // sort
        Collections.sort(arrList, (a, b) ->  b - a); /* 람다식을 이용한 내림차순 정렬 */
        System.out.println("=====정렬 버전입니다 =====");
        for(Integer elem : arrList)
            System.out.println(elem);

        // iterator() 메소드와 get() 메소드를 이용한 요소의 출력
        Iterator<Integer> iter = arrList.iterator();
        System.out.println("=====이터레이터 버전입니다 =====");
        while (iter.hasNext()) {
            System.out.print(iter.next() + " ");
        }

        // set() 메소드를 이용한 요소의 변경
        arrList.set(0, 20);
    }

    public static void linkedListTest(){

        LinkedList<String> lnkList = new LinkedList<String>();

 
        // add() 메소드를 이용한 요소의 저장
        lnkList.add("넷");
        lnkList.add("둘");
        lnkList.add("셋");
        lnkList.add("하나");

        

        // for 문과 get() 메소드를 이용한 요소의 출력
        for (int i = 0; i < lnkList.size(); i++) {
            System.out.print(lnkList.get(i) + " ");
        }

    
        // remove() 메소드를 이용한 요소의 제거
        lnkList.remove(1);

        

        // Enhanced for 문과 get() 메소드를 이용한 요소의 출력
        for (String e : lnkList) {
            System.out.print(e + " ");
        }

        

        // set() 메소드를 이용한 요소의 변경
        lnkList.set(2, "둘");

        

        for (String e : lnkList) {
            System.out.print(e + " ");
        }

        // size() 메소드를 이용한 요소의 총 개수
        System.out.println("리스트의 크기 : " + lnkList.size());
    }
}


/**
 * TIL
 * 1. Arrays.sort vs Collections.sort
 *      -> Arrays.sort : Dual Pivot Quicksort 로 구현되어있음
 *      -> Collections.sort : mergesort와 insert sort를 합친 tim sort로 구성되어있다고 함
 *      -> 정적배열의 경우 Arrays.sort, 일반적인 Object 에는 Collections.sort를 이용하자
 * 
 * 2. 자바 람다식에 대해서
 *    
 * 3. StringBuilder, StringBuffer, String
 */