/**
 * @author Icatoiu Vlad-Cosmin Clasa este abstracta deoarece nu are sens din
 *         punct de vedere logic exsitenta unui obiect Division.
 */
public abstract class Division {

	/**
	 * Singura metoda a clasei este astfel statica pentru a putea fi apelata
	 * fara crearea unui obiect. Principalul scop al acestei metode este sa
	 * realizeze impartirea intre 2 elemente. Astfel, in interiorul ei se
	 * verifica tipul elementelor primite ca parametru si in functie de acesta
	 * se aplica impartirea corespunzatoare. De asemenea, se verifica valoarea
	 * elementelor si in caz ca unul dintre ele este NaN se aplica un caz
	 * special.
	 * 
	 * @param a
	 *            - primul element
	 * @param b
	 *            - al doilea element
	 * @return - se returneaza rezultatul impartirii intre cele 2 elemente
	 */
	public static Element division(Element a, Element b) {

		Element aux = new Element();

		if (a.gettype().equals("Int") && b.gettype().equals("Int")) {

			aux.settype("Int");

			if (a.getval().equals("NaN") || b.getval().equals("NaN") || b.getval().equals("0")) {

				aux.setval("NaN");
				
				return aux;
			}

			int c = Integer.parseInt(a.getval()) / Integer.parseInt(b.getval());

			aux.setval(c);

			return aux;
		}

		if (a.gettype().equals("String") && b.gettype().equals("String")) {

			aux.settype("Int");

			if (b.getval().length() == 0) {
				
				aux.setval("NaN");
				
				return aux;
			}

			int c = a.getval().length() / b.getval().length();

			aux.setval(c);

			return aux;
		}

		if (a.gettype().equals("String") && b.gettype().equals("Int")) {

			aux.settype("String");

			if (b.getval().equals("NaN") || Integer.parseInt(b.getval()) <= 0) {

				aux.setval(a.getval());

				return aux;
			}

			aux.setval(a.getval().substring(0, a.getval().length() / Integer.parseInt(b.getval())));

			return aux;
		}

		if (a.gettype().equals("Int") && b.gettype().equals("String")) {

			aux.settype("Int");

			if (a.getval().equals("NaN") || b.getval().length() == 0) {

				aux.setval("NaN");
				
				return aux;
			}

			int c = Integer.parseInt(a.getval()) / b.getval().length();

			aux.setval(c);

			return aux;
		}

		if (a.gettype().equals("String") && b.gettype().equals("Double")) {

			aux.settype("Double");

			if (b.getval().equals("NaN") || Double.parseDouble(b.getval()) == 0) {

				aux.setval("NaN");
				
				return aux;
			}

			double c = a.getval().length() / Double.parseDouble(b.getval());

			aux.setval(c);
			
			return aux;
		}

		if (a.gettype().equals("Double") && b.gettype().equals("String")) {

			aux.settype("Double");

			if (a.getval().equals("NaN") || b.getval().length() == 0) {

				aux.setval("NaN");
			
				return aux;
			}

			double c = Double.parseDouble(a.getval()) / b.getval().length();

			aux.setval(c);
			
			return aux;
		}

		aux.settype("Double");

		if (a.getval().equals("NaN") || b.getval().equals("NaN") || Double.parseDouble(b.getval()) == 0) {

			aux.setval("NaN");

			return aux;
		}

		double c = Double.parseDouble(a.getval()) / Double.parseDouble(b.getval());

		aux.setval(c);

		return aux;
	}
}
