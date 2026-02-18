// Danil Elgin, DSAI04
import java.util.Scanner;
public class Main {
    public static int[] function(int[] numbers, int amount){
        boolean flag = true;
        int safe;
        while (flag){
            flag = false;
            for(int i = 1; i < amount; i++){
                if (numbers[i - 1] > numbers[i]){
                    safe = numbers[i - 1];
                    numbers[i - 1] = numbers[i];
                    numbers[i] = safe;
                    flag = true;
                }
            }
        }
        return numbers;
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int amount = scanner.nextInt();
        int[] numbers = new int[amount];
        for(int i = 0; i < amount; i++){
            numbers[i] = scanner.nextInt();
        }
        numbers = function(numbers, amount);
        for(int number: numbers){
            System.out.print(number + " ");
        }
    }
}
