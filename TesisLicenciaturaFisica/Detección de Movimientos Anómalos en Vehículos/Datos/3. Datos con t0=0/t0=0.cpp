#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
using namespace std;


char a[100];

int evento;

double t;
double t0;

char Senal_de_entrada[50] = "Datos2.1_inter.txt";
char Senal_de_salida[50] = "Datos2.1.t0txt";

ifstream file1;
ofstream file2;

int N_de_lineas(){                                     //Función para leer el número de datos
ifstream arch(Senal_de_entrada, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
return lin;
}



int main(){



file1.open(Senal_de_entrada);
file2.open(Senal_de_salida);


file1.getline(a, 100);
file1.getline(a, 20, ',');
t0=atof(a);
file1.getline(a, 100);
evento=atoi(a);
file2 << 0 << ',' << a << endl;


for(int i=1; i<=N_de_lineas(); i++){

file1.getline(a, 20, ',');
file1.getline(a, 100);

//if (atoi(a)!=evento){
file2 << i*0.01 << ',' << a << endl;
//evento=atoi(a);
//}

}

file1.close();
file2.close();

return 0;

}























