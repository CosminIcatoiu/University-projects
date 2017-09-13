/**
 * @author Icatoiu Vlad-Cosmin Clasa este abstracta deoarece existenta unui
 *         obiect Addition nu are sens din punct de vedere logic.
 */
public abstract class Addition {

	/**
	 * Singura metoda a clasei are rolul major de a efectua adunarea intre 2
	 * elemente. Practic in interiorul ei, se verifica tipul elementelor adunate
	 * si in functie de acesta se aplica adunarea corespunzatoare. De asemenea
	 * se verifica daca nu cumva un element este NaN, caz special, obtinandu-se
	 * rezultatul corespunzator. De asemenea pentru numerele de tip double se
	 * verifica rotunjirea acestora in momentul in care sunt concatenate la un
	 * sir.
	 * 
	 * @param a
	 *            - primul element ce trebuie adunat
	 * @param b
	 *            - al doilea element ce trebuie adunat
	 * @return - se returneaza rezultatul operatiei de adunare
	 */
	public static Element addition(Element a, Element b) {

		Element aux = new Element();

		if (a.gettype().equals("String") && b.gettype().equals("String")) {

			aux.settype("String");

			aux.setval(a.getval() + b.getval());

			return aux;
		}

		if (a.gettype().equals("Int") && b.gettype().equals("Int")) {

			if (a.getval().equals("NaN") || b.getval().equals("NaN")) {

				aux.settype("Int");
				
				aux.setval("NaN");
				
				return aux;
			}

			int c = Integer.parseInt(a.getval()) + Integer.parseInt(b.getval());

			aux.settype("Int");
			
			aux.setval(c);
			
			return aux;
		}

		if (a.gettype().equals("String") && (b.gettype().equals("Int") || b.gettype().equals("Double"))) {

			aux.settype("String");

			if (b.gettype().equals("Double") && !b.getval().equals("NaN")) {

				double aux1 = Double.parseDouble(b.getval());

				aux1 = Math.round(aux1 * 100.0) / 100.0;

				aux.setval(a.getval() + aux1);

				return aux;
			}

			aux.setval(a.getval() + b.getval());

			return aux;
		}

		if ((a.gettype().equals("Int") || a.gettype().equals("Double")) && b.gettype().equals("String")) {

			aux.settype("String");

			if (a.gettype().equals("Double") && !a.getval().equals("NaN")) {

				double aux1 = Double.parseDouble(a.getval());

				aux1 = Math.round(aux1 * 100.0) / 100.0;

				aux.setval(aux1 + b.getval());

				return aux;
			}
			
			aux.setval("" + a.getval() + b.getval());

			return aux;
		}

		if (a.getval().equals("NaN") || b.getval().equals("NaN")) {

			aux.settype("Double");

			aux.setval("NaN");
			
			return aux;
		}

		double c = Double.parseDouble(a.getval()) + Double.parseDouble(b.getval());

		aux.settype("Double");
		
		aux.setval(c);

		return aux;

	}
}
