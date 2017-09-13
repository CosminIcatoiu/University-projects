/**
 * @author icatoiu Vlad-Cosmin Clasa ce reprezinta un nod operand si anume
 *         double. Ea extinde clasa parinte Node si deci implementeaza
 *         Visitable. Cum clasa nu este abstracta, trebuie implementata metoda
 *         accept. Ea are un membru privat val si anume numarul double din
 *         nod.De asemenea constructorul initializeaza fiii cu null deoarece in
 *         program nu are sens ca un operand sa aiba copii.
 */
public class DoubleNode extends Node {

	private double val;

	public DoubleNode(String val) {

		this.setleft(null);
		this.setright(null);

		this.val = Double.parseDouble(val);
	}

	/**
	 * Metoda ce modifica valoarea salvata in nod
	 * 
	 * @param val
	 *            - noua valoare
	 */
	public void setDouble(double val) {
		this.val = val;
	}

	/**
	 * @return - Metoda returneaza valoarea salvata in nod
	 */
	public double getDouble() {
		return val;
	}

	public Element accept(Visitor v) {

		return v.visit(this);
	}
}
