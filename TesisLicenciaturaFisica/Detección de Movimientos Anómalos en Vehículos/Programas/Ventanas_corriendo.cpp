#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
using namespace std;

double Lim_inf = 0.0;
double Lim_inf_temp = 0.0;
double Lim_sup = 142.43;
double ventana = 15.0;
double dt = 0.5;

char Senal_de_entrada[50] = "Datos6.txt";
char Senal_de_salida[20];

//###############################################################################################################

int c2 = 0;

char a[50];

ofstream file1_0;
fstream file1_1;

std::string i_to_s;                        //Variables para pasar de un entero a un string.
std::stringstream canal_string;

double t2=0;

void tiempo(char a[]){
file1_1.getline(a,32,',');
t2=atof(a);
file1_1.getline(a,50);
}

void itoa(int x){                              //Función para pasar de entero a string.
canal_string << x;
i_to_s = canal_string.str();
canal_string.str(std::string());
}       



int main(){



for(int contador=0; contador<=(Lim_sup-Lim_inf-ventana)/dt; contador++){
itoa(contador*5);
strcpy(Senal_de_salida, ("Datos_" + i_to_s + ".txt").c_str());
file1_1.open(Senal_de_entrada,ios::in);
file1_1.getline(a,50);
file1_0.open(Senal_de_salida,ios::out);
//file1_0.setf(ios::fixed); 
file1_0 << "tiempo, ax, ay, az" << endl;

   while(t2<Lim_inf+contador*dt){
   tiempo(a);
   }

   Lim_inf_temp = t2;
   if(Lim_inf_temp + ventana > Lim_sup) return 0;
   if(t2!=0){
   file1_0 << t2 << ',' << a << endl;
   c2++;
   }
   while(t2<=Lim_inf_temp+ventana){
//   continuar:
   tiempo(a);
   file1_0 << t2 << ',' << a << endl;
   c2++;
   }



//if(c2%2!=0) goto continuar;
if(c2!=1502){
cout << "Error en archivo " << contador << endl;
}
file1_1.seekp(0, ios::beg);
file1_0.close();
file1_1.close();
t2=0;
c2=0;

}

return 0;

}

