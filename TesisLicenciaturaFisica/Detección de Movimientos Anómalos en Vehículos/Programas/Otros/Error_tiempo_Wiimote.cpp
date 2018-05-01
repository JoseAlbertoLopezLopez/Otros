#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
using namespace std;

char b[25];
char c[25];
int xyz[3];
double t;

char Datos_entrada[15] = "Datos2.txt";
char Datos_salida[15] = "Datos22.txt";

ifstream file8(Datos_entrada);
ofstream file9(Datos_salida);

void capturar_tiempo(char c[]){    
file8.getline(b,25,'.');
t=atoi(b);
file8.getline(c,25,',');
t += atof(c)/1000000;
file8.getline(c,25);
}


int N_de_lineas(){                                     //Función para leer el número de datos
ifstream arch(Datos_entrada, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
return lin;
}



int main(){



file9.setf(ios::fixed);             //Hace que se escriban los números con todas sus cifras, que no se use la notación decimal

file9 << "tiempo, ax, ay, az" << endl;

for(int i=1; i<=N_de_lineas(); i++){   

capturar_tiempo(c);

file9 << t << ',' << c << endl;

}

return 0;

}

