#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
using namespace std;


int Num_de_datos=15000;

double ventana=150.00;

char archivo_de_entrada[50]="Datos2.1.txt";
char archivo_de_salida[50]="Datos2.1_inter.txt";

//###############################################################################################################

int c1=0;
int extrapolados=0;

double dt=ventana/Num_de_datos;
double xyzt1[4];
double xyzt2[4];
double xyzt_inter[4]={0};

char a[100];

ifstream file_1;
ofstream file_0;

void Aceleraciones(char a[]){         //Función para leer datos
file_1.getline(a, 32, ',');
xyzt2[3] = atof(a);
file_1.getline(a, 32, ',');
xyzt2[0] = atoi(a);
file_1.getline(a, 32, ',');
xyzt2[1] = atoi(a);
file_1.getline(a, 32);
xyzt2[2] = atoi(a);
}

void Interpolar(){
xyzt_inter[0] = xyzt1[0]+((xyzt_inter[3]-xyzt1[3])/(xyzt2[3]-xyzt1[3]))*(xyzt2[0]-xyzt1[0]);
xyzt_inter[1] = xyzt1[1]+((xyzt_inter[3]-xyzt1[3])/(xyzt2[3]-xyzt1[3]))*(xyzt2[1]-xyzt1[1]);
xyzt_inter[2] = xyzt1[2]+((xyzt_inter[3]-xyzt1[3])/(xyzt2[3]-xyzt1[3]))*(xyzt2[2]-xyzt1[2]);
}

void xyzt1__xyzt2(){
xyzt1[3]=xyzt2[3];
xyzt1[0]=xyzt2[0];
xyzt1[1]=xyzt2[1];
xyzt1[2]=xyzt2[2];
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

file_1.getline(a, 50);
file_1.getline(a, 50);
file_0 << "tiempo, ax, ay, az" << endl;
file_0 << a << endl;

file_1.getline(a, 32, ',');
xyzt1[3] = atof(a);
file_1.getline(a, 32, ',');
xyzt1[0] = atoi(a);
file_1.getline(a, 32, ',');
xyzt1[1] = atoi(a);
file_1.getline(a, 32);
xyzt1[2] = atoi(a);

Aceleraciones(a);

xyzt_inter[3]+=dt;

for(int i=2; i<=((N_de_lineas())-2) and c1<Num_de_datos;){         //Es -2 debido a que después de los ultimos 2 puntos no se tiene la certeza si todavía halla que interpolar más de una vez.

if(xyzt2[3]>xyzt_inter[3]){
Interpolar();
file_0 << xyzt_inter[3] << ',' << xyzt_inter[0] << ',' << xyzt_inter[1] << ',' << xyzt_inter[2] << endl;
xyzt_inter[3]+=dt;
c1++;
}
else{
xyzt1__xyzt2();
Aceleraciones(a);
i++;
}

}


while(c1<Num_de_datos){           // Caso en el que se acaban los datos antes de completar la ventana.
Interpolar();
file_0 << xyzt_inter[3] << ',' << xyzt_inter[0] << ',' << xyzt_inter[1] << ',' << xyzt_inter[2] << endl;
xyzt_inter[3]+=dt;
c1++;
extrapolados++;
cout << "Datos extrapolados = " << extrapolados << endl;
}

return 0;

}









