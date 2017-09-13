import java.io.*;
import java.util.*;

public class Main {

	public static void main(String[] args) throws IOException{
		
		// cu ajutorul scanner-ului citim din fisierul de intrare si cu 
		// ajutorul writer-ului scriem in fisierul de output

		Scanner in = new Scanner(new BufferedReader(new FileReader("test.in")));

		FileWriter w= new FileWriter("test.out");
		
		int NrV= in.nextInt();
		
		int NrE= in.nextInt();
		
		int k=in.nextInt();
		
		SATGenerator sat = new SATGenerator();
		
		//cream toate clauzele corespunzatoare conditiei de k variabile din n
		// sa fie adevarate 

		for(int i =1; i <= NrV - k; i++){
			sat.CombinatorialClauseGenerator(i, k+1, NrV);
		}
		
		int first,second;

		// cream clauzele corespunzatoare muchiilor si le adaugam la formula 
		
		for(int i = 1; i<= NrE ; i++){
			
			first=in.nextInt();
			second=in.nextInt();
			
			sat.Formula+=sat.EdgeClauseGenerator(first, second);
			
			if( i != NrE)
				sat.Formula+="^";
			
		}
		
		//scriem formula obtinuta in fisier

		w.write(sat.Formula);
		
		in.close();
		w.close();
	}

}
