public class Interval implements Comparable {

	private int x, y;

	public Interval(int x, int y) {
		this.x = x;
		this.y = y;
	}

	//I need a compare method in order to sort the intervals

	public int compareTo(Object o) {

		if (x > ((Interval) o).x
				|| (x == ((Interval) o).x && y > ((Interval) o).y)) {
			return 1;
		}

		return -1;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

}
