import java.util.*;

/**
 * @author Icatoiu Vlad-Cosmin
 * Clasa Node descrie tipul nodului ce urmeaza a fis introdus in graf. Aceasta
 * implementeaza Comparable deoarece atunci cand introducem un element in set
 * trebuie sa stim dupa ce trebuie ele ordonate. Membrul name reprezinta numele
 * nodului si este privat deoarece nu dorim sa fie modificat din exterior. Membrul
 * type reprezinta tipul nodului si anume NodA, NodB sau NodC si de asemenea trebuie
 * sa fie privat pentru a nu fi alterat. Variabila membru version reprezinta iteratia
 * nodului respectiv, iar variabila id reprezinta id-ul nodului. Toate aceste informatii
 * determina comportamentul nodului deci nu vrem sa fie alterate din exterior.
 * De asemenea, clasa mai contine un set, o lista si un vector pentru retinerea vecinilor
 * si in functie de versiune se foloseste una din cele 3 metode.
 */
public class Node implements Comparable<Node>{

	private String name,type;
	private int version,id;
	
	private MySet<Node> set=null;
	private MyList<Node> list=null;
	private MyVector<Node> vector=null;
	
	/**
	 * Constructorul clasei Node initializeaza campurile specifice ale unui nod
	 * si, in functie de parametrul version determina felul in care trebuie 
	 * retinuti vecinii
	 * @param name Numele noului nod
	 * @param type Tipul noului nod
	 * @param version Versiunea noului nod
	 * @param id ID-ul noului nod
	 */
	public Node( String name, String type, int version, int id){
		
		this.name=name;
		this.type=type;
		this.version=version;
		this.id=id;
		
		switch(version){
		
			case 1:
				list= new MyList<Node>();
			
			case 2:
				vector= new MyVector<Node>();
			
			case 3:
				set= new MySet<Node>();
		}	
	}
	
	
	/** 
	 * Implementeaza metoda compareTo din interfata Comparable, astfel, nodurile
	 * vor fi introduse in set ordonate crescator dupa nume
	 */
	public int compareTo(Node n){
		return -n.name.compareTo(name);
	}
	
	/**
	 * @return returneaza numele nodului
	 */
	public String getname(){
		return name;
	}
	
	/**
	 * @return returneaza versiunea nodului
	 */
	public int getversion(){
		return version;
	}
	
	/**
	 * @return returneaza id-ul nodului
	 */
	public int getid(){
		return id;
	}
	
	/**
	 * @return returneaza tipul nodului
	 */
	public String gettype(){
		return type;
	}
	
	/**
	 * @return returneaza true daca lista de vecini este goala 
	 */
	public boolean islistEmpty(){
		return list.l.isEmpty();
	}
	
	/**
	 * @param i Indexul unui nod in lista
	 * @return returneaza nodul cu indexul i
	 */
	public Node getListNode(int i){
		return list.l.get(i);
	}
	
	/**
	 * @return returneaza true daca vectorul de vecini nu contine niciun nod
	 */
	public boolean isvectorEmpty(){
		return vector.v.isEmpty();
	}
	
	/**
	 * @param i - index-ul unui nod in vectorul de vecini
	 * @return nodul cu index-ul i in vectorul de vecini
	 */
	public Node getVectorNode(int i){
		return vector.v.elementAt(i);
	}
	
	/**
	 * @return returneaza true daca set-ul de vecini nu contine niciun nod
	 */
	public boolean issetEmpty(){
		return set.s.isEmpty();
	}
	
	/**
	 * @return returneaza primul vecin din set-ul de vecini
	 */
	public Node getSetNode(){
		return set.s.first();
	}
	
	/**
	 * Metoda ce sterge nodul primit ca parametru din lista de vecini
	 * @param n Nodul ce urmeaza a fi sters
	 */
	public void listremove(Node n){
		list.l.remove(n);
	}
	
	/**
	 * Metoda ce sterge nodul primit ca parametru din vectorul de vecini
	 * @param n Nodul ce urmeaza a fi sters
	 */
	public void vectorremove(Node n){
		vector.v.remove(n);
	}
	
	/**
	 * Metoda ce sterge nodul primit ca parametru din setul de vecini
	 * @param n Nodul ce urmeaza a fi sters 
	 */
	public void setremove(Node n){
		set.s.remove(n);
	}
	
	/**
	 * Metoda ce adauga nodul primit ca parametru in lista de vecini
	 * @param n Nodul ce urmeaza a fi adaugat
	 */
	public void listadd(Node n){
		list.l.add(n);
	}
	
	/**
	 * Metoda ce adauga nodul primit ca parametru in vectorul de vecini
	 * @param n Nodul ce urmeaza a fi adaugat
	 */
	public void vectoradd(Node n){
		vector.v.add(n);
	}
	
	/**
	 * Metoda ce adauga nodul primit ca parametru in setul de vecini
	 * @param n Nodul ce urmeaza a fi adaugat
	 */
	public void setadd(Node n){
		set.s.add(n);
	}
	
	/**
	 * @param n Nodul pentru care se realizeaza verificare
	 * @return returneaza true daca nodul n se afla in lista de vecini si fals, altfel
	 */
	public boolean listcontains(Node n){
		return list.l.contains(n);
	}
	
	/**
	 * @param n Nodul pentru care se realizeaza verificare
	 * @return returneaza true daca nodul n se afla in vectorul de vecini si fals, altfel
	 */
	public boolean vectorcontains(Node n){
		return vector.v.contains(n);
	}
	
	/**
	 * @param n Nodul pentru care se realizeaza verificare
	 * @return returneaza true daca nodul n se afla in setul de vecini si fals, altfel
	 */
	public boolean setcontains(Node n){
		return set.s.contains(n);
	}
	
	/**
	 * @return returneaza lista de vecini
	 */
	public LinkedList<Node> getList(){
		return list.l;
	}
	
	/**
	 * @return numarul de vecini din lista de vecini
	 */
	public int listSize(){
		return list.l.size();
	}
	
	/**
	 * @return numarul de vecini din vectorul de vecini
	 */
	public int vectorSize(){
		return vector.v.size();
	}
	
	/**
	 * @return returneaza vectorul de vecini
	 */
	public Vector<Node> getVector(){
		return vector.v;
	}
	
	/**
	 * @return returneaza un iterator prin setul de vecini
	 */
	public Iterator<Node> iterator(){
		return set.s.iterator();
	}
}
