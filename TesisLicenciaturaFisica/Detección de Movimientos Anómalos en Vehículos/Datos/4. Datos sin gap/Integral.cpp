#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
using namespace std;

char archivo_de_entrada[50] = "Datos3.txt";
char archivo_de_salida[50] = "integralDatos32.txt";

double constant_x = 0.0;
double constant_y = 0.0;
double constant_z = 0.0;

//###############################################################################################################

char a[100];

double xyzt[4];  
double xyzt2[4];  

double sum_x=constant_x;
double sum_y=constant_y;
double sum_z=constant_z;
double promedio_x=constant_x;
double promedio_y=constant_y;
double promedio_z=constant_z;

ifstream file1;
ofstream file2;

int N_de_lineas(){                                     //Función para leer el número de datos
ifstream arch(archivo_de_entrada, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
return lin;
}

void Aceleraciones2(char a[]){         //Función para leer datos
file1.getline(a, 32, ',');
xyzt2[3] = atof(a);
file1.getline(a, 32, ',');
xyzt2[0] = atof(a);
file1.getline(a, 32, ',');
xyzt2[1] = atof(a);
file1.getline(a, 32);
xyzt2[2] = atof(a);
}



int main(){



file1.open(archivo_de_entrada);
file2.open(archivo_de_salida);
file2.setf(ios::fixed);

file1.getline(a, 100);
file2 << "tiempo, vx, vy, vz" << endl;
file2 << 0 << ',' << constant_x << ',' << constant_y << ',' << constant_z << endl;

Aceleraciones2(a);

promedio_x+=xyzt2[0];
promedio_y+=xyzt2[1];
promedio_z+=xyzt2[2];

for(int i=1; i<=N_de_lineas()-2; i++){

xyzt[3]=xyzt2[3];
xyzt[0]=xyzt2[0];
xyzt[1]=xyzt2[1];
xyzt[2]=xyzt2[2];

Aceleraciones2(a);

sum_x += ((xyzt[0]-127-1.659)/25.1)*9.81*(xyzt2[3]-xyzt[3]);
sum_y += ((xyzt[1]-127)/25.1)*9.81*(xyzt2[3]-xyzt[3]);
sum_z += ((xyzt[2]-127-25.023)/25.1)*9.81*(xyzt2[3]-xyzt[3]);

/*promedio_x+=xyzt2[0];
promedio_y+=xyzt2[1];
promedio_z+=xyzt2[2];*/

file2 << xyzt2[3] << ',' << sum_x << ',' << sum_y << ',' << sum_z << endl;

}

//cout << promedio_x/(N_de_lineas()-1) << ',' << promedio_y/(N_de_lineas()-1) << ',' << promedio_z/(N_de_lineas()-1) << endl;

file1.close();
file2.close();

return 0;

}























