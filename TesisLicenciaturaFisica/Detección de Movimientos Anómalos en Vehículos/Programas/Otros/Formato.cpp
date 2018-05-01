#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
using namespace std;

char a[100];
char a2[100];
double xyz[3];

char Datos_entrada[100] = "2 (regular con curvas 1 pausa).txt";
char Datos_salida[100] = "Datos2.txt";

ifstream file8(Datos_entrada);
ofstream file9(Datos_salida);

void capturar_tiempo(char a2[]){    
file8.getline(a2,100,' ');
file8.getline(a2,100,' ');
//file8.getline(a,100);
}

void Aceleraciones(char a[]){
file8.getline(a,100,' ');
file8.getline(a,100,' ');
xyz[0]=atoi(a);
file8.getline(a,100,' ');
xyz[1]=atoi(a);
file8.getline(a,100);
xyz[2]=atoi(a);
}

int N_de_lineas(){                                     //Función para leer el número de datos
ifstream arch(Datos_entrada, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
return lin;
}



int main(){



file9 << "tiempo, ax, ay, az" << endl;

for(int i=1; i<=N_de_lineas(); i++){   

capturar_tiempo(a2);
Aceleraciones(a);
file9 << a2 << "," << xyz[0] << "," << xyz[1] << "," << xyz[2] << endl;

}

return 0;

}

