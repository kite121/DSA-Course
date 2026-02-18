//Danil Elgin DSAI-04
//interface and classes (MyLinkedMap, Entry) was written in the lab
import java.util.Scanner;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        int n, k;
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        k = scanner.nextInt();
        scanner.nextLine();
        MyLinkedListMap<String, Integer> map = new MyLinkedListMap<>(30);
        ArrayList<Entry<String, Integer>> answer = new ArrayList<>();
        String input = scanner.nextLine();
        String[] words = input.split(" ");
        for (int i = 0; i < words.length; i++) {
            if (map.get(words[i]) == null){
                map.put(words[i], 1 );
                continue;
            }
            map.put(words[i], map.get(words[i]) + 1 );
        }
        for(int i = 0; i < n; i++){
            if(map.get(words[i]) == -1){
                continue;
            }
            answer.add(new Entry<>(words[i],map.get(words[i])));
            map.put(words[i], -1);
            int index = answer.size() - 1;
            for (int j = answer.size() - 2; j > -1; j--) {
                if(answer.get(j).getValue() >= answer.get(index).getValue()){
                    Entry<String, Integer> safe = answer.get(j);
                    answer.set(j, answer.get(index));
                    answer.set(index, safe);
                    index--;
                }
                else{
                    break;
                }
            }
        }
        System.out.println(answer.get(answer.size() - k).getKey());
    }
}
interface MapADT<K, V>{
    V get(K key);
    void put(K key, V value);
    void remove(K key);
    int size();
    boolean isEmpty();
}
class Entry<K, V>{
    private K key;
    private V value;

    public Entry(K key, V value) {
        this.key = key;
        this.value = value;
    }


    public K getKey() {
        return key;
    }

    public V getValue() {
        return value;
    }

    public void setKey(K key) {
        this.key = key;
    }

    public void setValue(V value) {
        this.value = value;
    }
}
class MyLinkedListMap<K, V> implements MapADT<K, V>{
    private int size;
    private int capacity;
    private List<Entry<K, V>> hashmap[];

    public MyLinkedListMap(int capacity) {
        this.capacity = capacity;
        this.size = 0;
        this.hashmap = new List[capacity];
        for (int i = 0; i < capacity; i++){
            this.hashmap[i] = new LinkedList<>();
        }
    }

    @Override
    public V get(K key) {
        int idx = ((String)key).length() % this.capacity;
        for(Entry<K, V> entry: hashmap[idx]){
            if (entry.getKey().equals(key)){
                return (entry.getValue());
            }
        }
        return null;
    }

    @Override
    public void put(K key, V value) {
        int idx = ((String)key).length() % this.capacity;
        boolean flag = true;
        for(Entry<K, V> entry: hashmap[idx]){
            if (entry.getKey().equals(key)){
                entry.setValue(value);
                flag = false;
                break;
            }
        }
        if (flag){
            hashmap[idx].add(new Entry<>(key, value));
        }

    }

    @Override
    public void remove(K key) {
        int idx = ((String)key).length() % this.capacity;
        for(Entry<K, V> entry: hashmap[idx]){
            if (entry.getKey().equals(key)){
                hashmap[idx].remove(entry);
                break;
            }
        }
    }

    @Override
    public int size() {
        return this.size();
    }

    @Override
    public boolean isEmpty() {
        return this.size == 0;
    }
}
