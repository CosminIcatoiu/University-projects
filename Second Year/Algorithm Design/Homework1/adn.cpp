// Copyright [2017] <Icatoiu Vlad Cosmin>
#include<string.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>

using namespace std;

// Matrices used for the 3 cases ( 2,3, respectively 4 strings)

int dp4[101][101][101][101];
int dp3[101][101][101];
int dp2[101][101];

// The strings and the target string

string result;
string s1;
string s2;
string s3;
string s4;

// A function which solves the problem for 2 strings

int check2(int crt1, int crt2) {
	// If we have already calculated the current configuration we just return it

	if(dp2[crt1][crt2] != 0) {
		return dp2[crt1][crt2];
	}

	// If we arrived at the end of the strings it means that we found a good
	// combinations because we test before the function call if the sizes match
	if(crt1 == s1.size() && crt2 == s2.size()) {
		dp2[crt1][crt2] = 1;
		return dp2[crt1][crt2];
	}

	// If the current letter of the target string doesn`t match with any of the
	// current letters of the forming strings, we found an invalid combination
	if(result[crt1+crt2] != s1[crt1] && result[crt1+crt2] != s2[crt2]) {
		dp2[crt1][crt2] = -1;
		return -1;
	}

	// If the letter in the result matches with the letter in the first string
	// we evaluate the possibility of choosing this letter
	if( result[crt1+crt2] == s1[crt1] ) {
		dp2[crt1][crt2]= check2(crt1+1, crt2);
	}

	// If it is a successful posibility, there is no point in trying any other
	// way of creating the target string
	if(dp2[crt1][crt2] == 1) {
		return 1;
	}

	// If we didn`t find a good possibility we try to find one by choosing the
	// letter from the second string if only it matches with the current letter
	// in the target string
	if( result[crt1+crt2] == s2[crt2] ) {
		dp2[crt1][crt2] = check2(crt1, crt2+1);
	}

	return dp2[crt1][crt2];
}

// A function which function which the same thing as check2 but works for 3
// strings. Practically the conditions are identical but they are addapted for
// 3 strings.

int check3(int crt1, int crt2, int crt3) {
	if(dp3[crt1][crt2][crt3] != 0) {
		return dp3[crt1][crt2][crt3];
	}

	if(crt1 == s1.size() && crt2 == s2.size() && crt3 == s3.size()) {
		dp3[crt1][crt2][crt3] = 1;
		return dp3[crt1][crt2][crt3];
	}

	if(result[crt1+crt2+crt3] != s1[crt1] && result[crt1+crt2+crt3] != s2[crt2]
			&& result[crt1+crt2+crt3] != s3[crt3]) {
		dp3[crt1][crt2][crt3] = -1;
		return -1;
	}

	if( result[crt1+crt2+crt3] == s1[crt1] ) {
		dp3[crt1][crt2][crt3] = check3(crt1+1, crt2, crt3);
	}

	if(dp3[crt1][crt2][crt3] == 1) {
		return 1;
	}

	if( result[crt1+crt2+crt3] == s2[crt2] ) {
		dp3[crt1][crt2][crt3] = check3(crt1, crt2+1, crt3);
	}

	if(dp3[crt1][crt2][crt3] == 1) {
		return 1;
	}
	if( result[crt1+crt2+crt3] == s3[crt3] ) {
		dp3[crt1][crt2][crt3] = check3(crt1, crt2, crt3+1);
	}
	return dp3[crt1][crt2][crt3];
}

// A function which solves the problem when we are given 4 strings and works
// on the exact same principle as the former ones, the only difference being
// that we take into consideration the forth string too.

int check4(int crt1, int crt2, int crt3, int crt4) {
	if(dp4[crt1][crt2][crt3][crt4] != 0) {
		return dp4[crt1][crt2][crt3][crt4];
	}

	if(crt1 == s1.size() && crt2 == s2.size()
		&& crt3 == s3.size() && crt4 == s4.size()) {
		dp4[crt1][crt2][crt3][crt4] = 1;
		return dp4[crt1][crt2][crt3][crt4];
	}

	if(result[crt1+crt2+crt3+crt4] != s1[crt1] &&
		result[crt1+crt2+crt3+crt4] != s2[crt2] &&
		result[crt1+crt2+crt3+crt4] != s3[crt3] &&
		result[crt1+crt2+crt3+crt4] != s4[crt4] ) {
		dp4[crt1][crt2][crt3][crt4] = -1;
		return -1;
	}

	if( result[crt1+crt2+crt3+crt4] == s1[crt1] ) {
		dp4[crt1][crt2][crt3][crt4] = check4(crt1+1, crt2, crt3, crt4);
	}

	if(dp4[crt1][crt2][crt3][crt4] == 1) {
		return 1;
	}

	if( result[crt1+crt2+crt3+crt4] == s2[crt2] ) {
		dp4[crt1][crt2][crt3][crt4] = check4(crt1, crt2+1, crt3, crt4);
	}

	if(dp4[crt1][crt2][crt3][crt4] == 1) {
		return 1;
	}

	if( result[crt1+crt2+crt3+crt4] == s3[crt3] ) {
		dp4[crt1][crt2][crt3][crt4] = check4(crt1, crt2, crt3+1, crt4);
	}

	if(dp4[crt1][crt2][crt3][crt4] == 1) {
		return 1;
	}

	if( result[crt1+crt2+crt3+crt4] == s4[crt4] ) {
		dp4[crt1][crt2][crt3][crt4] = check4(crt1, crt2, crt3, crt4+1);
	}
	return dp4[crt1][crt2][crt3][crt4];
}

int main() {
	ifstream in("adn.in");

	int T;

	in >> T;

	int N, i;

	ofstream out("adn.out");

	for(i = 1; i <= T; i++) {
		in >> N;

		in >> s1;

		in >> s2;

		// Taking into consideration the number of strings we call the
		// appropriate function and print the result which will always be in the
		// first cell of the matrices. But before everything I reinitialize the
		// dp matrix that we are goint to use for the current test, only if the
		// test may return 1 (it passes the length test).

		if(N == 2) {
			in >> result;

			if( result.size() == s1.size() + s2.size() ) {
				memset(dp2, 0, sizeof(dp2));

				check2(0, 0);

				if(dp2[0][0] == -1)
					out << "0" << endl;
				else
					out << "1" << endl;
			} else {
				out << "0" << endl;
			}
		} else {
			if(N == 3) {
				in >> s3;

				in >> result;

				if(result.size() == s1.size() + s2.size() +s3.size()) {
					memset(dp3, 0, sizeof(dp3));

					check3(0, 0, 0);

					if(dp3[0][0][0] == -1)
						out << "0" << endl;
					else
						out << "1" << endl;

				} else {
					out << "0" << endl;
				}
			} else {
				if(N == 4) {
					in >> s3;

					in >> s4;

					in >> result;

					if(result.size() == s1.size() + s2.size()
													+ s3.size() + s4.size()) {
						memset(dp4, 0,
						s1.size()*s2.size()*s3.size()*s4.size()*sizeof(int));

						check4(0, 0, 0, 0);

						if(dp4[0][0][0][0] == -1)
							out << "0" << endl;
						else
							out << "1" << endl;

					} else {
						out << "0" << endl;
					}
				} else {
					if(s1.compare(s2) == 0)
						out << "1"<< endl;
					else
						out << "0"<< endl;
				}
			}
		}
	}

	in.close();
	out.close();
	return 0;
}
