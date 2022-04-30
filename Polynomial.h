
#include "Term.h"


class Polynomial {
private:
    Term *poly;

public:
    Polynomial(int koeff = 0, int stepenn = 0){
        poly = new Term[100];
        poly[0].koef = koeff;
        poly[0].stepen = stepenn;
    }
    ~Polynomial(){
        delete[] poly;
    }

    friend istream& operator>>(istream& in, Polynomial& newPoly){

        for (int i = 0; i < 2; ++i) {
            in >> newPoly.poly[i];
        }

        newPoly.sort();
    }

    friend ostream& operator<<(ostream& out, Polynomial& newPoly){
        for (int i = 0; i < 100; ++i) {
            out <<  newPoly.poly[i];
        }
    }

    friend Polynomial operator+(Polynomial& p1, Polynomial& p2){
        Polynomial res;
        p1.sort();
        p2.sort();
        int index;
        for (int i = 0; i < 99; ++i) {
            res.poly[i] = p1.poly[i];
            if(p1.poly[i].get_koef() != 0 and p1.poly[i].get_stepen() != 0){
                index = i;
            }
        }
        int counter = 0;
        for (int i = index+1; i < 100; ++i) {
            res.poly[i] = p2.poly[counter];
            counter++;
        }
        res.sort();
        return res;

    }

    void sort (){
        for (int i = 0; i < 1; ++i) {
            for (int j = i+1; j < 2; ++j) {
                if(this->poly[i].stepen == this->poly[j].stepen){
                    this->poly[i].koef += this->poly[j].koef;
                    for (int k = j; k < 2; ++k) {
                        this->poly[k] = this->poly[k+1];
                    }
                }
            }
        }

        for (int i = 0; i < 1; ++i) {
            for (int j = i; j < 2; ++j) {
                if (this->poly[j].stepen < this->poly[j+1].stepen){
                    swap(this->poly[j].stepen,this->poly[j+1].stepen);
                }
            }
        }

        for (int i = 0; i < 2; ++i) {
            if(this->poly[i].stepen == 0 and this->poly[i].koef == 0){
                for (int j = i; j < 1; ++j) {
                    swap(this->poly[j],this->poly[j+1]);
                }
            }
        }

    }

    Polynomial& operator=(const Polynomial& pnew){
        for (int i = 0; i < 6; ++i) {
            this->poly[i] = pnew.poly[i];
        }
        return *this;
    }



};


