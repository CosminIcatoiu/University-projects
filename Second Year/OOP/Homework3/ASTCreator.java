import java.util.*;

/**
 * @author Icatoiu Vlad-Cosmin Clasa este abstracta deoarece nu are sens logic
 *         existenta unui obiect, astfel, singura sa metoda este statica.
 *         Scopul clasei este acela de a crea arborele structural pentru
 *         evaluarea unei expresii matematice pe baza unui reverse polish
 *         notation creat imprealabil.
 */
public abstract class ASTCreator {

	/**
	 * Singura metoda a clasei creeaza 2 factory-uri, unul pentru a crea noduri
	 * operator si anume PlusNode, MinusNode, DivNode si MulNode si unul pentru
	 * a crea noduri operand si anume IntNode, StringNode si DoubleNode. De
	 * asemenea Cu ajutorul unui RPN creat imprealabil si unui string de
	 * operatori se verifica daca urmatorul element al vectorului este un
	 * operator sau este un operand, pentru fiecare folosindu-se factory-ul
	 * corespunzator. Principiul de creare al arborelui este simplu. Daca in RPN
	 * este un operand, atunci cream un nod cu fii nuli si il introducem in
	 * stiva. Daca este operator, atunci cream un nod de tipul corespunzator cu
	 * fiii, ultimele 2 elemente introduse in stiva, dupa care introducem noul
	 * nod in stiva. Astfel, la final pe stiva vom avea radacina arborelui.
	 * 
	 * @param RPN
	 *            - Reverse Polish Notation, obtinut dupa parsarea expresiei,
	 *            aceasta fiind forma cea mai convenienta pentru a crea ulterior
	 *            arborele.
	 * @param type
	 *            - o mapa intre numele variabilei( care se afla in RPN ) si
	 *            tipul variabilei respective
	 * @param val
	 *            - o mapa intre numele variabilei si valoarea variabilei
	 *            respective
	 * @return - se returneaza radacina arborelui
	 */
	public static Node create(ArrayList<String> RPN, HashMap<String, String> type, HashMap<String, String> val) {

		OperatorSingletonFactory OperatorFactory = OperatorSingletonFactory.getFactory();

		OperandSingletonFactory OperandFactory = OperandSingletonFactory.getFactory();

		String operations = "+-*/";

		Stack<Node> stack = new Stack<Node>();

		for (int i = 0; i < RPN.size(); i++) {

			if (!operations.contains(RPN.get(i))) {

				Node aux = OperandFactory.createNode(OperandFactory.getNodeType(type.get(RPN.get(i))), 
						val.get(RPN.get(i)));

				stack.push(aux);

			} else {

				Node aux, left, right;

				right = stack.pop();

				left = stack.pop();

				aux = OperatorFactory.createNode(OperatorFactory.getNodeType(RPN.get(i)), left, right);

				stack.push(aux);

			}
		}

		return stack.pop();
	}

}
