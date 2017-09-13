// Copyright [2017] <Icatoiu Vlad Cosmin>
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

using namespace std;

long long int * coord, * powers;

int ** dp;

int main() {
	long long int n, S;

	ifstream in("stropitori.in");

	string stadium;

	getline(in, stadium);

	in >> n >> S;

	powers = (long long int *)calloc(n, sizeof(long long int));

	coord = (long long int *)calloc(n, sizeof(long long int));

	dp = (int **)calloc(n, sizeof(int *));

	long long int i;

	for(i = 0; i < n; i++) {
		dp[i] = (int *)calloc(3, sizeof(int));
	}

	for(i = 0; i < n; i++) {
		in >> coord[i];
	}

	for(i = 0; i < n; i++) {
		in >> powers[i];
	}

	// For setting up the iterative dp method we have to set the values for the
	// last sprinkler. Obviously if we block it the value is 0. If we make it
	// sprinkle to the right we have to check if it doesn`t go outside the
	// stadium. And for the left, we check if it doesn`t sprinkle over the
	// previous one.

	dp[n-1][0] = 0;
	if(coord[n-1] + powers[n-1] <= S) {
		dp[n-1][2] = 1;
	} else {
		dp[n-1][2] = -1;
	}

	if(coord[n-1] - powers[n-1] > coord[n-2]) {
		dp[n-1][1] = 1;
	} else {
		dp[n-1][1] = -1;
	}

	// For the next sprinklers
	for(i = n-2; i >= 0 ; i --) {
		// If we choose to block a sprinkle we don`t influence the future ones
		// so we can pick whatever good combination we want for the next one.

		dp[i][0] = max(max(dp[i+1][0], dp[i+1][1]), dp[i+1][2]);

		// If we want to put it to the left and we are not at the first one
		// we check if we can put it to the left, and if we can we again don`t
		// influence the next one so we choose the best position for the next
		// one.

		if(i != 0) {
			if(coord[i] - powers[i] > coord[i-1]) {
				dp[i][1] = 1 + max(max(dp[i+1][0], dp[i+1][1]), dp[i+1][2]);
			} else {
				dp[i][1] = -1;
			}
		} else {
			// For the first sprinkler the only difference is that we check if
			// we go outside the stadium.

			if(coord[0] - powers[0] >= 0) {
				dp[0][1] = 1 + max(max(dp[1][0], dp[1][1]), dp[1][2]);
			} else {
				dp[0][1] = -1;
			}
		}

		// If we want to put it to the right we check if we can when the next
		// one is blocked or sprinkles also to the right, case in which we
		// choose the best combination out of this two.

		if(coord[i] + powers[i] >= coord[i+1]) {
			dp[i][2] = -1;
		} else {
			dp[i][2] = max(dp[i+1][0], dp[i+1][2]);

			// We check if we can put it to the right when the next one sprikles
			// to the left.

			if(coord[i] + powers[i] < coord[i+1] - powers[i+1]) {
				dp[i][2] = 1 + max(dp[i][2], dp[i+1][1]);
			} else {
				dp[i][2] = dp[i][2] + 1;
			}
		}
	}

	ofstream out("stropitori.out");

	out << max(max(dp[0][0], dp[0][2]), dp[0][1]);

	return 0;
}
