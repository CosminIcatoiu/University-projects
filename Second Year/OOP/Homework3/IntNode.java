/**
 * @author Icatoiu Vlad-Cosmin Clasa ce reprezinta un operand si anume int-ul,
 *         contine un membru de tip int ce va stoca valoarea corespunzatoare
 *         nodului. Clasa extinde superclasa Node si deci trebuie sa
 *         implementeze metoda accept. Constructorul initializeaza copiii
 *         nodului cu null deoarece nu are sens in cadrul programului ca un
 *         operand sa aiba fii.
 */
public class IntNode extends Node {

	private int val;

	public IntNode(String val) {

		this.setleft(null);
		this.setright(null);

		this.val = Integer.parseInt(val);
	}

	/**
	 * Metoda ce modifica valoarea stocata in nod
	 * 
	 * @param val
	 *            - noua valoare
	 */
	public void setInt(int val) {
		this.val = val;
	}

	/**
	 * @return - Metoda returneaza valoarea stocata in nod
	 */
	public int getInt() {
		return val;
	}

	public Element accept(Visitor v) {
		return v.visit(this);
	}
}
