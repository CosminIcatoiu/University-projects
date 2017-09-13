/**
 * @author Icatoiu Vlad-Cosmin Interfata Visitor pe baza careia se creeaza
 *         calculatorul expresiei matematice. Pentru fiecare nod operand aceasta
 *         doar intoarce un element cu acel tip si cu valoarea corespunzatoare
 *         iar pentru un operator se aplica operatia corespunzatoare pe fii.
 */
public interface Visitor {

	/**
	 * Functie ce creeaza un nou element cu tipul String si cu valoarea prezenta
	 * in nod.
	 * 
	 * @param node
	 *            - Nodul din care se ia valoarea elementului
	 * @return - se returneaza elementul creat
	 */
	public Element visit(StringNode node);

	/**
	 * Metoda ce creeaza un nou element cu tipul Int si cu valoarea prezenta in
	 * nod
	 * 
	 * @param node
	 *            - Nodul din care se ia valoarea pentru element
	 * @return - se returneaza elementul creat
	 */
	public Element visit(IntNode node);

	/**
	 * Metoda ce creeaza un nou element cu tipul Double si cu valoarea prezenta
	 * in nod.
	 * 
	 * @param node
	 *            - Nodul din care se ia valoarea pentru element
	 * @return - se returneaza elementul creat
	 */
	public Element visit(DoubleNode node);

	/**
	 * Metoda ce realizeaza adunarea intre copiii unui nod, mutand visitatorul
	 * recursiv in copii si aplicand ulterior metoda de adunare ( addition)
	 * 
	 * @param node
	 *            - Nodul a carui copii trebuie adunati
	 * @return - se returneaza rezultatul adunarii intre copiii nodului, cu
	 *         precizarea ca acestia s-ar putea sa fie de asemenea rezultatul
	 *         altor operatii.
	 */
	public Element visit(PlusNode node);

	/**
	 * Metoda ce realizeaza scaderea intre copiii unui nod, prin vizitarea
	 * ulterioara a acestora si aplicarea operatiei de scadere( substraction)
	 * 
	 * @param node
	 *            - Nodul a carui copii trebuie scazuti
	 * @return - se returneaza rezultatul scaderii intre copiii nodului
	 */
	public Element visit(MinusNode node);

	/**
	 * Metoda ce realizeaza inmultirea intre copiii unui nod, prin vizitarea
	 * ulterioara a acestora si aplicarea operatiei de inmultire(
	 * multiplication)
	 * 
	 * @param node
	 *            - Nodul a carui copii trebuie inmultiti
	 * @return - se returneaza rezultatul inmultirii intre copiii nodului
	 */
	public Element visit(MulNode node);

	/**
	 * Metoda ce realizeaza impartirea intre copiii unui nod, prin vizitarea lor
	 * si apelarea metodei de impartire( division)
	 * 
	 * @param node
	 *            - Nodul a carui copii trebuie inmultiti
	 * @return - se returneaza rezultatul impartirii intre copiii nodului
	 */
	public Element visit(DivNode node);
}
