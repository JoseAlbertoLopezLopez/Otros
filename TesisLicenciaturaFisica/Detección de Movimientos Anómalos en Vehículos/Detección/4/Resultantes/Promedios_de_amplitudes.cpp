#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
using namespace std;

const int c=3.15/.005;
double intervalo=0.05;

//###############################################################################################################

int N_de_lineas_C;
int N_de_lineas_S;
int c1=0;
int c2[c]={0};
int Max=0;

double suma_C[c]={0.};
double suma_S[c]={0.};
double temp1=0;

ifstream file_1_C;
ifstream file_1_S;
ofstream file_0;

char a[100]; 
char archivo_de_entrada[50];

int N_de_lineas(){                                     //Función para leer el número de datos.
ifstream arch(archivo_de_entrada, ifstream::in);       //OJO: Cambio el nombre de la variable.
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
arch.close();
return lin;
}



int main(){



string cadena="Frecuencias_mas_altas_C.txt";
strcpy(archivo_de_entrada, (cadena).c_str());
file_1_C.open(archivo_de_entrada);
N_de_lineas_C=N_de_lineas();

cadena="Frecuencias_mas_altas_S.txt";
strcpy(archivo_de_entrada, (cadena).c_str());
file_1_S.open(archivo_de_entrada);
N_de_lineas_S=N_de_lineas();

file_0.open("Promedios de amplitudes más altas.txt");

file_0 << "Cosenos:" << endl;
file_1_C.getline(a, 100);

for(int i=1; i<=N_de_lineas_C-1; i++){

file_1_C.getline(a, 20, ' ');
file_1_C.getline(a, 20, ' ');
temp1=atof(a);
file_1_C.getline(a, 20);

c1=temp1/intervalo;

c2[c1]++;
suma_C[c1]+=temp1;

if(c1>Max) Max=c1;

}

for(int i=0; i<=Max; i++){

if(suma_C[i]!=0) file_0 << suma_C[i]/c2[i] << endl;

}

int c2[c]={0};

file_0 << "Senos:" << endl;
file_1_S.getline(a, 100);

for(int i=1; i<=N_de_lineas_S-1; i++){

file_1_S.getline(a, 20, ' ');
file_1_S.getline(a, 20, ' ');
temp1=atof(a);
file_1_S.getline(a, 20);

c1=temp1/intervalo;

//cout << c1 << endl;

c2[c1]++;
suma_S[c1]+=temp1;

if(c1>Max) Max=c1;

}

for(int i=0; i<=Max; i++){

if(suma_S[i]!=0) file_0 << suma_S[i]/c2[i] << endl;

}

file_1_C.close();
file_1_S.close();
file_0.close();

return 0;
}































