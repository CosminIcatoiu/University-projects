import java.util.*;
import java.io.*;

/**
 * @author Icatoiu Vlad-Cosmin
 *
 * Clasa cuprinde atat operatia de deserializare cat si operatia de scriere
 * a operatiilor de cast. Clasa este abstracta deoarece, desi nu are vreo
 * metoda abstracta crearea unui obiect de tipul DeserializeOperations
 * nu are sens, de aceea toate metodele sunt statice.
 */
public abstract class DeserializeOperations {

	/**
	 * Aceasta metoda citeste linie cu linie dintr-un fisier pe care il primeste
	 * ca input prin intermediul scanner-ului si construieste un graf de la 0. 
	 * In functie de linia care a fost citita din fisier se verifica daca se pot 
	 * extrage informatii despre un nod al grafului respectiv, acestea fiind salvate
	 * in variabile definite la nivelul metodei. Dupa ce s-a gasit un nod, parcurgerea
	 * fiind BFS, se cauta toti vecinii, se realizeaza legaturile intre primul nod
	 * si acestia si se scriu in fisierul de cast( prin apelarea functiei CastWriter) 
	 * cazurile in care s-a reusit sau nu trecerea de la o versiune la alta a nodului.
	 * @param g - Graful in care vom introduce nodurile
	 * @param in - Fisierul din care deserializam
	 * @param cast - fisierul in care scriem operatiile de cast
	 * @throws IOException - in cazul in care apare o eroare de citire sau scriere
	 */
	public static void Deserialize(Graph g, Scanner in, FileWriter cast) throws IOException{
		
		String line=null;
		
		String type=null;
		
		String name=null;
		
		int version=0,id=0,counter=0;
		
		LinkedList<String> casted= new LinkedList<String>();
		
		Node n=null;
		
		Map<String,Integer> actualsettings = new HashMap<String,Integer>();
		
		while(in.hasNextLine()){
			
			line=in.nextLine();
			
			if(counter == 0){
			
				type=line.substring(15,19);
			
				version=Integer.parseInt(line.substring(30,31));
				
				id=Integer.parseInt(line.substring(37,38));
			
			}
			
			if (counter == 1){
				
				String words[]=line.split("<");
				
				words=words[1].split(">");
				
				name=new String(words[1]);
				
				version=CastWriter(cast,version,type,g,casted,name);
				
				n= new Node(name,type,version,id);
				
				if(!g.containsNode(name)){
					
					g.insertNode(name, n);
				}
			}
			
			counter++;
			
			if(counter == 2){
				
				do{
				
					counter=0;
					
					line=in.nextLine();
					
					String words[]=line.split("<");
					
					if(words[1].substring(0, 1).equals("O")){
					
						type=words[1].substring(14,18);
						
						version=Integer.parseInt(words[1].substring(29,30));
						
						id=Integer.parseInt(words[1].substring(36,37));
					}
					
					if(words[1].substring(0,1).equals("N")){
						
						words=words[1].split(">");
						
						name= new String(words[1]);
						
						version=CastWriter(cast,version,type,g,casted,name);
						
						Node aux= new Node(name,type,version,id);
						
						if(!g.containsNode(name)){
							
							g.insertNode(name, aux);
						}
						
						NodeOperations.addEdge(g, name, n.getname());
					}
					
				
				}while(!line.substring(0,1).equals("<"));
			}
			
		}
		
		in.close();
		
	}
	
	/**
	 * Metoda ce realizeaza scrierea operatiilor de schimbare a versiunii nodurilor in fisier
	 * In cazul in care versiunea curenta este egala cu versiunea precedenta, atunci nu se 
	 * scrie nimic.
	 * @param cast - fisierul in care se scriu cast-urile 
	 * @param version - versiunea precedenta a nodului
	 * @param type - tipul nodului, necesar pentru a obtine setarile predefinite pentru
	 * acel tip de nod
	 * @param g - graful pentru care analizam setarile
	 * @param casted - o lista cu nodurile pentru care am scris deja operatia de cast
	 * @param name - numele nodului pentru care urmeaza sa facem cast-ul
	 * @return - se returneaza versiunea actualizata, aceasta fiind cea din setarile 
	 * predefinite ale grafului sau versiunea precedenta
	 * @throws IOException - in cazul in care apar erori de scriere in fisier
	 */
	public static int CastWriter(FileWriter cast, int version, String type, Graph g, 
			LinkedList<String> casted, String name)  throws IOException{
		
		if( version < g.getsettings(type)){
		
			if( !casted.contains(name) ){
			
				cast.write("OK cast "+ type + " " + name + " from Version=\"" + version 
						+ " to Version=\"" + g.getsettings(type)+ "\"\n");
				
				casted.add(name);
			}
			
			return g.getsettings(type);
		
		}
		else
		{
		
			if( version > g.getsettings(type)){
			
				if( !casted.contains(name) ){
				
					cast.write("Fail cast "+ type + " " + name + " from Version=\"" + version 
							+ " to Version=\"" + g.getsettings(type)+ "\"\n");
					
					casted.add(name);
				}
			}
			
			return g.getsettings(type);
		}
	}
}
