import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    static BufferedReader in;
    static StringTokenizer strtok;
    
    static String next() throws IOException {
        while (strtok == null || !strtok.hasMoreTokens())
            strtok = new StringTokenizer(in.readLine());
        return strtok.nextToken();
    }

    static int nextInt() throws IOException {
        return Integer.parseInt(next());
    }
    
    static long nextLong() throws IOException {
        return Long.parseLong(next());
    }
    
    static double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }

    public static void main(String args[]) throws IOException {
        in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        out.close();    
    }
}
