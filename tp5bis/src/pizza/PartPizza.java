package pizza;

import java.awt.Point;

public class PartPizza {
	
	Point top_left;
	
	Point bottom_right;
	
	public PartPizza(Point tl, Point br) {
		top_left = tl;
		bottom_right = br;
	}
	
	public PartPizza(int x1, int y1, int x2, int y2) {
		top_left = new Point(x1 , y1);
		bottom_right = new Point(x2 , y2);
	}
	
	public int getWidth()  {
		return bottom_right.x - top_left.x + 1;
	}
	
	public int getHeight()  {
		return bottom_right.y - top_left.y + 1;
	}
	
	public int getSize() {
		return getWidth() * getHeight();
	}
	
	public String toString() {
		return top_left.x+" "+top_left.y+" "+bottom_right.x+" "+bottom_right.y;
	}

}
