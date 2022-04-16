
#include <iostream>
using namespace std;


class Term {
private:
	int koef;
	int stepen;
public:
	Term(int k = 0, int step = 0) {
		koef = k;
		stepen = step;
	}

	friend istream& operator>>(istream& in, Term& newTerm) {
		char bufstroka[20];
		char bufkoef[20];
		char bufstepen[20];
		int ind = 0, indX = 0;
		in.getline(bufstroka,100);

		bool onlyX = true, nostepen = true;

		

		for (int i = 0; bufstroka[i] != 'x'; i++) {
			if (bufstroka[i] == ' ') {
				continue;
			}
			else {
				onlyX = false;
				bufkoef[ind] = bufstroka[i];
				ind++;
				
			}
			indX = i + 1;
		}
		newTerm.koef = atoi(bufkoef);

		ind = 0;
		for (int i = indX + 1; i < strlen(bufstroka); i++) {
			if (bufstroka[i] != ' ' and bufstroka[i] != '^') {
				nostepen = false;
				bufstepen[ind] = bufstroka[i];
				ind++;
			}
		}

		newTerm.stepen = atoi(bufstepen);

		if(onlyX) {
			newTerm.koef = 1;
		}

		if (nostepen) {
			newTerm.stepen = 1;
		}

		return in;
	}

	Term& operator+(const Term& t2) {
		Term res;

		if (stepen == t2.stepen) {
			res.koef = koef + t2.koef;
			res.stepen = stepen;
		}
		return res;
	}

	friend ostream& operator<<(ostream& out, Term& T) {
		if (T.stepen == 0) {
			out << T.koef;
		}
		else if (T.stepen == 1) {
			if (T.koef == 1) {
				out << 'x';
			}
			else {
				out << T.koef << 'x';
			}
		}
		else {
			if (T.koef == 1) {
				out << 'x^' << T.stepen;
			}
			else {
				out << T.koef << "x^" << T.stepen;
			}
			
		}
		return out;
	}



};


