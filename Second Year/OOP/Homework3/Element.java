/**
 * @author Icatoiu Vlad-Cosmin Clasa ce creeaza un nou "tip de date" Element
 *         care are 2 campuri private val si type. Clasa a fost creata cu scopul
 *         de a manevra mai usor cu operanzii si a nu folos instanceof impreuna
 *         cu clasa Object. Astfel, toti operanzii sunt stocati ca 2 stringuri
 *         facand foarte convenabila si pastrarea NaN-ului si operatiile pe ei,
 *         putand fi usor convertiti, concatenati etc. Constructorul
 *         initializeaza cele 2 valori cu sirul vid.
 */
public class Element {

	private String val;
	private String type;

	public Element() {
		val = "";
		type = "";
	}

	/**
	 * @return - Metoda ce returneaza valoarea elementului
	 */
	public String getval() {
		return val;
	}

	/**
	 * @return - Metoda ce intoarce tipul elementului
	 */
	public String gettype() {
		return type;
	}

	/**
	 * Metoda ce modifica valoarea elementului
	 * 
	 * @param val
	 *            - noua valoare
	 */
	public void setval(Object val) {
		this.val +=  val;
	}

	/**
	 * Metoda ce modifica tipul elementului
	 * 
	 * @param type
	 *            - noul tip
	 */
	public void settype(String type) {
		this.type = type;
	}
}
