#include <iostream>
#include "Huge_Integer.h"
using namespace std;
int main()
{
    HugeInt** I = nullptr;
    int _nos;
    ifstream fin("input.txt");
    fin >> _nos;
    I = new HugeInt * [_nos];
    for (int i = 0; i < _nos; i++)
    {
        I[i] = new HugeInt(fin);
    }
    for (int i = 0; i < _nos; i++)
    {
        cout << *I[i] << endl;
    }
    //cout << (*I[0] <= *I[0]);
    HugeInt test;
    
    test = *I[0]/(*I[0]);
    //test /= (*I[1]);
    cout << test;
    


    return 0;
}
