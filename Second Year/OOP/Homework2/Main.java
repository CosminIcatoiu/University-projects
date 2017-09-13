import java.io.*;
import java.util.*;

/**
 * @author Icatoiu Vlad-Cosmin
 *	Clasa ce contine metoda care citeste operatiile din fisierul de intrare si executa operatiile 
 *	corespunzatoare asupra grafului.
 */
public class Main {

	/**
	 * In interiorul functiei main avem un scanner cu ajutorul caruia citim din fisierul de intrare.
	 * Citirea se realizeaza linie cu linie. Ulterior, cu ajutorul unui vector de string-uri, splitam
	 * linia in cuvinte si verificam care este primul cuvant. In functie de acesta, determinam ce operatie
	 * trebuie exectuata si apelam respectiva metoda. Daca gasim o instructiune settings la un moment dat
	 * inseamna ca se pregateste o deserializare, deci cream fisierul in care se vor scrie operatiile de 
	 * cast si de asemenea, reinitializam graful pentru a introduce nodurile in el.
	 * @param args - parametrii ce vin din linia de comanda, in cazul nostru numele fisierului de intrare
	 * @throws IOException - in cazul in care apar erori la deschiderea fisierelor sau la citire
	 */
	public static void main(String[] args) throws IOException{
		
		File inputfile= new File(args[0]);

		Scanner in = new Scanner(inputfile);
		
		String line;
		
		line=in.nextLine();
		
		String words[]=line.split(" ");

		FileWriter w=null; 
		
		Graph g= new Graph(words[1],words[2],words[3]);
		
		while(in.hasNextLine()){
			
			line=in.nextLine();
			
			words=line.split(" ");
			
			if(words[0].equals(new String("Add"))){
				
				NodeOperations.addNode(g, words);
			}
			
			if(words[0].equals(new String("AddM"))){
				
				NodeOperations.addEdge(g, words[1], words[2]);
			}
			
			if(words[0].equals(new String("DelM"))){
				
				NodeOperations.deleteEdge(g, words[1], words[2]);
			}
			
			if(words[0].equals(new String("Del"))){
				
				NodeOperations.removeNode(g, words[1]);
			}
			
			if(words[0].equals(new String("Serialize"))){
				
				w=new FileWriter(words[2]);
				
				SerializeOperations.Serialize(g, words[1], w);
				
				w.close();
			}
			
			if(words[0].equals(new String("Settings"))){
				
				g=null;
				g=new Graph(words[1],words[2],words[3]);
				
				line=in.nextLine();
				
				words=line.split(" ");
				
				File inputfile2= new File(words[1]);
				
				Scanner in2= new Scanner(inputfile2);
				
				words=words[1].split("\\.");
				
				
				int index=words[0].length()-1;
				
				while( !words[0].substring(index, index +1).equals("/") && index > 0 
						&& !words[0].substring(index, index +1).equals("\\") ){
					index --;
				}
				
				String newfile = null;
				if(index != 0){
					
					newfile= new String(words[0].substring(0, index+1) +"Deserializare_"+ 
							words[0].substring(index+1)+ "_CAST.log");
				}
				else
				{
					newfile = new String("Deserializare_"+ words[0].substring(index)+ "_CAST.log");
				}
				
				FileWriter cast = new FileWriter(newfile);
				
				DeserializeOperations.Deserialize(g, in2, cast);
				
				cast.close();
			}
		}
		
		w.close();
		in.close();

	}
}
