
#include "Term.h"


void cinclear() {
    if (char(cin.peek()) == '\n')
        cin.ignore();
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(32767, '\n');
    }
}



class Polynomial {
private:
    Term *poly;
    int size;

public:
    Polynomial(int koeff = 0, int stepenn = 0){
        if(koeff == 0 and stepenn == 0){
            size = 0;
        }
        else {
            size = 1;
            poly = new Term;
            poly[0].koef = koeff;
            poly[0].stepen = stepenn;
        }
    }
    
    Polynomial(Polynomial& P){
        size = P.size;
        poly = new Term[size];
        for (int i = 0; i < size; ++i) {
            poly[i] = P.poly[i];
        }
    }
    
    Polynomial& operator=(const Polynomial& P){
        size = P.size;
        if(this->poly != nullptr){
            delete []poly;
        }
        poly = new Term[size];

        for (int i = 0; i < size; ++i) {
            poly[i] = P.poly[i];
        }

        return *this;
    }

    void setsize(int count){
        size = count;
    }

    friend istream& operator>>(istream& in, Polynomial& newPoly){

        int count;
        in >> count;
        cinclear();
        bool flag;
        if(newPoly.size == 1){flag = true;}
        else{flag = false;}
        newPoly.size += count;
        newPoly.resize();

        if(flag){
            for (int i = 1; i < newPoly.size; ++i) {
                in >> newPoly.poly[i];
            }
        }
        else{
            for (int i = 0; i < newPoly.size; ++i) {
                in >> newPoly.poly[i];
            }
        }
        newPoly.sortt();
        newPoly.sortt();
        return in;
    }

    friend ostream& operator<<(ostream& out, Polynomial& newPoly){
        for (int i = 0; i < newPoly.size; ++i) {
            if(newPoly.poly[i].koef == 0){
                continue;
            }
            out <<  newPoly.poly[i];
            if(newPoly.size != 1 and i != newPoly.size-1 and newPoly.poly[i+1].koef > 0){
                out << " + ";
            }
        }
        out << endl;
        return out;
    }

    friend Polynomial operator+(Polynomial& p1, Polynomial& p2){
        Polynomial res;
        res.size = p1.size + p2.size;
        res.resize();
        p1.sortt();
        p2.sortt();

        for (int i = 0; i < p1.size; ++i) {
            res.poly[i] = p1.poly[i];
        }

        int counter = 0;
        for (int i = p1.size; i < p1.size + p2.size; ++i) {
            res.poly[i] = p2.poly[counter];
            counter++;
        }
        res.sortt();
        return res;

    }

    friend Polynomial operator*(Polynomial& p1, Polynomial& p2){
        Polynomial res;
        for (int i = 0; i < p1.size; ++i) {
            for (int j = 0; j < p2.size; ++j) {
                res.poly[res.size] = p1.poly[i] * p2.poly[j];
                res.size++;
                res.resize_1();
            }
            res.sortt();
        }
        return res;
    }

    void resize_1(){ //+1
        Polynomial res;
        res.poly = new Term [size + 1];
        for (int i = 0; i < size; ++i) {
            res.poly[i] = poly[i];
        }
        poly = res.poly;
    }

    void resize(){//start resize
        Polynomial res;
        res.poly = new Term [size];
        poly = res.poly;


    }

    void sortt(){ //universal sort and data processing func
        for (int i = 0; i < size-1; ++i) {
            for (int j = i+1; j < size; ++j) {
                if(poly[i].stepen == poly[j].stepen){
                    poly[i].koef += poly[j].koef;
                    for (int k = j; k < size; ++k) {
                        poly[k] = poly[k+1];
                    }
                    size--;
                }
            }
        }
        //сложили подобные
        for (int i = 0; i < size; ++i) {
            for (int j = i+1; j < size; ++j) {
                if (poly[i].stepen < poly[j].stepen){
                    swap(poly[i],poly[j]);
                }
            }
        }
    }
};

