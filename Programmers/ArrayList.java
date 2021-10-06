/**
 * Arraylist 구현 (단 제너릭스는 사용하지 않았음)
 */

public class ArrayList {
    private Object[] arr = null;
    private int capacity = 0;
    private int size = 0;

    /* 생성자 */
    ArrayList(){
        this.capacity = 1;
        arr = new Object[this.capacity];
        this.size = 0;
    }
    ArrayList(int capacity){
        this.capacity = capacity;
        this.arr = new Object[capacity];
        this.size = 0;
    }

    public void add(Object element){
        if(this.size == this.capacity)
            expandArray();
        
        arr[this.size++] = element;
    }

    public void add(int index, Object element){
        if(this.size == this.capacity)
            expandArray();
        
        for(int i = this.size; i >= index; i--)
            arr[i] = arr[i - 1];

        arr[index] = element;
        this.size++;
    }

    public void addFirst(Object element){
        add(0, element);
    }

    public Object get(int index){
        if(index >= this.size || index < 0) return null;

        return this.arr[index];
    }

    public Object remove(int index){
        if(index >= this.size || index < 0) return null;
        Object res = this.arr[index];

        for(int i = index; i < this.size - 1; i--)
            arr[i] = arr[i + 1];

        this.size--;

        return res;
    }

    public void reset(){
        this.arr = new Object[this.capacity];
    }

    public int size(){
        return this.size;
    }


    private void expandArray(){
        this.capacity *= 2;

        this.arr = copyArr(this.capacity);
    }

    private Object[] copyArr(int size){
        Object[] aTempArr = new Object[this.capacity];

        for(int i = 0; i < this.arr.length; i++){
            aTempArr[i] = this.arr[i];
        }
        return aTempArr;
    }
}