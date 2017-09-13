
/**
 * @author Icatoiu Vlad-Cosmin
 * Clasa NodeOperation cuprinde toate operatiile ce se pot face asupra unui nod
 * si anume, acelea de adaugare a unui nod intr-un graf, de stergere a unui nod
 * dintr-un graf, de adaugare a unei muchii intre 2 noduri si stergere a unei
 * muchii dintre 2 noduri. Clasa este abstracta pentru ca, desi nu are metode
 * abstracte nu are sens conceptual existenta unui obiect de tipul NodeOperations
 * si de aceea metodele sunt statice.
 */
public abstract class NodeOperations {
	
	/**
	 * Metoda ce insereaza un nod intr-un graf.
	 * @param g Graful in care e inserat nodul
	 * @param line Linia din fisierul de intrare ce contine operatia de add
	 * Dupa ce se creeaza un nod nou, este introdus in graf si apoi se verifica
	 * toti vecinii dati ca parametru si daca acestia se afla in graf atunci
	 * se adauga o muchie intre ei si nodul abia introdus
	 */
	public static void addNode( Graph g, String [] line){
		
		Node n= new Node(line[2],line[1],g.getsettings(line[1]),g.getcounter());
		
		g.insertNode(line[2], n);
		
		g.setcounter();
			
		for( int i = 3; i < line.length; i++ ){
			
			if(g.getNode(line[i]) != null){
			
				addEdge(g,n.getname(),g.getNode(line[i]).getname());
			}
		}	
			
	}
		
	/**
	 * Metoda ce sterge un nod din graf.
	 * @param g Graful din care se sterge nodul
	 * @param name Numele nodului ce urmeaza a fi sters
	 * Se identifica nodul cu numele dat ca parametru. Ulterior, in functie de
	 * versiune, deci de modul de retinere al vecinilor se parcurg vecinii si 
	 * se sterg muchiile dintre ei pentru a fi siguri ca nu ramanem cu o 
	 * "ramasita" a nodului ca vecin al unui nod din graf. La final se sterge nodul.
	 */
	public static void removeNode( Graph g, String name){
			
		Node aux =g.getNode(name);
			
		if(aux.getversion() == 1){
				
			while(!aux.islistEmpty()){
				
				deleteEdge(g,aux.getname(),aux.getListNode(0).getname());
			}
				
		}
			
		if(aux.getversion() == 2){
				
			while( !aux.isvectorEmpty() ){
				
				deleteEdge(g,aux.getname(),aux.getVectorNode(0).getname());
			}
				
		}
			
		if(aux.getversion() == 3){
				
			while(!aux.issetEmpty()){
					
				deleteEdge(g,aux.getname(),aux.getSetNode().getname());
			}
		}
			
		g.removeNode(name);
			
	}
		
	/**
	 * Metoda ce realizeaza o muchie intre 2 noduri date ca parametru
	 * @param g Graful in care se afla cele 2 noduri
	 * @param node1 Numele primului nod
	 * @param node2 Numele celui de-al doilea nod
	 * In functie de versiunea fiecarui nod, daca nu cumva exista deja o muchie
	 * intre cele 2 noduri se introduce pe rand fiecare nod in lista/setul/vectorul
	 * de vecini al celuilalt
	 */
	public static void addEdge(Graph g, String node1, String node2){
			
		if(g.getNode(node1).getversion() == 1){
			
			if( !g.getNode(node1).listcontains(g.getNode(node2)) ){
			
				g.getNode(node1).listadd(g.getNode(node2));
			}
		}
			
		if(g.getNode(node1).getversion() == 2){
			
			if( !g.getNode(node1).vectorcontains(g.getNode(node2)) ){
			
				g.getNode(node1).vectoradd(g.getNode(node2));
			}
		}
			
		if(g.getNode(node1).getversion() == 3){
		
			if( !g.getNode(node1).setcontains(g.getNode(node2)) ){
			
				g.getNode(node1).setadd(g.getNode(node2));
			}
		}
			
		if(g.getNode(node2).getversion() == 1){
			
			if( !g.getNode(node2).listcontains(g.getNode(node1)) ){
			
				g.getNode(node2).listadd(g.getNode(node1));
			}
		}
			
		if(g.getNode(node2).getversion() == 2){
			
			if( !g.getNode(node2).vectorcontains(g.getNode(node1)) ){
				
				g.getNode(node2).vectoradd(g.getNode(node1));
			}
		}
			
		if(g.getNode(node2).getversion() == 3){
			
			if( !g.getNode(node2).setcontains(g.getNode(node1)) ){
			
				g.getNode(node2).setadd(g.getNode(node1));
			}
		}
			
	}
		
	/**
	 * Functie ce sterge muchia dintre 2 noduri. In functie de iteratia fiecarui
	 * nod se sterge celalalt nod din setul/vectorul/lista celuilalt nod 
	 * @param g Graful in care se afla cele 2 noduri
	 * @param node1 Numele primului nod
	 * @param node2 Numele celui de-al doilea nod
	 */
	public static void deleteEdge(Graph g, String node1, String node2){
			

		if(g.getNode(node1).getversion() == 1){
			
			g.getNode(node1).listremove(g.getNode(node2));
		}
			
		if(g.getNode(node1).getversion() == 2){
			
			g.getNode(node1).vectorremove(g.getNode(node2));
		}
			
		if(g.getNode(node1).getversion() == 3){
			
			g.getNode(node1).setremove(g.getNode(node2));
		}
			
		if(g.getNode(node2).getversion() == 1){
			
			g.getNode(node2).listremove(g.getNode(node1));
		}
			
		if(g.getNode(node2).getversion() == 2){
			
			g.getNode(node2).vectorremove(g.getNode(node1));
		}
			
		if(g.getNode(node2).getversion() == 3){
			
			g.getNode(node2).setremove(g.getNode(node1));
		}
		
	}
		
}
