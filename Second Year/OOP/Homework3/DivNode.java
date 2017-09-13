/**
 * @author Icatoiu Vlad-Cosmin. Clasa ce reprezinta un nod operator, ea
 *         corespunzand operatiei de impartire. Ea extinde clasa node ce
 *         implementeaza interfata Visitable.
 */
public class DivNode extends Node {

	/**
	 * In constructor se initializeaza copiii nodului, aceia ce vor fi ulterior
	 * impartiti.
	 * 
	 * @param left
	 *            - primul copil
	 * @param right
	 *            - al doilea copil
	 */
	public DivNode(Node left, Node right) {

		this.setleft(left);
		this.setright(right);
	}

	public Element accept(Visitor v) {
		return v.visit(this);
	}
}
