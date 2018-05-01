#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <cstdlib>
using namespace std;

double prueba;
int N = 220;
int N_frec = 220;
int frec_totales = 1980;
int frecuencia;
int comparador;
double A = 0.0;
double S = 0.0;
int f = 0;
char a[100];
double valor_limite_1 = 10.0;
double gap = 50.0;

ofstream file("datos_random.txt");
ofstream file1("Amplitudes.txt");
ofstream file2("Frecuencias.txt");
fstream file3("Frecuencias.txt");



int main(){



int fraccion_1 = (int) N*.1;

for(int i=1; i<=fraccion_1; i++){

prueba = (1.*rand()/RAND_MAX)*valor_limite_1*10.0;

if(prueba > gap){

file1 << prueba << endl;
frecuencia = rand()%frec_totales;

Continuar:
file3.seekp(0, ios::beg);
    for(int j=2; j<=i; j++){
    file3.getline(a,32);
    comparador = atoi(a);
    if(frecuencia == comparador){
    frecuencia = rand()%frec_totales;
    goto Continuar;
    }
    }
file2 << frecuencia << endl;

}

else{
i=i-1;
}

}

for(int i=fraccion_1+1; i<=N_frec; i++){

file1 << (1.*rand()/RAND_MAX)*valor_limite_1 << endl;
frecuencia = rand()%frec_totales;

Continuar2:
file3.seekp(0, ios::beg);
    for(int j=2; j<=i; j++){
    file3.getline(a,32);
    comparador = atoi(a);
    if(frecuencia == comparador){
    frecuencia = rand()%frec_totales;
    goto Continuar2;
    }
    }
file2 << frecuencia << endl;

}



file1.close();
file2.close();
file3.close();

file << "time" << "," << 'x' << "," << 'y' << "," << 'z' << endl;       //Formato de aplicación de celular

ifstream file1("Amplitudes.txt");
ifstream file2("Frecuencias.txt");


for(int n=0; n<=frec_totales-1; n++){


for(int i=1; i<=N_frec; i++){

file1.getline(a, 32 , '\n');
A = atof(a);
file2.getline(a, 32 , '\n');
f = atoi(a);

S = S + A*cos(2.*M_PI*(1.*f*n/frec_totales));

}

file1.close();
file2.close();

file1.open("Amplitudes.txt");
file2.open("Frecuencias.txt");

file << n << "," << S << "," << 0.0 << "," << 0.0 << endl;

S = 0.0;

}

/*
//Formato de gráfica de Gnuplot

ofstream file("datos.txt");

for(int n=0; n<=N-1; n++){
file << n << " " << x << " " << y << " " << z << endl;
}
*/

return 0;

}


