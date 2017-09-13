import java.util.HashMap;

/**
 * @author Icatoiu Vlad-Cosmin Clasa reprezinta factory-ul pentru operanzi,
 *         adica este clasa ce va crea ulterior toate nodurile int,string sau
 *         double. Aceasta este de asemenea un singleton pentru ca nu ar avea
 *         sens existenta mai multor factory-uri de acelasi tip. Astfel,
 *         constructorul este privat pentru a nu putea fi accesat din exterior.
 *         De asemenea, clasa contine un enum cu tipurile de noduri si o mapa ce
 *         realizeaza legatura intre tipurile din enum si tipurile de baza
 *         int,double,string. Nu vrem ca mapa sa fie modificata, deci nu exista
 *         metoda de set pentru aceasta. In constructor se initializeaza mapa si
 *         se introduc corespondentele.
 */
public class OperandSingletonFactory {

	private static final OperandSingletonFactory factory = new OperandSingletonFactory();

	private HashMap<String, NodeType> nodes;

	private OperandSingletonFactory() {

		nodes = new HashMap<String, NodeType>();

		nodes.put("int", NodeType.IntNode);
		nodes.put("double", NodeType.DoubleNode);
		nodes.put("string", NodeType.StringNode);

	}

	/**
	 * @return - Metoda ce returneaza singurul factory ce poate fi creat pentru
	 *         a putea fi folosit in mai multe locuri
	 */
	public static OperandSingletonFactory getFactory() {

		return factory;
	}

	public enum NodeType {

		StringNode, DoubleNode, IntNode
	}

	/**
	 * Metoda ce creeaza un nod nou in functie de tipul de nod din enum,
	 * initializandu-l cu o valoare
	 * 
	 * @param type
	 *            - tipul nodului
	 * @param val
	 *            - valoarea ce trebuie salvata in nod, are tipul String pentru
	 *            ca asa sunt retinute toti operanzii in mape sau elemente
	 * @return - se returneaza noul nod creat
	 */
	public Node createNode(NodeType type, String val) {

		switch (type) {

		case StringNode:
			return new StringNode(val);

		case DoubleNode:
			return new DoubleNode(val);

		case IntNode:
			return new IntNode(val);
		}

		throw new IllegalArgumentException("The node type " + type + " is not recognised.");
	}

	/**
	 * @param s
	 *            - tipul de baza
	 * @return - Metoda ce returneaza tipul din enum corespunzator tipului de
	 *         baza
	 */
	public NodeType getNodeType(String s) {

		return nodes.get(s);
	}
}
