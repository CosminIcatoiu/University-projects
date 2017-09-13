import java.util.*;

/**
 * @author Icatoiu Vlad-Cosmin Clasa reprezinta factory-ul pentru operatori,
 *         adica este clasa ce va crea ulterior toate nodurile plus,minus, mul
 *         sau div. Aceasta este de asemenea un singleton pentru ca nu ar avea
 *         sens existenta mai multor factory-uri de acest tip. Astfel,
 *         constructorul este privat pentru a nu putea fi accesat din exterior.
 *         De asemenea, clasa contine un enum cu tipurile de noduri si o mapa ce
 *         realizeaza legatura intre tipurile din enum si semnele matematice
 *         corespunzatoare lor. Nu vrem ca mapa sa fie modificata, deci nu
 *         exista metoda de set pentru aceasta. In constructor se initializeaza
 *         mapa si se introduc corespondentele.
 */
public class OperatorSingletonFactory {

	private static final OperatorSingletonFactory factory = new OperatorSingletonFactory();

	private HashMap<String, NodeType> nodes = new HashMap<String, NodeType>();

	private OperatorSingletonFactory() {

		nodes.put("+", NodeType.PlusNode);
		nodes.put("-", NodeType.MinusNode);
		nodes.put("/", NodeType.DivNode);
		nodes.put("*", NodeType.MulNode);

	}

	/**
	 * @return - Metoda ce returneaza factory-ul creat pentru a putea fi folosit
	 *         in mai multe locuri
	 */
	public static OperatorSingletonFactory getFactory() {
		return factory;
	}

	public enum NodeType {

		PlusNode, MinusNode, DivNode, MulNode
	}

	/**
	 * Metoda ce creeaza un nod in functie de tipul din enum si ii initializeaza
	 * copiii, deoarece operatorii au mereu fii in cadrul acestui program, dar
	 * nu au o valoare
	 * 
	 * @param type
	 *            - tipul nodului
	 * @param left
	 *            - fiul stang
	 * @param right
	 *            - fiul drept
	 * @return - Metoda returneaza nodul creat
	 */
	public Node createNode(NodeType type, Node left, Node right) {

		switch (type) {

		case PlusNode:
			return new PlusNode(left, right);

		case MinusNode:
			return new MinusNode(left, right);

		case DivNode:
			return new DivNode(left, right);

		case MulNode:
			return new MulNode(left, right);

		}

		throw new IllegalArgumentException("The node type " + type + " is not recognised.");
	}

	/**
	 * @param s
	 *            - semnul matematic corespunzator unei operatii
	 * @return - se returneaza omologul semnului din enum
	 */
	public NodeType getNodeType(String s) {

		return nodes.get(s);
	}
}
