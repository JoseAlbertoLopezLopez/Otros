#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
using namespace std;


int eje = 1;
int todos_los_ejes = 1;             // 0: Desactivado, 1: Activado.
int discretizacion = 1502;          /*En algunos casos aunque el numero de frecuencias restadas sea mayor la 
                                     amplitud de la señal no se reduce tanto como con ciertos numeros 
                                     específicos de frecuencias, algunos menores.*/
int N_de_senales = 1;               // 1: Desactivado, >1: Activado

char Senal_de_entrada[50] = "Datos_0.txt";

string Senal_de_entrada_fija1 = "Datos_";
string Senal_de_entrada_fija2 = ".txt";

double filtro_amplitud = 1e-30;


//Terminan variables manuales ###################################################################################

//DFT

char a[100];
char a2[100];
char coeficientes[3][100]={"coeficientes_x.txt", "coeficientes_y.txt", "coeficientes_z.txt"};  //Los ejes x e y están al revés debido a que se quizo nombrar a los ejes del acelerómetro del telefono de forma diferente a la de fábrica
char datos_sin_ruido[3][100]={"datos_sin_ruido_x.txt", "datos_sin_ruido_y.txt", "datos_sin_ruido_z.txt"};

double xyzt[4];              //Aceleraciones en x,y,z y tiempo.

fstream file2;           
ofstream file3;

std::string i_to_s;                        //Variables para pasar de un entero a un string.
std::stringstream canal_string;

//(1)
int N_de_lineas(){                                     //Función para leer el número de datos.
ifstream arch(Senal_de_entrada, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
arch.close();
return lin;
}


void espejo(){                                         //Funció para poner los datos al revés
ifstream file(Senal_de_entrada, ifstream::in);
int lin = N_de_lineas();

for(int i=1; i<=lin; i++){
file.open(Senal_de_entrada);
file.getline(a, 99);

   for(int j=1; j<=lin-i+1; j++){
   file.getline(a, 99);
   }

file2 << a << endl;
file.close();
}
file2.close();
}


void Aceleraciones(char a[]){         //Función para leer datos
file2.getline(a, 32, ',');
xyzt[3] = atof(a);
file2.getline(a, 32, ',');
xyzt[0] = atof(a);
file2.getline(a, 32, ',');
xyzt[1] = atof(a);
file2.getline(a, 32);
xyzt[2] = atof(a);
}


int k;                                                     


int N = N_de_lineas() - 1;                                 //Número de datos


complex<double> Cpx, Cix, Ckx, Ckx_;                       //Coeficientes pares, impares y totales de acel. en x 
complex<double> w = complex<double>(0.,(-2.*M_PI)/discretizacion);      //Argumento de la exponencial compleja de la fórmula
complex<double> e = exp(w);
complex<double> m = complex<double>(1.,0.);                //Sirve para actualizar variables


void itoa(int x){                              //Función para pasar de entero a string.
canal_string << x;
i_to_s = canal_string.str();
canal_string.str(std::string());
}                       


//Quitar ruido


char opcion;
ofstream file4;
ifstream file5;
fstream file6;
fstream file7;

double ACx;
double ASx;
double x2=0.0;


//También se usa la función (1)


int N_de_lineasC(){                                     //Función para leer el número de coeficientes
ifstream arch(coeficientes[eje-1], ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
arch.close();
return lin;
}

void Aceleraciones2(char a[]){         //Función para leer datos
file5.getline(a2, 32, ',');
//xyzt[3] = atof(a);
file5.getline(a, 32, ',');
xyzt[0] = atof(a);
file5.getline(a, 32, ',');
xyzt[1] = atof(a);
file5.getline(a, 32);
xyzt[2] = atof(a);
}

void Leer_amplitudes_s(char a[]){         //Función para leer datos
file6.getline(a, 100, ',');
file6.getline(a, 100, ')');
ASx = 1.*atof(a);
file6.getline(a, 100);
}

void Leer_amplitudes_c(char a[]){         //Función para leer datos
file7.getline(a, 100, '(');
file7.getline(a, 100, ',');
ACx = 1.*atof(a);
file7.getline(a, 100);
}




