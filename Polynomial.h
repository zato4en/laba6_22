
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
    ~Polynomial(){
        delete[] poly;
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
        newPoly.sort();
        cinclear();
    }

    friend ostream& operator<<(ostream& out, Polynomial& newPoly){
        for (int i = 0; i < newPoly.size; ++i) {
            out <<  newPoly.poly[i];
            if(newPoly.size != 1 and i != newPoly.size - 1){
                out << " + ";
            }
        }
        out << endl;
    }

    friend Polynomial operator+(Polynomial& p1, Polynomial& p2){
        Polynomial res;
        res.size = p1.size + p2.size;
        p1.sort();
        p2.sort();
        int index;
        for (int i = 0; i < p1.size; ++i) {
            res.poly[i] = p1.poly[i];
            if(p1.poly[i].get_koef() != 0 and p1.poly[i].get_stepen() != 0){
                index = i;
            }
        }

        int counter = 0;
        for (int i = index+1; i < p1.size + p2.size; ++i) {
            res.poly[i] = p2.poly[counter];
            counter++;
        }
        res.sort();
        return res;

    }

    void resize(){
        Polynomial res;
        res.poly = new Term [size];
        for (int i = 0; i < size; ++i) {
            res.poly[i] = poly[i];
        }
        delete [] poly;
        poly = res.poly;

    }

    void sort(){



        for (int i = 0; i < size-1; ++i) {
            for (int j = i+1; j < size; ++j) {
                if(this->poly[i].stepen == this->poly[j].stepen){
                    this->poly[i].koef += this->poly[j].koef;
                    for (int k = j; k < size; ++k) {
                        this->poly[k] = this->poly[k+1];
                    }
                    size--;
                }
            }
        }
        //сложили подобные

        for (int i = 0; i < size-1; ++i) {
            for (int j = i; j < size; ++j) {
                if (this->poly[j].stepen < this->poly[j+1].stepen){
                    swap(this->poly[j].stepen,this->poly[j+1].stepen);
                }
            }
        }
        //сортируем по степеням

//        for (int i = 0; i < 2; ++i) {
//            if(this->poly[i].stepen == 0 and this->poly[i].koef == 0){
//                for (int j = i; j < 1; ++j) {
//                    swap(this->poly[j],this->poly[j+1]);
//                }
//            }
//        }
//

    }

    Polynomial& operator=(const Polynomial& pnew){
        for (int i = 0; i < 6; ++i) {
            this->poly[i] = pnew.poly[i];
        }
        return *this;
    }



};


