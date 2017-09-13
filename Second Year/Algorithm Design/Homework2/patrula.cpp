// Copyright [2017] <Icatoiu Vlad Cosmin>

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

vector<list< int > > graph;
// O matrice ce contine cate muchii exista de la fiecare nod la altul
int ** appearences;

/* Pentru fiecare nod se pastreaza parintii, adica nodurile din care se poate
ajunge direct acolo astfel incat calea totala sa fie minima */
vector<list< int > > parents;

// Pentru fiecare nod se pastreaza cate drumuri minime se vin pana in el.
vector<long long int> nr_paths;

// Distanta fata de sursa
vector<long long int> distances;

// Numarul de strazi pe care l-ar lumina fiecare nod.
vector<long long int> lights;

/* Functie ce realizeaza o parcurgere in latime a grafului si spre deosebire
de algoritmul clasic de drum minim, care actualizeaza drumul minim atunci cand
nodul nu fusese vizitat, se mai verifica daca, atunci cand nodul e vizitat,
distanta pana la sursa e 1 + distanta din nodul curent. Acest lucru ar
reprezenta un alt drum minim. De asemenea se salveaza nr_path-uri si parintii
in ambele cazuri, iar daca nodul nu fusese vizitat e introdus in coada.
*/
void bfs(int node) {
	distances[node] = 0;
	nr_paths[node] = 1;
	queue<int> q;
	list<int>::const_iterator it;

	q.push(node);

	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(it = graph[u].begin(); it != graph[u].end(); ++it) {
			if(distances[(*it)] == distances[u] +1) {
				nr_paths[(*it)] += appearences[u][(*it)] * nr_paths[u];
				parents[(*it)].push_back(u);
			}

			if(distances[(*it)] == INT_MAX) {
				distances[(*it)] = distances[u] + 1;
				q.push((*it));
				nr_paths[(*it)] = appearences[u][(*it)] * nr_paths[u];
				parents[(*it)].push_back(u);
			}
		}
	}
}

/* Functie ce calculeaza pentru fiecare nod cate strazi ar lumina daca am 
lumina respectivul oras si salveaza valoarea maxima in max.
*/
long long int count(int node, int end, long long int * max, long long int pr) {
	list<int>::const_iterator it;
	long long int crt_result = 0;

	if(parents[node].front() == end) {
		lights[node] += 2* pr * appearences[node][end];

		if(lights[node] > *max) {
			*max = lights[node];
		}
		return pr * appearences[node][end];
	}

	for(it = parents[node].begin(); it != parents[node].end(); ++it) {
		long long int aux = count((*it), end, max, pr*appearences[node][(*it)]);
		crt_result += aux;
	}

	if(node != 1) {
		lights[node] += 2* crt_result;
	} else {
		lights[node] += crt_result;
	}

	if(lights[node] > *max) {
		*max = lights[node];
	}

	return crt_result;
}

int main() {
	int nr_nodes, nr_roads;
	int first_node, second_node;

	ifstream in("patrula.in");
	in >> nr_nodes >> nr_roads;

	graph.resize(nr_nodes + 1);
	parents.resize(nr_nodes + 1);
	nr_paths.resize(nr_nodes + 1);
	distances.resize(nr_nodes + 1, INT_MAX);
	lights.resize(nr_nodes +1, 0);

	appearences = (int **)calloc(nr_nodes + 1, sizeof(int *));
	int i;

	for(i = 0; i <= nr_nodes; i++) {
		appearences[i] = (int *)calloc(nr_nodes + 1, sizeof(int));
	}

	// La citire se initializeaza graful si matricea de aparitii a fiecarei
	// muchii.
	for(i = 1; i <= nr_roads; i++) {
		in >> first_node >> second_node;
		if(appearences[first_node][second_node] == 0) {
			graph[first_node].push_back(second_node);
			graph[second_node].push_back(first_node);
		}
		appearences[first_node][second_node] ++;
		appearences[second_node][first_node] ++;
	}

	bfs(nr_nodes);
	long long int max = -1;
	ofstream out("patrula.out");
	count(1, nr_nodes, &max, 1);

	out << nr_paths[1];
	out << endl;
	out << fixed << setprecision(3) << ((double)max) / nr_paths[1] << endl;
	return 0;
}
