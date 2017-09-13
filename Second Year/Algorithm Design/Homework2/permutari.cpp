// Copyright [2017] <Icatoiu Vlad Cosmin>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<list>
#include<stack>
#include<fstream>

using namespace std;

// Graful folosit este unul orientat in care avem 26 de noduri, corespunzatoare
// tururor literelor din alfabet.
vector <list <int > > graph;
vector<int> visited;
stack <char> order;
int length_check = 0;
int cycle = 0;

/* Functie care primeste 2 cuvinte ca parametru si le analizeaza lexicografic.
Parcurge cuvintele pozitie cu pozitie si la prima pozitie diferita creeaza
o muchie in graf intre acele 2 litere( de la litera din primul cuvant la
litera din al doilea cuvant. De asemenea analizeaza daca nu cumva cele 2 
cuvinte nu se pot afla in niciun alfabet in aceasta ordine lexicografica.*/
void create_link(char * first_word, char * second_word) {
	int l1 = strlen(first_word);
	int l2 = strlen(second_word);
	int i = 0, ok = 0;

	// Crearea legaturii intre cele 2 litere
	while(i < l1 && i < l2) {
		if(first_word[i] != second_word[i]) {
			ok = 1;
			graph[first_word[i]-'a'].push_back(second_word[i]-'a');
			break;
		} else {
			i++;
		}
	}

	/* Verificarea daca nu cumva primul cuvant este mai lung si contine la
	inceput primul cuvant.*/
	if(i == l2 && ok == 0 && i != l1) {
		length_check = 1;
	}
}

/* Functie care parcurge un graf in inaltime, marcheaza un nod ca fiind vizitat
si apoi parcurge vecinii. Daca am dat de un nod aflat in curs de vizitare
inseamna ca am dat de un ciclu. Altfel, apelam functia recursiv pentru vecin
daca nu a fost deja vizitat. Dupa ce s-au terminat de parcurs toti vecinii,
marcam nodul ca fiind vizitat si il introducem in stiva ce pastreaza ordinea.*/ 
void dfs(int node) {
	visited[node] = 1;

	list<int>::const_iterator it;

	for(it = graph[node].begin(); it != graph[node].end(); ++it) {
		if(visited[(*it)] == 1) {
			cycle = 1;
			break;
		}
		if(visited[(*it)] != 2) {
			dfs(*it);
		}
	}
	visited[node] = 2;
	order.push('a' + node);
}

/* Functie ce realizeaza sortarea topologica parcurgand toate nodurile si 
apeland functia dfs pe cele care nu au fost deja vizitate, dar doar daca nu 
s-a gasit deja un ciclu.*/
void top_sort() {
	int i;

	for(i = 0; i < 26; i++) {
		if(cycle == 1)
			break;
		if(visited[i] == 1) {
			cycle = 1;
			break;
		}
		if(visited[i] == 0) {
			dfs(i);
		}
	}
}

int main() {
	graph.resize(26);
	visited.resize(26, 0);
	char * first_word = (char *)calloc(100, sizeof(char));
	char * second_word = (char *)calloc(100, sizeof(char));
	int words, i;

	ifstream in("permutari.in");
	ofstream out("permutari.out");
	in >> words;

	// Daca primim un singur cuvant orice alfabet este corect
	if(words == 1) {
		out << "abcdefghijklmnopqrstuvwxyz";
		return 0;
	}

	in >> first_word >> second_word;
	create_link(first_word, second_word);

	// Construim graful in timp ce citim cuvintele
	for(i = 1; i <= words - 2; i++) {
		strcpy(first_word, second_word);
		in >> second_word;
		create_link(first_word, second_word);
	}

	if(length_check == 1) {
			out << "Imposibil" << endl;
			return 0;
	}

	top_sort();

	if(cycle == 1) {
		out << "Imposibil" << endl;
	} else {
		while(!order.empty()) {
			out << order.top();
			order.pop();
		}
		out << endl;
	}
	return 0;
}
