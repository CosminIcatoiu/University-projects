/**
 * @author Icatoiu Vlad-Cosmin Clasa de baza a tuturor nodurilor, ea
 *         implementeaza Visitable,dar, fiind abstacta nu este nevoie sa
 *         implementeze si metoda accept. Clasa este abstracta si pentru ca nu
 *         are sens in cadrul programului existenta unui nod fara un tip anume.
 *         Ea contine copiii care sunt de acelasi tip.
 */
public abstract class Node implements Visitable {

	private Node left, right;

	/**
	 * @return - Metoda returneaza primul copil
	 */
	public Node getleft() {
		return left;
	}

	/**
	 * @return - Metoda returneaza al doilea copil
	 */
	public Node getright() {
		return right;
	}

	/**
	 * Metoda seteaza copilul stang al nodului
	 * 
	 * @param n
	 *            - noul copil stang al nodului
	 */
	public void setleft(Node n) {
		left = n;
	}

	/**
	 * Metoda seteaza fiul drept al nodului
	 * 
	 * @param n
	 *            - noul fiu drept al nodului
	 */
	public void setright(Node n) {
		right = n;
	}

}
