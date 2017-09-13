import java.util.*;
import java.io.*;

/**
 * @author Icatoiu Vlad-Cosmin Clasa Main este clasa creier a temei care aplica
 *         toate metodele asupra expresiei si obtine rezultatul pe care il
 *         returneaza ulterior. Clasa este abstracta pentru ca nu are sens in
 *         cadrul programului existenta unui obiect de acest tip.
 */
public abstract class Main {

	/**
	 * Metoda main initializeaza doua mape ce realizeaza corespondenta intre
	 * numele unei variabile si tipul, respectiv valoarea ei. De asemenea metoda
	 * contine un evaluator ce va evalua ulterior expresia, un scanner cu care
	 * citim din fisierul de intrare si un writer cu ajutorul caruia scriem in
	 * fisierul de iesire. Cat timp avem ce citi din fisier splitam linia dupa
	 * spatii si verificam primul cuvant( daca este operatie sau o declarare).
	 * Dupa aceea initializeaza corespondentele, singurul caz special fiind
	 * acela cand stringul are mai multe spatii( Ex. "ana are mere"). Daca nu
	 * este o declaratie, atunci reconstruim expresia matematica, de aceasta
	 * data fara spatii intre caractere si cream arborele. Ulterior evaluam
	 * expresia si salvam rezultatul intr-un element auxiliar. Apoi scriem
	 * rezultatul in fisier. Singurul caz special este acela cand rezultatul
	 * este double deoarece trebuie sa il rotunjim. Trebuie sa avem grija ca el
	 * sa nu fie NaN si daca nu sa rotunjim la 2 zecimale. La final inchidem
	 * fisierele de citire si scriere.
	 * 
	 * @param args
	 *            - parametrii liniei de comanda
	 * @throws IOException
	 *             - se arunca o exceptie in cazul in care nu se reuseste citrea
	 *             sau scrierea in fisier.
	 */
	public static void main(String[] args) throws IOException {

		HashMap<String, String> type = new HashMap<String, String>();

		HashMap<String, String> val = new HashMap<String, String>();

		ASTEvaluator eval = new ASTEvaluator();

		Scanner in = new Scanner(new BufferedReader(new FileReader("arbore.in")));

		FileWriter writer = new FileWriter("arbore.out");

		String line;

		String[] split;

		while (in.hasNextLine()) {

			line = in.nextLine();

			split = line.split(" ");

			if (!split[0].equals("eval")) {

				if (!split[0].equals("string")) {

					type.put(split[1], split[0]);

					val.put(split[1], split[3].substring(0, split[3].length() - 1));

				} else {

					type.put(split[1], split[0]);

					String aux = "";

					for (int i = 3; i < split.length; i++) {

						aux += split[i] + " ";
					}

					val.put(split[1], aux.substring(1, aux.length() - 3));

				}
			} else {

				String expression = "";

				for (int i = 1; i < split.length; i++) {

					expression += split[i];
				}

				expression = expression.substring(0, expression.length() - 1);

				Node n = ASTCreator.create(RPNCreator.convert(expression), type, val);

				Element aux = n.accept(eval);

				if (!aux.gettype().equals("Double")) {

					writer.write(aux.getval() + "\n");

				} else {

					if (aux.getval().equals("NaN")) {

						writer.write("NaN" + "\n");

					} else {

						double aux1 = Double.parseDouble(aux.getval());

						aux1 = Math.round(aux1 * 100.0) / 100.0;

						writer.write(aux1 + "\n");
					}
				}
			}
		}

		writer.close();

		in.close();

	}

}
