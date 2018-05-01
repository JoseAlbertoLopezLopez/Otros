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

char Senal_de_entrada[50] = "1(estatico)txt";
char Senal_de_salida[50] = "Eventos";

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


file1.getline(a, 20, ' ');
file1.getline(a, 20, ' ');
t0=atof(a);
file1.getline(a, 20, ' ');
evento=atoi(a);
file1.getline(a, 100);
file2 << 0 << ',' << evento << endl;


for(int i=1; i<=N_de_lineas(); i++){

file1.getline(a, 20, ' ');
file1.getline(a, 20, ' ');
t=atof(a);
file1.getline(a, 20, ' ');

if (atoi(a)!=evento){
file2 << t-t0 << ',' << evento << endl;
evento=atoi(a);
}

file1.getline(a, 100);
}

file1.close();
file2.close();

return 0;

}























