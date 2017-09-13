/**
 * @author Icatoiu Vlad-Cosmin Clasa ce reprezinta un operand si anume
 *         string-ul, contine un membru de tip string ce va stoca valoarea
 *         corespunzatoare nodului. Clasa extinde superclasa Node si deci
 *         trebuie sa implementeze metoda accept. Constructorul initializeaza
 *         copiii nodului cu null deoarece nu are sens in cadrul programului ca
 *         un operand sa aiba fii.
 */
public class StringNode extends Node {

	private String str;

	public StringNode(Object str) {

		this.setleft(null);
		this.setright(null);
		this.str = (String) str;
	}

	/**
	 * Metoda ce actualizeaza valoarea din nod
	 * 
	 * @param s
	 *            - noua valoare
	 */
	public void setString(String s) {
		str = s;
	}

	/**
	 * @return - Metoda ce returneaza valoarea stocata in nod
	 */
	public String getString() {
		return str;
	}

	public Element accept(Visitor v) {

		return v.visit(this);
	}
}
