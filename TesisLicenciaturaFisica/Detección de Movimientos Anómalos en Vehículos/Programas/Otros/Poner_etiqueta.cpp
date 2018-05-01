#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
using namespace std;

int num_arc_ent=7;

char archivo_salida[50]="Datos6_etiq.txt";

string Senal_de_entrada_fija1 = "Datos6.";
string Senal_de_entrada_fija2 = ".txt";

char frenado='f';
char rebase='r';
char zigzag='z';
char regular='n';
char mov_actual=rebase;

//###############################################################################################################

char archivo_entrada[50];
char a[50];

ofstream file_0;
ifstream file_1;

std::string i_to_s;                        //Variables para pasar de un entero a un string.
std::stringstream canal_string;

int N_de_lineas(){                                     //Función para leer el número de datos.
ifstream arch(archivo_entrada, ifstream::in);
int lin=0;
while(arch.good()) if(arch.get()=='\n') lin++;
arch.close();
return lin;
}

void itoa(int x){                              //Función para pasar de entero a string.
canal_string << x;
i_to_s = canal_string.str();
canal_string.str(std::string());
}       



int main(){



file_0.open(archivo_salida);
file_0 << "tiempo, ax, ay, az" << endl;

for(int i=1; i<=num_arc_ent; i++){

itoa(i);
strcpy(archivo_entrada, (Senal_de_entrada_fija1 + i_to_s + Senal_de_entrada_fija2).c_str());
file_1.open(archivo_entrada);
//file_1.getline(a, 50);

   for(int j=1; j<=N_de_lineas(); j++){

   file_1.getline(a, 50);
   file_0 << a << " ";

   if(i%2>0 or i==1){
   file_0 << regular << endl;   
   }
   if(i==2){
   file_0 << zigzag << endl;
   }
   if(i==4){
   file_0 << frenado << endl;
   }
   if(i==6){
   file_0 << rebase << endl;
   }

   }

file_1.close();

}

file_0.close();

return 0;
}













