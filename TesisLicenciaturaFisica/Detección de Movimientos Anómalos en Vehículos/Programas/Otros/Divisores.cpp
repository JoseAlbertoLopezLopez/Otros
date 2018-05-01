#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
using namespace std;

int N = 27966;
int limite = 25;         //Límite real: 2*limite


int main(){

for(int j=0; j<=limite; j++){

cout << endl;
cout << "Para  " << N-2*j << endl;

   for(int i=2; i<N-2*j-1; i++){

   if(!((N-2*j)%i)){
   cout << i << endl;
   }

   }

}

return 0;

}

