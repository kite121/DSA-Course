//Danil Elgin DSAI-04
//interface and classes (MyLinkedMap, Entry) was written in the lab
import java.util.Scanner;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        int n, m;
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        scanner.nextLine();
        MyMap<String, Integer> map = new MyMap<>(n);
        ArrayList<Entry<String, Integer>> answer = new ArrayList<>();
        String input_1 = scanner.nextLine();
        m = scanner.nextInt();
        scanner.nextLine();
        String input_2 = scanner.nextLine();
        String[] words_1 = input_1.split(" ");
        String[] words_2 = input_2.split(" ");
        for(int i = 0; i < n; i++) {
            map.put(words_1[i], 1);
        }
        for(int i = 0; i < m; i++){
            if (map.get(words_2[i]) == null || map.get(words_2[i]) == -1){
                continue;
            }
            map.put(words_2[i], -1);
        }
        for(int i = 0; i < n; i++){
            if (map.get(words_1[i]) == 1){
                answer.add(new Entry<>(words_1[i],1 ));
                map.put(words_1[i], -1);
            }
        }
        System.out.println(answer.size());
        for(int i = 0; i < answer.size(); i++){
            System.out.println(answer.get(i).getKey());
        }
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
class MyMap<K, V> implements MapADT<K, V>{
    private static final int PRIME = 71;
    private int size;
    private int capacity;
    private List<Entry<K, V>> hashmap[];

    public MyMap(int capacity) {
        this.capacity = capacity;
        this.size = 0;
        this.hashmap = new List[capacity];
        for (int i = 0; i < capacity; i++){
            this.hashmap[i] = new ArrayList<>();
        }
    }
    public int hashCode(K key){
        int hash = 0;
        for(int i = 0; i < key.toString().length(); i++){
            hash += key.toString().charAt(i) * PRIME;
        }
        return hash % this.capacity;
    }

    @Override
    public V get(K key) {
        int idx = hashCode(key);
        for(Entry<K, V> entry: hashmap[idx]){
            if (entry.getKey().equals(key)){
                return (entry.getValue());
            }
        }
        return null;
    }

    @Override
    public void put(K key, V value) {
        int idx = hashCode(key);
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
        int idx = hashCode(key);
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
