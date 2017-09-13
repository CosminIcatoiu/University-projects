import java.util.*;

/**
 * @author Icatoiu Vlad-Cosmin Clasa este abstracta pentru ca nu are sens
 *         existenta unui obiect ce creeaza un reverse polish notation. Practic
 *         scopul clasei este acela de a parsa o expresie matematica si a crea
 *         un RPN ce ulterior va fi interpretat pentru a crea un arbore
 */
public abstract class RPNCreator {

	/**
	 * Metoda ce stabileste prioritatile intre operatori si anume ca minus si
	 * plus sunt egali si inferiori lui ori si impartit care sunt si ei egali.
	 * 
	 * @param op1
	 *            - primul operator
	 * @param op2
	 *            - al doilea operator
	 * @return - se returneaza un intreg in functie de prioritatea primului fata
	 *         de al doilea, 0 daca au prioritati egale , -1 daca primul are
	 *         prioritate mai mica si 1 daca primul are prioritate mai mare
	 */
	public static int priority(char op1, char op2) {

		if (op1 == op2)
			return 0;

		if ((op1 == '*' || op1 == '/') && (op2 == '/' || op2 == '*'))
			return 0;

		if ((op1 == '+' || op1 == '-') && (op2 == '+' || op2 == '-'))
			return 0;

		if ((op1 == '-' || op1 == '+') && (op2 == '*' || op2 == '/'))
			return -1;

		return 1;
	}

	/**
	 * Metoda principala care transforma o expresie matematica intr-un RPN.
	 * Principiul de transformare este urmatorul: daca se intalneste o variabila
	 * atunci ea este pusa automat in vectorul de output. Daca se intalneste un
	 * operator se verifica daca nu cumva operatorul din varful stivei are
	 * prioritate mai mare sau egala, caz in care extragem ce se afla pe stiva
	 * si mutam in output. Daca se intalneste o paranteza este ca si cand am
	 * avea o expresie in interiorul expresiei. In momentul in care intalnim
	 * paranteza inchizatoare mutam totul de pe stiva in pana la prima paranteza
	 * in output.
	 * 
	 * @param expression
	 *            - expresia matematica
	 * @return - se returneaza un vector de stringuri ce reprezinta RPN-ul
	 */
	public static ArrayList<String> convert(String expression) {

		ArrayList<String> output = new ArrayList<String>();

		String operations = "+-*/()";

		Stack<Character> stack = new Stack<Character>();

		for (int i = 0; i < expression.length(); i++) {

			if (!operations.contains("" + expression.charAt(i))) {

				String aux = "";

				while (!operations.contains("" + expression.charAt(i))) {

					aux += expression.charAt(i);

					i++;

					if (i == expression.length())
						break;
				}

				i--;

				output.add(aux);

			} else {

				if (expression.charAt(i) == '(') {

					stack.push(expression.charAt(i));

				} else {

					if (expression.charAt(i) == ')') {

						while (stack.peek() != '(') {

							output.add("" + stack.pop());
						}

						stack.pop();

					} else {

						while (!stack.isEmpty()) {

							if (RPNCreator.priority(expression.charAt(i), stack.peek()) > 0) {

								break;

							}

							output.add("" + stack.pop());
						}

						stack.push(expression.charAt(i));
					}
				}
			}
		}

		while (!stack.isEmpty()) {

			output.add("" + stack.pop());
		}

		return output;
	}
}
