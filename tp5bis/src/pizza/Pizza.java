package pizza;

import java.awt.Point;
import java.awt.Rectangle;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class Pizza {
	
	
	char[][] pizza;	
	int height;	
	int width;	
	int size;
	int ham;
	

	public Pizza(String fichier) {
		try {
			Scanner donnee = new Scanner(new FileReader(fichier));
			height = donnee.nextInt();
			width = donnee.nextInt();
			ham = donnee.nextInt();
			size = donnee.nextInt();
			pizza = new char[height][width];
			int l = 0;
			while(donnee.hasNext()) { 
				String line = donnee.next();
				pizza[l++] = line.toCharArray();
			}
			donnee.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public List<PartPizza> parts()  {
		List<pizza.PartPizza> liste = new ArrayList<PartPizza>();
		List<pizza.PartPizza> lesParts = new ArrayList<PartPizza>();
		
		List<Point> multiplications = factors(size);

		
		for(int i=0;i<height;i++) { //for(int i=0;i<height;i++) {
			for(int j=0;j<width;j++) { //for(int j=0;j<width;j++) {

				for(Point fois : multiplications) {
					PartPizza tmp = new PartPizza(i,j,i+fois.x-1,j+fois.y-1);
					if(isValid(tmp)) liste.add(tmp);
				}
				
			}
		}
		//Collections.shuffle(liste);
		
		for(PartPizza tmp : liste) {

			if(!overlaps(tmp,lesParts)) lesParts.add(tmp);
		}
		
		return lesParts;
	}
	
	
	private boolean overlaps(PartPizza part, List<PartPizza> liste) {
		Rectangle a,b;
		a = new Rectangle(part.top_left.x,part.top_left.y,part.getWidth(),part.getHeight());
		for(PartPizza tmp : liste) {
			b = new Rectangle(tmp.top_left.x,tmp.top_left.y,tmp.getWidth(),tmp.getHeight());
			if(a.intersects(b)) return true;			
		}
		return false;
	}

	public String googleHashCode() {
		List<PartPizza> liste = parts();
		StringBuilder builder = new StringBuilder();
		builder.append(liste.size());
		for(PartPizza part : liste) {
			builder.append("\n");
			builder.append(part.toString());
		}
		return builder.toString();
	}
	
	private boolean isValid(PartPizza p) {
		
		int enoughHam=0;
		if(p.bottom_right.x >= height) return false;
		if(p.bottom_right.y >= width) return false;
		for (int i=p.top_left.x;i<=p.bottom_right.x;i++) {
			for (int j=p.top_left.y;j<=p.bottom_right.y;j++) {
				if(pizza[i][j] == 'H') enoughHam++;
			}
		}
		return enoughHam >= ham;
	}

	private List<Point> factors(int number) {
		List<Point> multiplications = new ArrayList<Point>();
		for(int n = ham;n<=number;n++) {
			for(int i = 1;i<=n;i++) {
				if((n % i) == 0) multiplications.add(new Point(i,(n / i)));
			}
		}
		Collections.shuffle(multiplications);
		return multiplications;
	}
}
