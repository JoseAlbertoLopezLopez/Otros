#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
using namespace std;


char archivo_entrada1[50]="Datos6_etiq.txt";
char archivo_entrada2[50]="Deteccion_6S.gpl";

double gapi = 5;  //Tiempo despues o antes del tiempo de registro del evento a partir del cual se toma en cuenta la detección.
double gapf = 0;

double dt=0.01; //Tiempo entre datos consecutivos de los datos de recorridos.

//###############################################################################################################

char archivo_salida[50]="Fronteras.txt";

double tf1;
double tf2;
double ti=15;
double tf;
double t;

char a[100];
char Nombres[5][50]={"Normal", "Rebase", "Frenado", "Zig-zag", "Total"};
char evento_actual;
char cambio[1];

ifstream file_1;
ifstream file_2;
ofstream file_3;
ifstream file_4;

int Eventos[4][5]; // 0:Normal, 1:Rebase, 2:Frenado, 3:ZZ - normal, rebase, frenado, zig-zag, total.
int var1;
int var2;
int es_evento=0;
int c1=1;
int c2=1;
int N1;
int N2;
int N3;

int N_de_lineas(char a[]){                                     //Función para leer el número de datos.
ifstream arch(a, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
arch.close();
return lin;
}

void Leer(){
file_2.getline(a,50, '\'');
file_2.getline(a,50,' ');
t=atof(a);
file_2.getline(a,50,'\'');
var2=atoi(a);
file_2.getline(a,100);
}

void Fronteras(){

for(c1=1; c1<=N1-1; c1++){
file_1.getline(a,50,' ');
file_1.getline(a,10);

if(es_evento==0 and a[0]!='n'){
cout << a << "ewr" << endl;
file_3 << ((int) (tf2/0.5))*0.5 << ',' << cambio << ',' << es_evento << endl;
evento_actual=a[0];
es_evento=1;
}

if(es_evento==1 and a[0]=='n'){
cout << a << "ewr" << endl;
file_3 << ((int) (tf2/0.5))*0.5 << ',' << cambio << ',' << es_evento << endl;
evento_actual=a[0];
es_evento=0;
}

if(c1==N1-1){
cout << a << "ewr" << endl;
file_3 << ((int) (tf2/0.5))*0.5 << ',' << cambio << ',' << es_evento << endl;
}

tf2=(c1-1)*dt;
cambio[0]=a[0];

}
}


void Comparar_deteccion_etiqueta(){

for(int i=1; i<=N3; i++){

file_4.getline(a,50,',');
tf=atof(a);
file_4.getline(a,50,',');
evento_actual=a[0];
file_4.getline(a,50);
es_evento=atoi(a);

if(evento_actual=='n') var1=0;
else if(evento_actual=='f') var1=2;
else if(evento_actual=='r') var1=1;
else if(evento_actual=='z') var1=3;
else{cout << "Error" << endl;}

if(es_evento==1) tf+=gapf;

while(t<=((int) (ti/0.5))*0.5 and c2<=N2){
Leer();
c2++;
//cout << a << endl;
if(t==((int) (ti/0.5))*0.5){
cout << t << "," << endl;
break;
}
}

Eventos[var1][4]++;
Eventos[var1][var2]++;

while(t<tf and c2<=N2){
Leer();
c2++;
cout << var1 << endl;
Eventos[var1][4]++;
Eventos[var1][var2]++;
}


if(es_evento==1){ 
ti=tf+0.5;
}
else{
ti=tf+gapi+0.5;
}

}
}



int main(){



N1=N_de_lineas(archivo_entrada1);
N2=N_de_lineas(archivo_entrada2);

file_1.open(archivo_entrada1);
file_3.open(archivo_salida);
file_2.open(archivo_entrada2);

file_1.getline(a,100);

Fronteras();
file_3.close();
N3=N_de_lineas(archivo_salida);
file_4.open(archivo_salida);
Comparar_deteccion_etiqueta();

for(int i=0; i<=3; i++){

cout << Nombres[i] << endl;

   for(int j=0; j<=4; j++){

   cout << "  " << Nombres[j] << ": " << Eventos[i][j] << endl;

   }

cout << "Eff: " << 1.0*Eventos[i][i]/(1.0*Eventos[i][4]) << endl;
cout << endl;

}

file_1.close();
file_2.close();
file_4.close();

return 0;

}



