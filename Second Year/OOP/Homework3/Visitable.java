/**
 * @author Icatoiu Vlad-Cosmin Interfata pe care nodurile o implementeaza pentru
 *         a putea fi calculata valoarea expresiei matematice
 */
public interface Visitable {

	/**
	 * Metoda pe care o implementeaza fiecare nod deoarece ea practic permite
	 * vizitarea nodului curent de catre Vizitator si in functie de tipul
	 * nodului Vizitatorul aplica operatia corespunzatoare
	 * 
	 * @param v
	 *            - Vizitatorul
	 * @return - Se returneaza un element pe care Vizitatorul il returneaza
	 *         atunci cand apeleaza metoda visit pe tipul de nod corespunzator
	 */
	public Element accept(Visitor v);
}
