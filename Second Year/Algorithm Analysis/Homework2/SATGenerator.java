import java.util.*;

public class SATGenerator {

	private ArrayList<Integer> vars = new ArrayList<Integer>();

	public String Formula = "";

	//Metoda ce converteste un nod intr-o variabila din SAT

	public String convertNode(int i) {
		return "x" + i;
	}

	// Metoda ce creeaza clauzele corespunzatoare muchiilor

	public String EdgeClauseGenerator(int first, int second) {

		return "(" + convertNode(first) + "V" + convertNode(second) + ")";
	}

	//Metoda ce creeaza clauzele corespunzatoare conditiei k variabile din
	// n sa fie adevarate 

	public void CombinatorialClauseGenerator(int current_var, int total, int nr) {

		//daca am ajuns la finalul variabilelor si nu am completat vectorul 
		// cu variabile inseamna ca nu putem construi o clauza cu variabilele
		// actuale din vector
		
		if (current_var == nr && vars.size() + 1 != total)
			return;

		//adaugam variabila curenta in vector

		vars.add(current_var);

		//vedem daca am introdus k+1 variabile, caz in care cream 
		//clauza corespunzatoare 

		if (vars.size() == total) {

			Formula += "(";
			for (int i = 0; i < vars.size(); i++) {

				Formula += "~" + convertNode(vars.get(i));

				if (i != vars.size() - 1)
					Formula += "V";

			}

			Formula += ")^";
			
			//stergem variabila actuala din vector pentru a o putea forma si celelalte
			//variante de clauze

			vars.remove(vars.get(vars.size() - 1));
			return;
		}

		// pentru variabila curenta incercam sa introducem toate variabilele urmatoare
		// in vector 

		for (int i = current_var + 1; i <= nr; i++) {

			CombinatorialClauseGenerator(i, total, nr);
		}

		//stergem variabila curenta pentru a putea genera si celelalte combinatii

		vars.remove(vars.get(vars.size() - 1));

		return;
	}

}
