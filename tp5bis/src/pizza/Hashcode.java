package pizza;

import java.io.PrintWriter;

public class Hashcode {


	public static void main(String[] args) {
		Pizza pizza = new Pizza(args[0]);
			
		PrintWriter writer;
		try {
			writer = new PrintWriter(args[1], "UTF-8");
			writer.print(pizza.googleHashCode());
			writer.close();
		} catch (Exception e) {
			e.printStackTrace();
			return;
		}
		System.out.println("Wrote in "+args[1]);
	}

}
