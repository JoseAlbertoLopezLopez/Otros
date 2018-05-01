#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
using namespace std;

double t1=0.0;

char archivo_de_entrada[50]="Datos3_inter.txt";
char archivo_de_salida[50]="Diferencia_de_tiempos.txt";

//###############################################################################################################

ifstream file;
ofstream file2;

double t2;
char a[100];

int N_de_lineas(){                                     //Función para leer el número de datos
ifstream arch(archivo_de_entrada, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
return lin;
}

int N = N_de_lineas() - 1;

void leer(char a[]){
file.getline(a, 32, ',');
t2 = atof(a);
file.getline(a, 32);
}



int main(){

file.open(archivo_de_entrada);
file2.open(archivo_de_salida);

file.getline(a, 100);

for (int k=1; k<=N; k++){        
leer(a);
file2 << k << " " << t2-t1 << endl;
t1 = t2;
}

file.close();
file2.close();

return 0;

}






