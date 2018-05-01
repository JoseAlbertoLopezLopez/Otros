#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
using namespace std;


char archivo_de_entrada[20]="Datos6.txt";
char archivo_de_salida[20]="Datos6_gap.txt";

//###############################################################################################################

double t1;
double t2;
double gap=0;

char a[100];

ifstream file_1;
ofstream file_0;

void Leer_tiempo(char a[]){
file_1.getline(a, 15, ',');
t2 = atof(a);
file_1.getline(a, 50);
}

int N_de_lineas(){                                     //Función para leer el número de datos.
ifstream arch(archivo_de_entrada, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
arch.close();
return lin;
}


int main(){


file_1.open(archivo_de_entrada);
file_0.open(archivo_de_salida);
file_0.setf(ios::fixed); 

file_1.getline(a, 15, ',');
t1 = atof(a);
file_1.getline(a, 50);

file_1.close();
file_1.open(archivo_de_entrada);

file_1.getline(a, 50);
file_0 << "tiempo, ax, ay, az" << endl;


for(int i=1; i<=N_de_lineas()-1; i++){

Leer_tiempo(a);

if(t2-t1<.05){
file_0 << t2 - gap<< ',' << a << endl;
t1=t2;
}
else{

cout << t1 << endl;
cout << t2 << endl;
gap+=t2-t1-.005;
file_0 << t2 - gap << ',' << a << endl;
t1=t2;
   
//return 0;
}


}

return 0;

}





















