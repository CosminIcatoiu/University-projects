
/**
 * @author Icatoiu Vlad-Cosmin O clasa ce implementeaza metodele visit pentru
 *         fiecare tip de nod, obiectul creat fiind practic calculatorul
 *         expresiei matematice primite ca input. Practic aceasta clasa merge
 *         prin noduri si aplica operatia corespunzatoare.
 */
public class ASTEvaluator implements Visitor {

	public Element visit(IntNode node) {

		Element aux = new Element();

		aux.settype("Int");

		aux.setval(node.getInt());

		return aux;
	}

	public Element visit(DoubleNode node) {

		Element aux = new Element();

		aux.settype("Double");

		aux.setval(node.getDouble());

		return aux;
	}

	public Element visit(StringNode node) {

		Element aux = new Element();

		aux.settype("String");

		aux.setval(node.getString());

		return aux;
	}

	public Element visit(PlusNode node) {

		return Addition.addition(node.getleft().accept(this), node.getright().accept(this));
	}

	public Element visit(MinusNode node) {

		return Substraction.substraction(node.getleft().accept(this), node.getright().accept(this));

	}

	public Element visit(MulNode node) {

		return Multiplication.multiplication(node.getleft().accept(this), node.getright().accept(this));

	}

	public Element visit(DivNode node) {

		return Division.division(node.getleft().accept(this), node.getright().accept(this));

	}

}
