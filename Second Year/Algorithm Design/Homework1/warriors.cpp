// Copyright [2017] <Icatoiu Vlad Cosmin>

#include<math.h>
#include<stdio.h>
#include<iostream>
#include<fstream>

using namespace std;

int main() {
	ifstream in("warriors.in");

	long int lifes, max_level;

	in >> max_level >> lifes;

	ofstream out("warriors.out");

	// If we only have a life we have no other option than checking the levels
	// one by one.

	if(lifes == 1) {
		out << max_level;
		return 0;
	}

	double log = log2(max_level);

	// If we have enough lifes then we can apply the binary search algorithm to
	// find the number of lifes so the answer is ceil(log2(max_level)).

	if(lifes >= log) {
		out << ceil(log);
		return 0;
	}

	// If we have 2 lifes then we have to find the first number which multiplied
	// by its successor is greater than 2*max_level and that is the answer.

	if(lifes == 2) {
		int rad = floor(sqrt(2*max_level));

		while(rad*(rad+1) < 2*max_level) {
			rad++;
		}

		out << rad;
		return 0;
	}

	int minimum = 1, j;
	long long int sum;
	double aux;

	// Otherwise we do an algorithm based on binomials which I will furthermore
	// explain in the README

	while(true) {
		sum = 0;
		aux = 1;

		for(j = 1; j <= lifes; j++) {
			aux = aux *(double)(minimum-j+1);
			aux = aux /(double)j;
			sum += aux;
		}

		if(sum >= max_level) {
			break;
		}
		minimum++;
	}

	out << minimum;

	return 0;
}
