#include <iostream>
#include <cstring>
using namespace std;

//глобальная функция для срезов с-строк
char* slice(char*s, int from, int to){
    char* buf = new char[strlen(s)+1];
    strcpy(buf,s);
    int j = 0;
    for(int i = from; i < to; ++i)
        buf[j++] = buf[i];
    buf[j] = 0;
    return buf;
}

char** splitt(char* stroka, char razdel1, char razdel2) {
    char** res = new char* [100];
    int ind_start = 0, ind_end = 0, count = 0;
    for (int i = 0; i < strlen(stroka)+1; i++){
        if (stroka[i] == razdel1 or stroka[i] == razdel2) {
            ind_end = i;
            res[count] = new char[ind_end - ind_start];
            strcpy(res[count],slice(stroka,ind_start,ind_end));
            count++;
            ind_start = ind_end + 1;
        }
    }
    ind_end = strlen(stroka) - 1;
    res[count] = new char[ind_end - ind_start + 1];
    strcpy(res[count],slice(stroka,ind_start,ind_end));

    return res;
}


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

        char bufstroka[20];//введенная строка
        char bufkoef[20]; //подстрока для коэффициента
        char bufstepen[20]; //подстрока для показателя степени

        in.getline(bufstroka, 100);

        for (int i = 0; i < strlen(bufstroka); i++) {
            if (bufstroka[i] == ' ') {
                for (int j = i + 1; j < strlen(bufstroka) + 1; j++) {
                    bufstroka[j - 1] = bufstroka[j];
                }
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
                    mas_of_term[i].koef = 1;
                }
                else{
                    int indexX = 0;
                    for (int j = 0; j < strlen(bufstroka)+1; ++j) {
                        if(bufstroka[j] == 'x'){
                            indexX = j;
                        }
                    }
                    strcpy(bufkoef,slice(bufstroka,0,indexX));
                    mas_of_term[i].koef = atoi(bufkoef);
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
                    strcpy(bufstepen, slice(bufstroka, 0, indexX));
                    mas_of_term[i].stepen = atoi(bufstepen);
                    
                }

                //заполнили степень


            }

            for (int i = 0; i < count; ++i) {
                newTerm = newTerm + mas_of_term[i];
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