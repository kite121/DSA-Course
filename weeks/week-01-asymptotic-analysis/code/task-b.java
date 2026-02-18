// Danil Elgin, DSAI04
import java.util.Scanner;
public class Main {
    public static String[] function(String[] nicks, int[] points, int amount, int table_amount){
        int index;
        int max;
        String nick_max;
        if (table_amount > amount){
            table_amount = amount;
        }
        String[] result = new String[table_amount];
        for(int i = 0; i < table_amount; i++){
            index = i;
            max = points[i];
            nick_max = nicks[i];
            for(int j = i + 1; j < amount; j++){
                if (max < points[j]){
                    index = j;
                    max = points[j];
                    nick_max = nicks[j];
                }
            }
            points[index] = points[i];
            points[i] = max;
            nicks[index] = nicks[i];
            nicks[i] = nick_max;
            result[i] = nicks[i] + " " + points[i];
        }
        return result;
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int amount = scanner.nextInt();
        int table_amount = scanner.nextInt();
        int[] points = new int[amount];
        String[] nicks = new String[amount];
        for(int i = 0; i < amount; i++){
            nicks[i] = scanner.next();
            points[i] = scanner.nextInt();
        }
        String[] results = new String[table_amount];
        results = function(nicks, points, amount, table_amount);
        for(String result: results){
            System.out.println(result);
        }
    }
}
