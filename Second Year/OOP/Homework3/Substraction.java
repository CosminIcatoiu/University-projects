/**
 * @author Icatoiu Vlad-Cosmin Clasa este abstracta deoarece existenta unui
 *         obiect Substraction nu are sens logic si astfel, singura sa metoda
 *         este statica.
 */
public abstract class Substraction {

	/**
	 * Singura metoda a clasei are rolul de a realiza scaderea intre 2 elemente.
	 * In interiorul ei se verifica tipul elementelor si in functie de acesta se
	 * aplica inmultirea corespunzatoare. De asemenea, se verifica aparitia unor
	 * cazuri speciale si anume cand unul din elemente este NaN.
	 * 
	 * @param a
	 *            - primul element
	 * @param b
	 *            - al doilea element
	 * @return - se returneaza rezultatul scaderii celor 2 elemente
	 */
	public static Element substraction(Element a, Element b) {

		Element aux = new Element();

		if (a.gettype().equals("Int") && b.gettype().equals("Int")) {

			if (a.getval().equals("NaN") || b.getval().equals("NaN")) {

				aux.settype("Int");

				aux.setval("NaN");

				return aux;
			}

			int c;

			c = Integer.parseInt(a.getval()) - Integer.parseInt(b.getval());

			aux.settype("Int");

			aux.setval(c);

			return aux;
		}

		if (a.gettype().equals("String") && b.gettype().equals("String")) {

			aux.settype("Int");

			int c = a.getval().length() - b.getval().length();

			aux.setval(c);

			return aux;
		}

		if (a.gettype().equals("String") && b.gettype().equals("Double")) {

			aux.settype("Double");

			if (b.getval().equals("NaN")) {

				aux.setval("NaN");

				return aux;
			}

			double c = a.getval().length() - Double.parseDouble(b.getval());

			aux.setval(c);

			return aux;
		}

		if (a.gettype().equals("Double") && b.gettype().equals("String")) {

			aux.settype("Double");

			if (a.getval().equals("NaN")) {

				aux.setval("NaN");

				return aux;
			}

			double c = Double.parseDouble(a.getval()) - b.getval().length();

			aux.setval(c);

			return aux;
		}

		if (a.gettype().equals("Int") && b.gettype().equals("String")) {

			aux.settype("Int");

			if (a.getval().equals("NaN")) {

				aux.setval("NaN");

				return aux;
			}

			int c = Integer.parseInt(a.getval()) - b.getval().length();

			aux.setval(c);

			return aux;
		}

		if (a.gettype().equals("String") && b.gettype().equals("Int")) {

			aux.settype("String");

			if (b.getval().equals("NaN")) {

				aux.setval(a.getval());

				return aux;
			}

			if (Integer.parseInt(b.getval()) > a.getval().length()) {

				aux.setval("");

				return aux;
			}

			if (Integer.parseInt(b.getval()) >= 0) {

				aux.setval(a.getval().substring(0, a.getval().length() - Integer.parseInt(b.getval())));

				return aux;
			}

			aux.setval(a.getval());

			for (int i = 0; i < Math.abs(Integer.parseInt(b.getval())); i++) {

				aux.setval("#");
			}

			return aux;
		}

		aux.settype("Double");

		if (a.getval().equals("NaN") || b.getval().equals("NaN")) {

			aux.setval("NaN");

			return aux;
		}

		double c = Double.parseDouble(a.getval()) - Double.parseDouble(b.getval());

		aux.setval(c);

		return aux;
	}
}
