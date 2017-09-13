import java.util.*;
import java.io.*;

/**
 * @author Icatoiu Vlad-Cosmin
 *Clasa SerializeOperations contine operatiile necesare pentru a efectua serializarea
 *unui graf. A doua metoda este una ajutatoare ce scrie vecinii unui nod in fisier.
 *Clasa este abstracta deoarece, desi nu are metode statice existenta unui obiect
 *SerializeOperations nu are sens conceptual si deci toate metodele ei sunt statice.
 */
public abstract class SerializeOperations {

	/**
	 * Metoda ce realizeaza serializarea unui graf. Datele din graf sunt introduse
	 * in fisier printr-o parcurgere de tip BFS. Astfel, introducem nodurile intr-o
	 * coada incepand cu cel dat ca parametru si pentru fiecare scriem vecinii si
	 * datele astfel. Scriem detaliile nodului apoi pe urmatoarea linie numele, apoi
	 * tipul de retinere a vecinilor. Dupa scriem detaliile tuturor vecinilor, fara
	 * a le scrie vecinii deoarece vom scrie aceste lucruri atunci cand ajungem la ei
	 * in coada. Serializarea se realizeaza conform unui fisier XML. Daca nodul a 
	 * mai fost vizitat nu ii mai scriem detaliile ci o referinta la el. Verificam daca
	 * nodul a mai fost introdus in coada cu ajutorul unui vector de vizitati in care
	 * introducem nodurile in momentul in care le scoatem din coada.
	 * @param g Graful pe care il serializam
	 * @param name Numele nodului de la care incepem parcurgerea
	 * @param w fisierul in care scriem serializarea
	 * @throws IOException in cazul in care nu reusim sa scriem in fisier
	 */
	public static void Serialize(Graph g, String name, FileWriter w) throws IOException{
		
		LinkedList<Node> queue = new LinkedList<Node>();
		
		Map <String,Integer> visited = new HashMap<String,Integer>();
		
		queue.addFirst(g.getNode(name));
		
		visited.put(name, 1);
		
		
		while( !queue.isEmpty() ){
			
			Node n = queue.getLast() ;
			
			queue.removeLast();
			
			visited.put(n.getname(), 1);
			
			w.write("<Object class=\"" + n.gettype() + "\" Version=\""+ n.getversion() 
				+"\" id=\""+ n.getid() +"\">\n");
			
			w.write("\t<Nume>"+n.getname()+"</Nume>\n");
			
			if( n.getversion() == 1 ){
				
				w.write("\t<LIST>\n");
				
				Collections.sort(n.getList());
				
				for( int i = 0; i < n.listSize(); i++){
					
					Node aux = n.getListNode(i);
					
					SerializeNeighbours(queue,visited,aux,w);
					
				}
				
				w.write("\t</LIST>\n");
			}
				
			if( n.getversion() == 2 ){
				
				w.write("\t<VECTOR>\n");
				
				Collections.sort(n.getVector());
				
				for( int i = 0; i < n.vectorSize(); i++){
					
					Node aux = n.getVectorNode(i);
					
					SerializeNeighbours(queue,visited,aux,w);
					
				}	
				
				w.write("\t</VECTOR>\n");
				
			}
			
			if( n.getversion() == 3 ){
				
				w.write("\t<SET>\n");
				
				Iterator<Node> it= n.iterator();
				
				while(it.hasNext()){
					
					Node aux = it.next();
					
					SerializeNeighbours(queue,visited,aux,w);
					
				}
				
				w.write("\t</SET>\n");
			}
			
			w.write("</Object>\n");
				
		}
		
	}
	
	/**
	 * Metoda ce scrie serializarea unui vecin in fisier, verificand daca acesta este
	 * vizitat sau este in coada si eventual il introduce in coada in cazul in care
	 * niciuna din coditiile de mai sus nu este indeplinita
	 * @param queue Coada in care introducem vecinii
	 * @param visited Vectorul de noduri vizitate anterior
	 * @param n Vecinul pe care vrem sa il serializam
	 * @param w Fisierul in care scriem serializarea 
	 * @throws IOException in cazul in care nu reusim sa scriem in fisier
	 */
	public static void SerializeNeighbours(LinkedList<Node> queue, Map<String,Integer> visited, Node n, FileWriter w)
		throws IOException{
		
		if( !queue.contains(n) && !visited.containsKey(n.getname()) ){
			
			w.write("\t\t<Object class=\"" + n.gettype() + "\" Version=\"" + n.getversion() 
				+"\" id=\""+ n.getid() +"\">\n");
			
			w.write("\t\t\t<Nume>"+n.getname()+"</Nume>\n");
			
			w.write("\t\t</Object>\n");
			
			queue.addFirst(n);
		}
		else{
			if( visited.containsKey(n.getname()) ){
			
				w.write("\t\t<Refference class=\"" + n.gettype() + "\" Version=\"" + n.getversion() +
						"\" id=\"" + n.getid() +"\">\n");
			}
			else{
				
				w.write("\t\t<Object class=\"" + n.gettype() + "\" Version=\"" +
						n.getversion() +"\" id=\""+ n.getid() +"\">\n");
				
				w.write("\t\t\t<Nume>"+n.getname() +"</Nume>\n");
				
				w.write("\t\t</Object>\n");
			}
		}
	}
}
