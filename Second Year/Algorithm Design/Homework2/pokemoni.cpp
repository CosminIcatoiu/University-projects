// Copyright [2017] <Icatoiu Vlad Cosmin>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <list>

using namespace std;

/* Starea curenta este data de nod, pokemonul cu care suntem si cate schimbari
mai putem face. */
long long int dp[101][20][21];

/* Reprezinta costul fiecarei muchii cu fiecare pokemon. Ultimul parametru este
a cata aparitie a muchiei este, pentru a putea diferentia intre mai multe muchii
de la x la y. */
int weights[101][101][20][1000];

// Reprezinta numarul de aparitii al fiecare muchii.
int appearences[101][101];

/* Costul unui drum de la sursa pana la un nod. Redundant pentru ca e pastrat
si in matricea dp, dar l-am folosit la cazul de baza. */
long long int cost[101];
vector< list < int> > graph;

// Coada de prioritati pentru algoritmul Dijkstra
priority_queue<pair<long long int, int>, vector<pair<long long int, int> >,
									greater<pair <long long int, int> > > q;


/* Functie ce realizeaza algoritmul Dijkstra pentru cazul de baza si anume 
atunci cand nu avem schimbari de facut. Coada de prioritati va contine perechi
cost, nod ordonate descrescator dupa cost. Astfel, dupa ce scoatem un nod din
coada, pentru toti vecinii sai (indiferent ca acestia sunt duplicate sau nu -
verificam pentru toate muchiile x-y nu doar pentru una) vedem daca nu cumva
putem sa relaxam drumul minim pana la sursa cu ajutorul nodului curent. De 
precizat ca acest lucru se face pentru un singur pokemon o data. */
void fill_basic(int i) {
	pair<long long int, int> aux = q.top();
	int node = aux.second;
	q.pop();

	if(aux.first == cost[node]) {
		list<int>::const_iterator it;

		for(it = graph[node].begin(); it != graph[node].end(); ++it) {
			int j;

			for(j = 0; j < appearences[node][(*it)]; j++) {
				if(aux.first + weights[node][(*it)][i][j] < cost[(*it)]) {
					cost[(*it)] = aux.first + weights[node][(*it)][i][j];

					dp[(*it)][i][0] = cost[(*it)];

					q.push(make_pair(cost[(*it)], (*it)));
				}
			}
		}
	}
}

/* Functia basic_case nu face altceva decat sa aplice functia anterioara pentru
toti pokemonii si astfel sa rezolve cazul K = 0. */
void basic_case(int node, int nr_pok) {
	int i = 0;

	for(i = 0; i < nr_pok; i++) {
		memset(cost, 1000000, sizeof(cost));

		cost[node] = 0;
		dp[node][i][0] = 0;

		q.push(make_pair(0, node));

		while(!q.empty()) {
			fill_basic(i);
		}
	}
}

/* Functia fill_dp nu face altceva decat sa extinda cazul de baza pentru un K
anume. Principiul este acelasi ca la Dijkstra, singura diferenta aparand la
relaxare. Pe langa relaxarea clasica in care se verifica costurile de la pasul
curent (K - ul curent), se verifica daca nu cumva putem sa relaxam drumul
minim printr-un alt pokemon de la pasul anterior, pas deja calculat. La final se
introduce in coada cea mai buna relaxare, daca ea exista. */
void fill_dp(int pok, int attempts, int P) {
	int i, j;
	pair<long long int, int> aux = q.top();
	q.pop();
	int node = aux.second;

	if(aux.first == dp[node][pok][attempts]) {
	list<int>::const_iterator it;

		for(it = graph[node].begin(); it != graph[node].end(); ++it) {
			for(i = 0; i < appearences[node][(*it)]; i++) {
				int ok = 0;
				if(aux.first + weights[node][(*it)][pok][i]
												< dp[(*it)][pok][attempts]) {
					dp[(*it)][pok][attempts] = aux.first +
												weights[node][(*it)][pok][i];
					ok = 1;
				}

				for(j = 0 ; j < P; j++) {
					if(j != pok) {
						if(dp[node][j][attempts-1] + weights[node][(*it)][j][i]
												< dp[(*it)][pok][attempts]) {
							dp[(*it)][pok][attempts] = dp[node][j][attempts -1]
												+ weights[node][(*it)][j][i];
							ok = 1;
						}
					}
				}

				if(ok == 1) {
					q.push(make_pair(dp[(*it)][pok][attempts], (*it)));
				}
			}
		}
	}
}

int main() {
	int N, M, P, K;
	int first_node, second_node, pok, changes;

	memset(appearences, 0, sizeof(appearences));
	memset(dp, 1000000, sizeof(dp));

	ifstream in("pokemoni.in");

	in >> N >> M >> P >> K;
	graph.resize(N + 1);
	int i, j;

	/* La citire se initializeaza graful, tabela cu costuri si tabela cu
	aparitii. */
	for(i = 1; i <= M; i++) {
		in >> first_node >> second_node;
		for(j = 0; j < P; j++) {
			in >> pok;
			int index = appearences[first_node][second_node];

			weights[first_node][second_node][j][index] = pok;
			weights[second_node][first_node][j][index] = pok;
		}

		if(appearences[first_node][second_node] == 0) {
				graph[first_node].push_back(second_node);
				graph[second_node].push_back(first_node);
		}

		appearences[first_node][second_node] ++;
		appearences[second_node][first_node] ++;
	}

	/* Calculam cazul de baza si apoi cel mai bun drum pentru aces caz.
	Rezultatul se afla in orasul 1, deoarece cazul de baza e apelat cu orasul N
	si pe noi ne intereseaza astfel drumul minim intre capete. Evident trebuie
	sa analizam toti pokemonii pentru a determina minimul. */
	basic_case(N, P);

	long long int min = dp[1][0][0];

	for(i = 0; i < P; i++) {
		if(dp[1][i][0] < min) {
			min = dp[1][i][0];
		}
	}

	// Daca avem posibilitati de a schimba pokemonii
	if(K > 0) {
		// Evident pentru orice pokemon si orice numar de schimbari drumul
		// minim din starea finala pana in starea finala este 0.
		for(i = 1; i <= K; i++) {
			for(j = 0; j < P; j++) {
				dp[N][j][i] = dp[N][j][0];
			}
		}

		/* Pentru fiecare numar de schimbari si pentru fiecare pokemon umplem
		succesiv matricea dp. Acest lucru este posibil pentru ca pentru a
		defini costul minim pentru un pokemon intr-o stare nu avem nevoie 
		decat de costul minim pentru acel pokemon in orasul anterior sau 
		de costul minim pentru toti pokemonii, dar pentru K - 1, lucruri
		care evident se calculeaza inainte. */
		for(changes = 1; changes <= K; changes++) {
			for(pok = 0; pok < P; pok++) {
				q.push(make_pair(0, N));

				while(!q.empty()) {
					fill_dp(pok, changes, P);
				}
			}
		}

		// La final stabilim minimul care din nou va fi in orasul unu, de
		// aceasta data pentru numarul maxim de schimbari.
		min = dp[1][0][K];
		for(i = 0; i < P; i++) {
			if(dp[1][i][K] < min) {
				min = dp[1][i][K];
			}
		}
	}

	ofstream out("pokemoni.out");
	out << min;
}
