
#include "Polynomial.h"

int main()
{
    cout << "input amount of terms, and then terms itself" << endl;
    Polynomial p1,p2;

    cin >> p1;
    cout << p1;
    cout << "input amount of terms, and then terms itself" << endl;
    cin >> p2;
    cout << p2;
    Polynomial p3 = (p1 + p2);
    cout << p3;
}