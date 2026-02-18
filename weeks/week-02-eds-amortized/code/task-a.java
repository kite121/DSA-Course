//Danil Elgin DSAI-04
//interfaces and classes (LinkedListQueue, ListStack, Node_queue) was written in the lab
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        int sign = 0;
        int helper = 0;
        int digit = 0;
        int mx = 0;
        int helper_mx = 0;
        ListStack<Character> stack = new ListStack<>();
        LinkedListQueue<Character> queue = new LinkedListQueue<>();
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        int skip = 0;
        for(int i = 0; i < input.length();i ++) {
            if (skip != 0) {
                skip -= 1;
                continue;
            }
            if (input.charAt(i) == ' ') {
                continue;
            }
            if (input.charAt(i) == 'm') {
                if (input.charAt(i + 1) == 'i') {
                    stack.push('n');
                    stack.push('i');
                    stack.push('m');
                    skip = 3;
                    continue;
                } else {
                    stack.push('x');
                    stack.push('a');
                    stack.push('m');
                    skip = 3;
                    continue;
                }
            }
            if (input.charAt(i) == '(') {
                sign = 1;
                helper += 1;
                stack.push('(');
                continue;
            }
            if (input.charAt(i) == '+') {
                if (sign == 1) {
                    if (!stack.isEmpty()) {
                        while (stack.peek() != '(') {
                            queue.offer(stack.peek());
                            queue.offer(' ');
                            stack.pop();
                        }
                    }
                } else {
                    if (!stack.isEmpty()) {
                        while (!stack.isEmpty()) {
                            queue.offer(stack.peek());
                            queue.offer(' ');
                            stack.pop();
                        }
                    }
                }
                stack.push('+');
                continue;
            }
            if (input.charAt(i) == '-') {
                if (sign == 1) {
                    if (!stack.isEmpty()) {
                        while (stack.peek() != '(') {
                            queue.offer(stack.peek());
                            queue.offer(' ');
                            stack.pop();
                        }
                    }
                } else {
                    if (!stack.isEmpty()) {
                        while (!stack.isEmpty()) {
                            queue.offer(stack.peek());
                            queue.offer(' ');
                            stack.pop();
                        }
                    }
                }
                stack.push('-');
                continue;
            }
            if(input.charAt(i) == '*'){
                if(sign == 1){
                        while(!stack.isEmpty() && stack.peek() != '(' && (stack.peek() == '*' || stack.peek() == '/')){
                            queue.offer(stack.peek());
                            queue.offer(' ');
                            stack.pop();
                        }
                        stack.push('*');
                }
                else{
                    if(!stack.isEmpty()){
                        while(!stack.isEmpty() && (stack.peek() == '*' || stack.peek() == '/')){
                            queue.offer(stack.peek());
                            queue.offer(' ');
                            stack.pop();
                        }
                    }
                    stack.push('*');
                }
                continue;
            }
            if(input.charAt(i) == '/'){
                if(sign == 1){
                        while(!stack.isEmpty() && stack.peek() != '(' && (stack.peek() == '*' || stack.peek() == '/')){
                            queue.offer(stack.peek());
                            queue.offer(' ');
                            stack.pop();
                        }
                        stack.push('/');
                }
                else{
                    if(!stack.isEmpty()){
                        while(!stack.isEmpty() && (stack.peek() == '*' || stack.peek() == '/')){
                            queue.offer(stack.peek());
                            queue.offer(' ');
                            stack.pop();
                        }
                    }
                    stack.push('/');
                }
                continue;
            }
            if(input.charAt(i) == ')'){
                if (helper == 1) {
                    sign = 0;
                }
                while(stack.peek() != '('){
                    queue.offer(stack.peek());
                    queue.offer(' ');
                    stack.pop();
                }
                stack.pop();
                if (!stack.isEmpty()) {
                    if (stack.peek() == 'm') {
                        for (int j = 0; j < 3; j++) {
                            queue.offer(stack.peek());
                            stack.pop();
                        }
                        queue.offer(' ');
                    }
                }
                helper -= 1;
                continue;
            }
            if(input.charAt(i) == ','){
                while(stack.peek() != '('){
                    queue.offer(stack.peek());
                    queue.offer(' ');
                    stack.pop();
                }
                continue;
            }
            if (i + 1 != input.length()){
                if(input.charAt(i + 1) != ' ' && input.charAt(i + 1) != ')'){
                        digit = 1;
                }
                else{
                    digit = 0;
                }
            }
            if (digit == 1){
                queue.offer(input.charAt(i));
            }
            else {
                queue.offer(input.charAt(i));
                queue.offer(' ');
            }
        }
        while(!stack.isEmpty()){
            queue.offer(stack.peek());
            queue.offer(' ');
            stack.pop();
        }
        int size = queue.size();
        for(int i = 0; i < size - 1; i++){
            System.out.print(queue.peek_first());
            queue.pool();
        }
    }
}
interface Stack<T> {
    void push(T value);
    T pop();
    T peek();
    int size();
    boolean isEmpty();
}
interface Queue<T> {
    void offer(T item);
    T pool();
    T peek_last();
    T peek_first();
    int size();
    boolean isEmpty();
}
class Node_stack<T> {
    T value;
    Node_stack<T> previous = null;
    public Node_stack(T value, Node_stack<T> previous) {
        if (previous == null){
            this.value = value;
        }
        else{
            this.value = value;
            this.previous = previous;
        }
    }
}
class Node_queue<T> {
    T value;
    Node_queue<T> next;

    public Node_queue(T value, Node_queue<T> next) {
        this.value = value;
        this.next = next;
    }
}
class LinkedListQueue<T> implements Queue<T> {
    private Node_queue<T> head;
    private Node_queue<T> tail;
    int size;

    public LinkedListQueue() {
        this.head = this.tail = null;
        this.size = 0;
    }

    @Override
    public boolean isEmpty() {
        return this.size == 0;
    }

    @Override
    public int size() {
        return this.size;
    }

    @Override
    public void offer(T value) {
        if (this.size == 0) {
            this.head = new Node_queue<T>(value, null);
            this.tail = head;
            this.head.next = null;
            this.size++;
        } else {
            this.tail.next = new Node_queue<T>(value, null);
            this.tail = this.tail.next;
        }
        this.size++;
    }

    @Override
    public T pool() {
        if (this.size == 0){
            throw new RuntimeException("The queue is empty");
        } else {
            T ret =  this.head.value;
            this.head = this.head.next;
            this.size--;
            return ret;
        }
    }
    public T peek_first(){
        if (this.size == 0){
            throw new RuntimeException("The queue is empty");
        } else {
            return this.head.value;
        }
    }
    public T peek_last(){
        if (this.size == 0){
            throw new RuntimeException("The queue is empty");
        } else {
            return this.tail.value;
        }
    }
}

class ListStack<T> implements Stack<T>{
    private int size;
    private Node_stack<T> tail;
    ListStack(){
        size = 0;
        tail = null;
    }
    public int size(){
        return this.size;
    }
    public boolean isEmpty(){
        return this.size == 0;
    }
    public void push(T value){
        if (size == 0){
            tail = new Node_stack<T>(value, null);
        }
        else{
            this.tail = new Node_stack<T>(value, this.tail);
        }
        size += 1;
    }
    public T pop(){
        try {
            if (size == 0) {
                throw new RuntimeException("The stack is empty");
            }
            else {
                T safe = tail.value;
                this.tail = tail.previous;
                size -= 1;
                return safe;
            }
        } catch (RuntimeException e) {
            throw new RuntimeException(e);
        }
    }
    public T peek(){
        try {
            if (size == 0) {
                throw new RuntimeException("The stack is empty");
            }
            else {
                return tail.value;
            }
        } catch (RuntimeException e) {
            throw new RuntimeException(e);
        }
    }

}
