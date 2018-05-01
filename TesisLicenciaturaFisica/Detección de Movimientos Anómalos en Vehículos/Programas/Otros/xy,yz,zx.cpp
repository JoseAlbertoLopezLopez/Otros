#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
using namespace std;

char archivo_de_entrada[50]="Datos4.txt";
char archivo_de_salida[50]="Datos4xy.txt";

//###############################################################################################################

char a[100];

double xyzt[4];              //Aceleraciones en x,y,z y tiempo.

ifstream file_1;
ofstream file_0;

int N_de_lineas(){                                     //Función para leer el número de datos.
ifstream arch(archivo_de_entrada, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
arch.close();
return lin;
}

void Aceleraciones(char a[]){         //Función para leer datos
file_1.getline(a, 32, ',');
xyzt[3] = atof(a);
file_1.getline(a, 32, ',');
xyzt[0] = atof(a);
file_1.getline(a, 32, ',');
xyzt[1] = atof(a);
file_1.getline(a, 32);
xyzt[2] = atof(a);
}



int main(){



file_1.open(archivo_de_entrada);
file_0.open(archivo_de_salida);

file_1.getline(a, 50);
file_0 << "tiempo, axy, ayz, azx" << endl;

for(int i=1; i<=N_de_lineas()-1;i++){

Aceleraciones(a);

file_0 << xyzt[3] << ',' << sqrt(xyzt[0]*xyzt[0]+xyzt[1]*xyzt[1]) << ',' << sqrt(xyzt[1]*xyzt[1]+xyzt[2]*xyzt[2]) << ',' << sqrt(xyzt[2]*xyzt[2]+xyzt[0]*xyzt[0]) << endl;

}

return 0;

}





















