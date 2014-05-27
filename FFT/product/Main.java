import java.io.*;
import java.util.*;
import java.math.*;

class Main {
	public static void main(String args[]) throws IOException {
		Scanner in = new Scanner(new File("input.txt"));
		PrintWriter out = new PrintWriter("output2.txt");
		BigInteger a = in.nextBigInteger();
		BigInteger b = in.nextBigInteger();

		a = a.multiply(b);

		out.println(a);
		out.close();
	}
}