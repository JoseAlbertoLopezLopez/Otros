#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
using namespace std;

double t;
double x;
double y;
double z;
double f;
int eje = 1;
int todos_los_ejes = 0;
char a[100];
string d;

char Datos_de_entrada[50] = "Datos4.17.txt";

char coeficientes[3][100]={"coeficientes_x.txt", "coeficientes_y.txt", "coeficientes_z.txt"};  //Los ejes x e y están al revés debido a que se quizo nombrar a los ejes del acelerómetro del telefono de forma diferente a la de fábrica

char datos_sin_ruido[3][100]={"datos_sin_ruido_x.txt", "datos_sin_ruido_y.txt", "datos_sin_ruido_z.txt"};  //Los ejes x e y están al revés debido a que se quizo nombrar a los ejes del acelerómetro del telefono de forma diferente a la de fábrica

char G_Espectro_senos[3][100]={"G_Espectro_senos_x.txt", "G_Espectro_senos_y.txt", "G_Espectro_senos_z.txt"};  //Los ejes x e y están al revés debido a que se quizo nombrar a los ejes del acelerómetro del telefono de forma diferente a la de fábrica

char G_Espectro_cosenos[3][100]={"G_Espectro_cosenos_x.txt", "G_Espectro_cosenos_y.txt", "G_Espectro_cosenos_z.txt"};  //Los ejes x e y están al revés debido a que se quizo nombrar a los ejes del acelerómetro del telefono de forma diferente a la de fábrica

char G_Datos[3][100]={"G_Datos_xyz_7.txt", "NULL.txt", "NULL.txt"};  //Los ejes x e y están al revés debido a que se quizo nombrar a los ejes del acelerómetro del telefono de forma diferente a la de fábrica


//###############################################################################################################


ifstream file;
//ifstream file2;
ofstream file3;
//ofstream file4;
//ofstream file5;

int N_de_lineas(){                                     //Función para leer el número de datos
ifstream arch(Datos_de_entrada, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
return lin;
}

int N_de_lineasC(){                                     //Función para leer el número de coeficientes
ifstream arch(coeficientes[eje-1], ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
return lin;
}

int n = N_de_lineas()-1;

int N = N_de_lineasC();

void escribir_columna_xyz(char a[]){         //Función para leer datos
file.getline(a, 32, ',');
t = atof(a);
file3 << a << " ";                      //CAMBIO
file.getline(a, 32, ',');
x = atof(a);
file.getline(a, 32, ',');
y = atof(a);
file.getline(a, 32);
z = atof(a);
file3 << sqrt(x*x+y*y+z*z) << endl;
}



int main(){



if(todos_los_ejes==1){
eje=1;
cout << endl;
cout << "ALERTA: Se trabajará con todos los ejes" << endl;
cout << endl;
}

for(int contador=0; contador<=todos_los_ejes*2; contador++){

file.open(Datos_de_entrada);
//file2.open(coeficientes[eje-1]);                   //ACTIVAR EL MODO DE ABRIR SI SOLO EL ARCHIVO EXISTE PARA EVITAR CREAR ARCHIVOS VACIOS
file3.open(G_Datos[eje-1]);
//file4.open(G_Espectro_senos[eje-1]);
//file5.open(G_Espectro_cosenos[eje-1]);
/*
for(int i=0; i<=N-1; i++){
escribir_Cc(a);
file5 << 1.*M_PI*i/N << " " << abs(f) << endl;            //Espectro en valor absoluto
}

file2.close();
file2.open(coeficientes[eje-1]);

for(int i=0; i<=N-1; i++){
escribir_Cs(a);
file4 << 1.*M_PI*i/N << " " << abs(-f) << endl;          //Espectro en valor absoluto
}
*/
if(eje == 1){
file.getline(a, 32);
for(int i=1; i<=n; i++){
escribir_columna_xyz(a);
}
}


file.close();
//file2.close();
file3.close();
//file4.close();
//file5.close();

eje++;

}

return 0;

}








