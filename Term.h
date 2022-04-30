#include <iostream>
#include <cstring>
using namespace std;

//глобальная функция для срезов с-строк
char* slice(char*s, int from, int to){
    char* buf = new char[strlen(s)+1];
    strcpy(buf,s);
    int j = 0;
    for(int i = from; i <= to; ++i)
        buf[j++] = buf[i];
    buf[j] = 0;
    return buf;
}

char** splitt(char* stroka, char razdel1, char razdel2) {
    char** res = new char*[100];
    int ind_start = 0, ind_end = 0, count = 0;

    for (int i = 0; i < strlen(stroka)+1; i++){
        if (stroka[i] == razdel1 or stroka[i] == razdel2) {
            ind_end = i-1;
            res[count] = new char[ind_end - ind_start+1];
            strcpy(res[count],slice(stroka,ind_start,ind_end));
            count++;
            ind_start = ind_end+1;
        }

    }
    ind_end = strlen(stroka) - 1;
    res[count] = new char[ind_end - ind_start];
    strcpy(res[count],slice(stroka,ind_start,ind_end));


    return res;
}


class Term {
protected:
    int koef;
    int stepen;
    friend class Polynomial;
public:
    Term(int k = 0, int step = 0) {
        koef = k;
        stepen = step;
    }


    int get_koef(){
        return this->koef;
    }

    int get_stepen(){
        return this->stepen;
    }


    friend istream& operator>>(istream& in, Term& newTerm) {

        char bufstroka[20];//введенная строка
        char bufkoef[20]; //подстрока для коэффициента
        char bufstepen[20]; //подстрока для показателя степени

        in.getline(bufstroka, 100);
        bool flag_no_probel = true;
        while(true) {
            flag_no_probel = true;
            for (int i = 0; i < strlen(bufstroka); i++) {
                if (bufstroka[i] == ' ') {
                    for (int j = i; j < strlen(bufstroka); j++) {
                        bufstroka[j] = bufstroka[j + 1];
                    }
                }
            }
            for (int i = 0; i < strlen(bufstroka); ++i) {
                if(bufstroka[i] == ' '){
                    flag_no_probel = false;
                }
            }
            if(flag_no_probel){
                break;
            }
        }
        //убрали пробелы

        bool noX = true;

        int count = 1;
        for (int i = 0; i < strlen(bufstroka) + 1; i++) {
            if (bufstroka[i] == '+' or bufstroka[i] == '-') {
                count++;
            }
            if (bufstroka[i] == 'x') {
                noX = false;
            }
        }
        //проверили, есть ли х в ненулевой степени (флаг noX)
        if(count > 1){
            Term* mas_of_term = new Term[count];
            char** matr;
            matr = splitt(bufstroka,'+','-');

            for (int i = 0; i < count; ++i) {
                strcpy(bufstroka,matr[i]);
                if(bufstroka[0] == '+'){
                    for (int j = 0; j < strlen(bufstroka); ++j) {
                        bufstroka[j] = bufstroka[j+1];
                    }
                }

                bool nokoef = false, nostepen = true, noX = true;
                if(bufstroka[0] == 'x'){
                    nokoef = true;
                }
                for (int j = 0; j < strlen(bufstroka)+1 ; ++j) {
                    if(bufstroka[j] == '^'){
                        nostepen = false;
                    }
                    if(bufstroka[j] == 'x'){
                        noX = false;
                    }
                } //проверили конкретный терм на наличие показателя и коэффа


                if(nokoef){
                    mas_of_term[i].koef = 1;
                }
                else{
                    int indexX = -1;
                    for (int j = 0; j < strlen(bufstroka)+1; ++j) {
                        if(bufstroka[j] == 'x'){
                            indexX = j;
                        }
                    }
                    if(indexX != -1){
                        strcpy(bufkoef,slice(bufstroka,0,indexX-1));
                    }
                    else{
                        strcpy(bufkoef,slice(bufstroka,0,strlen(bufstroka)));
                    }
                    if(bufkoef[0] == '-' and bufkoef[1] == '\0'){
                        mas_of_term[i].koef = -1;
                    }
                    else {
                        mas_of_term[i].koef = atoi(bufkoef);
                    }

                }
                //заполнили коэф


                if(nostepen){
                    if (noX) {
                        mas_of_term[i].stepen = 0;
                    }
                    else{
                        mas_of_term[i].stepen = 1;
                    }

                }
                else{
                    int indexX = -1;
                    for (int j = 0; j < strlen(bufstroka) + 1; ++j) {
                        if (bufstroka[j] == 'x') {
                            indexX = j;
                        }
                    }
                    strcpy(bufstepen, slice(bufstroka, indexX+2, strlen(bufstroka)));
                    mas_of_term[i].stepen = atoi(bufstepen);

                }

                //заполнили степень


            }
            newTerm.stepen = mas_of_term[0].stepen;
            for (int j = 0; j < count; ++j) {
                newTerm += mas_of_term[j];
            }
        }


        else{
            bool nokoef = false, nostepen = true, noX = true;
            if(bufstroka[0] == 'x'){
                nokoef = true;
            }
            for (int j = 0; j < strlen(bufstroka)+1 ; ++j) {
                if(bufstroka[j] == '^'){
                    nostepen = false;
                }
                if(bufstroka[j] == 'x'){
                    noX = false;
                }
            }
            //проверили конкретный терм на наличие показателя и коэффа

            if(nokoef){
                newTerm.koef = 1;
            }
            else{
                int indexX = 0;
                for (int j = 0; j < strlen(bufstroka)+1; ++j) {
                    if(bufstroka[j] == 'x'){
                        indexX = j;
                    }
                }
                strcpy(bufkoef,slice(bufstroka,0,indexX));
                newTerm.koef = atoi(bufkoef);
            }
            //заполнили коэф

            if(nostepen){
                if (noX) {
                    newTerm.stepen = 0;
                }
                else{
                    newTerm.stepen = 1;
                }

            }
            else{
                int indexX = -1;
                for (int j = 0; j < strlen(bufstroka) + 1; ++j) {
                    if (bufstroka[j] == 'x') {
                        indexX = j;
                    }
                }
                strcpy(bufstepen, slice(bufstroka, indexX+2, strlen(bufstroka)));
                newTerm.stepen = atoi(bufstepen);

            }
            //заполнили степень
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

    friend Term& operator+=(Term& left, const Term& right) {
        if(left.stepen == right.stepen){
            left.koef += right.koef;
        }
        return left;
    }


    Term& operator=(const Term& t2){
        this->stepen = t2.stepen;
        this->koef = t2.koef;
        return *this;
    }


    friend ostream& operator<<(ostream& out, Term& T) {
        if (T.stepen == 0) {
            out << T.koef;
        }
        else if (T.stepen == 1) {
            if (T.koef == 1) {
                out << 'x';
            }
            else if(T.koef == 0){
                out << '0';
            }
            else {
                out << T.koef << 'x';
            }
        }
        else {
            if (T.koef == 1) {
                out << 'x^' << T.stepen;
            }
            else if (T.koef == 0){
                out << '0';
            }
            else {
                out << T.koef << "x^" << T.stepen;
            }

        }
        return out;
    }



};

