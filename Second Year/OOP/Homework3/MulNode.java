/**
 * @author Icatoiu Vlad-Cosmin Clasa ce descrie un operator si anume operatorul
 *         ori. Ea extinde clasa Node deci trebuie sa implementeze metoda
 *         accept din Visitable, nefiind abstracta. Constructorul seteaza copiii
 *         intre care urmeaza sa se faca inmultirea
 */
public class MulNode extends Node {

	public MulNode(Node left, Node right) {

		this.setleft(left);
		this.setright(right);
	}

	public Element accept(Visitor v) {

		return v.visit(this);
	}
}
