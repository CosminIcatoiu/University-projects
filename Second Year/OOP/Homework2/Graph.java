import java.util.*;

/**
 * @author Icatoiu Vlad-Cosmin
 * Clasa simuleaza un graf, acesta fiind retinut prin intermediul unui hashmap intre
 * numele nodului si nodul propriu-zis. Membrii sunt privati, iar in ceea ce priveste
 * membrul settings, acesta nu poate fi deloc modificat din exterior deoarece evident
 * nu am vrea ca o actiune exterioara sa modifice functionarea grafului nostru. Membrul
 * counter retine numarul de noduri ce au fost introduse in graf, el fiind ulterior si
 * id-ul fiecarui nod. 
 */
public class Graph {

	private Map<String,Node> Graph= new HashMap<String,Node>();
	
	private int counter=0;
	
	private Map<String,Integer> settings= new HashMap<String,Integer>();
	
	/**
	 * Constructorul ce initializeaza setarile dupa care vor functiona
	 * nodurile din graf.
	 * @param settings1 - modul de functionare al tipului de nod A
	 * @param settings2 - modul de functionare al tipului de nod B
	 * @param settings3 - modul de functionare al tipului de nod C
	 */
	public Graph(String settings1, String settings2, String settings3){
		
		settings.put( new String("NodA"), Integer.parseInt(settings1));
		settings.put( new String("NodB"), Integer.parseInt(settings2));
		settings.put( new String("NodC"), Integer.parseInt(settings3));
	
	}

	/**
	 * functie ce creste counter-ul atunci cand se introduce un nod in graf
	 */
	public void setcounter(){
		counter++;
	}
	
	/**
	 * @return- se returneaza counter-ul actual pentru a putea fi asignat ca 
	 * id unui nod
	 */
	public int getcounter(){
		return counter;
	}

	/**
	 * @param type - tipul de nod pentru care ne intereseaza setarile predefinite
	 * @return - se returneaza versiunea in care functioneaza acel tip de nod
	 */
	public int getsettings(String type){
		return settings.get(type);
	}
	
	/**
	 * @param name numele nodului pentru care se verifica daca exista deja sau nu in graf
	 * @return true daca nodul exista deja in graf si fals, altfel
	 */
	public boolean containsNode( String name ){
		return Graph.containsKey(name);
	}
	
	/**
	 * Ambii parametri sunt necesari pentru a realiza maparea intre ei
	 * @param name - numele nodului ce urmeaza a fi introdus in graf
	 * @param n - nodul propriu-zis
	 */
	public void insertNode(String name, Node n){
		Graph.put(name, n);
	}
		
	/**
	 * @param name Numele nodului pe care vrem sa il intoarcem
	 * @return - nodul al carui nume este dat ca parametru
	 */
	public Node getNode(String name){
		return Graph.get(name);
	}
	
	/**
	 * Metoda ce sterge un nod dintr-un graf
	 * @param name Numele nodului ce urmeaza a fi sters
	 */
	public void removeNode(String name){
		Graph.remove(name);
	}
	
}
